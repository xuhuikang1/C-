#include <string>


class Constant {
public:
    Constant(const std::string &name): name_(name) {}
    Constant* getType();
    std::string getName() { return name_; }
public:
    std::string name_;
};


class Int: public Constant {
public:
    Int(): Constant("Int") {}
};


class DataType : public Constant {
public:
    DataType(const std::string &type) : Constant(type) {}
};