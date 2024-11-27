#include <iostream>
#include <string>


using namespace std;


using std::string;




class Book {
public:
    Book(){};
    Book(string n,string a,string p,string pd,string i,bool iB):
        name(n),author(a),publisher(p),publishDate(pd),ISBN(i),isBorrow(iB){};
    string getInfo() {
        string bookInfo;
        string iB = isBorrow ? "true":"false";
        bookInfo += "name: "+name+" author: "+author+" publisher: "+ publisher+" publishDate: "+publishDate+" ISBN: "+ISBN+" isBorrow: "+iB;
        return bookInfo;
    }
    string getISBN(){
        return ISBN;
    }
    bool borrowBook(){
        if(!isBorrow){
            isBorrow=true;
            return true;
        } else {
            return false;
        }
    }
    bool returnBook(){
        if(isBorrow){
            isBorrow=false;
            return true;
        } else {
            return false;
        }
    }
private:
    string name;
    string author;
    string publisher;
    string publishDate;
    string ISBN;
    bool   isBorrow;
};

int main(){
    Book bookList[1000];
    int capacity=1000;
    while(true){
        int operation;
        string name;
        string author;
        string publisher;
        string publishDate;
        string ISBN;
        bool isBorrow;
        bool isBreak=false;
        std::cout << "请选择操作项：" << endl;
        std::cout  << "1.存入书籍" << endl;
        std::cout  << "2.查找书籍" << endl;
        std::cout  << "3.借书" << endl;
        std::cout  << "4.还书" << endl;
        std::cout  << "5.退出" << endl;
        cin >> operation;
        switch(operation){
            case 1:{
                if(capacity==0){
                    cout << "图书馆已满，请扩容";
                }else{
                    isBorrow=false;
                    std::cout  << "请输入书籍信息(名称 作者 出版商 出版日期 ISBN号):" << endl;
                    cin >> name >> author >> publisher >> publishDate >> ISBN;
                    Book newBook(name,author,publisher,publishDate,ISBN,isBorrow);
                    bookList[1000-capacity]=newBook;
                    capacity--;
                }
                break;
            }
            case 2:{
                std::cout << "请输入需要查询的书籍ISBN号:" << endl;
                cin >> ISBN;
                for(int index=0;index <= 1000-capacity;index++){
                    if(bookList[index].getISBN()==ISBN){
                        string bookInfo =bookList[index].getInfo();
                        std::cout << "您查找的书籍信息:"+bookInfo << endl;
                        break;
                    }
                    if(index==1000-capacity){
                        std::cout << "未查到相关书籍信息" << endl;
                    }
                }
                break;
            }
            case 3:{
                std::cout << "请输入需要借阅的书籍ISBN号:" << endl;
                cin >> ISBN;
                for(int index=0;index <= 1000-capacity;index++){
                    if(bookList[index].getISBN()==ISBN){
                        bool borrow =bookList[index].borrowBook();
                        if(borrow){
                            std::cout << "借阅成功" << endl;
                        }else{
                            std::cout << "书籍已经被借阅" << endl;
                        }
                        break;
                    }
                    if(index==1000-capacity){
                        std::cout << "未查到相关书籍信息" << endl;
                    }
                }
                break;
            }
            case 4:{
                std::cout << "请输入需要归还的书籍ISBN号:" << endl;
                cin >> ISBN;
                for(int index=0;index <= 1000-capacity;index++){
                    if(bookList[index].getISBN()==ISBN){
                        bool borrow =bookList[index].returnBook();
                        if(borrow){
                            std::cout << "归还成功" << endl;
                        }else{
                            std::cout << "归还失败,请咨询管理员" << endl;
                        }
                        break;
                    }
                    if(index==1000-capacity){
                        std::cout << "未查到相关书籍信息" << endl;
                    }
                }
                break;
            }
            case 5:{
                isBreak=true;
                break;
            }
            default: {
                // 
            }
        }
        if(isBreak){
            std::cout <<"欢迎使用" << endl;
            break;
        }
    }
    return 0;
};
