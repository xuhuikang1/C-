#ifndef MUTITHREADEDTABLEWRITER_H_
#define MUTITHREADEDTABLEWRITER_H_

#include "Exports.h"
#include "Concurrent.h"
#include "Util.h"
#include "Types.h"
#include "Exceptions.h"
#include <unordered_map>
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <tuple>
#include <cassert>
#include <unordered_map>


namespace dolphindb{

class DBConnection;

class PytoDdbRowPool;
class EXPORT_DECL MultithreadedTableWriter {
public:
    enum Mode{
        M_Append,
        M_Upsert,
    };
    struct ThreadStatus{
        long threadId;
        long sentRows,unsentRows,sendFailedRows;
        ThreadStatus(){
            threadId = 0;
            sentRows = unsentRows = sendFailedRows = 0;
        }
    };
    struct Status : ErrorCodeInfo{
        bool isExiting;
        long sentRows, unsentRows, sendFailedRows;
        std::vector<ThreadStatus> threadStatus_;
        void plus(const ThreadStatus &threadStatus){
            sentRows += threadStatus.sentRows;
            unsentRows += threadStatus.unsentRows;
            sendFailedRows += threadStatus.sendFailedRows;
        }
    };
    /**
     * If fail to connect to the specified DolphinDB server, this function throw an exception.
     */
    MultithreadedTableWriter(const std::string& host, int port, const std::string& userId, const std::string& password,
                            const std::string& dbPath, const std::string& tableName, bool useSSL, bool enableHighAvailability = false, const std::vector<std::string> *pHighAvailabilitySites = nullptr,
							int batchSize = 1, float throttle = 0.01f,int threadCount = 1, const std::string& partitionCol ="",
							const std::vector<COMPRESS_METHOD> *pCompressMethods = nullptr, Mode mode = M_Append,
                            std::vector<std::string> *pModeOption = nullptr, const std::function<void(ConstantSP)> &callbackFunc = nullptr, bool enableStreamTableTimestamp = false);

    virtual ~MultithreadedTableWriter();

    template<typename... TArgs>
    bool insert(ErrorCodeInfo &errorInfo, TArgs... args) {
        RWLockGuard<RWLock> guard(&insertRWLock_, false);
        if (hasError_.load()) {
            throw RuntimeException("Thread is exiting for " + errorInfo_.errorInfo);
        }
        {
            auto argSize = sizeof...(args);
            if (argSize != colTypes_.size()) {
                errorInfo.set(ErrorCodeInfo::EC_InvalidParameter, "Column counts don't match " + std::to_string(argSize));
                return false;
            }
        }
        {
            errorInfo.clearError();
            int colIndex1 = 0, colIndex2 = 0;
            ConstantSP result[] = { Util::createObject(getColDataType(colIndex1++), args, &errorInfo, colExtras_[colIndex2++])... };
            if (errorInfo.hasError()){
                for(int i = static_cast<int>(colTypes_.size() - 1); i >= 0; --i){
                    if(result[i].isNull()){
                        errorInfo.errorInfo.append(" for col ").append(std::to_string(i + 1));
                        return false;
                    }
                }
                return false;
            }
            std::vector<ConstantSP> oneRow(std::begin(result), std::end(result));
            std::vector<ConstantSP>* pRow = &oneRow;
            return insert(&pRow, 1, errorInfo);
        }
    }

	void waitForThreadCompletion();
    void getStatus(Status &status);
    void getUnwrittenData(std::vector<std::vector<ConstantSP>*> &unwrittenData);
	bool insertUnwrittenData(std::vector<std::vector<ConstantSP>*> &records, ErrorCodeInfo &errorInfo) { return insert(records.data(), static_cast<int>(records.size()), errorInfo, true); }
    
	//bool isExit(){ return hasError_; }
    //const DATA_TYPE* getColType(){ return colTypes_.data(); }
    //int getColSize(){ return colTypes_.size(); }
private:
	bool insert(std::vector<ConstantSP> **records, int recordCount, ErrorCodeInfo &errorInfo, bool isNeedReleaseMemory = false);
	void setError(int code, const std::string &info);
    void setError(const ErrorCodeInfo &errorInfo);
    DATA_TYPE getColDataType(int colIndex) {
		DATA_TYPE dataType = colTypes_[colIndex];
		if (dataType >= ARRAY_TYPE_BASE)
			dataType = (DATA_TYPE)(dataType - ARRAY_TYPE_BASE);
		return dataType;
	}
	void insertThreadWrite(int threadhashkey, std::vector<ConstantSP> *prow);
    static void callBack(std::function<void(ConstantSP)> callbackFunc, bool result, std::vector<ConstantSP>* block);
    std::vector<ConstantSP>* createColumnBlock();
    struct WriterThread {
		WriterThread() : nonemptySignal(false,true){}
		SmartPointer<DBConnection> conn;
        
        std::list<std::vector<ConstantSP>*> writeQueue_;   //每个元素都是一个子表，按列排好，最大行数为perVectorSize_
        std::vector<std::vector<ConstantSP>*> failedQueue_;
        ThreadSP writeThread;
        Signal nonemptySignal;

        Mutex mutex_, writeQueueMutex_;
        unsigned int threadId;
        long sentRows;
		bool exit;
    };
    class SendExecutor : public dolphindb::Runnable {
    public:
		SendExecutor(MultithreadedTableWriter &tableWriter,WriterThread &writeThread):
                        tableWriter_(tableWriter),
                        writeThread_(writeThread){};
        virtual void run();
    private:
        void callBack();
		bool isExit() { return tableWriter_.hasError_.load() || writeThread_.exit; }
        bool init();
        bool writeAllData();
        MultithreadedTableWriter &tableWriter_;
        WriterThread &writeThread_;
    };
    
private:
    friend class SendExecutor;
	friend class InsertExecutor;
    const std::string dbName_;
    const std::string tableName_;
    const int batchSize_;
    int       perBlockSize_;               //每一段预分配的空间可以容纳的行数 perBlockSize_ = batchSize < 65535 ? 65535 : batchSize_
    const int throttleMilsecond_;
    bool isPartionedTable_, exited_;
	std::atomic_bool hasError_;
    //all column include callback id
    std::vector<std::string> colNames_,colTypeString_;
    std::vector<DATA_TYPE> colTypes_;
	std::vector<int> colExtras_;
    //columns except callback id which no need to save.
    std::vector<std::string> saveColNames_;
    std::vector<DATA_TYPE> saveColTypes_;
    std::vector<int> saveColExtras_;
	std::vector<COMPRESS_METHOD> saveCompressMethods_;
    //Following parameters only valid in multithread mode
    SmartPointer<Domain> partitionDomain_;
    int partitionColumnIdx_;
    int threadByColIndexForNonPartion_;
	//End of following parameters only valid in multithread mode
    std::vector<WriterThread> threads_;
	ErrorCodeInfo errorInfo_;
    std::string scriptTableInsert_;

	SynchronizedQueue<std::vector<ConstantSP>*> unusedQueue_;
    friend class PytoDdbRowPool;
    PytoDdbRowPool *pytoDdb_;
    Mode mode_;
    std::function<void(ConstantSP)> callbackFunc_;
    RWLock insertRWLock_;

    bool enableStreamTableTimestamp_;
public:
    PytoDdbRowPool * getPytoDdb(){ return pytoDdb_;}
};

}

#endif //MUTITHREADEDTABLEWRITER_H_