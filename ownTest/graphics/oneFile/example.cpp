#include "example.h"


Constant* Constant::getType() {
    return new DataType("DataType(" + name_ + ")");
}