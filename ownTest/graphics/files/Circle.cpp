#include "Circle.h"
#include <iostream>
#include <string>

Circle::Circle(double radius):radius(radius){};
Circle::~Circle(){};
void Circle::draw(){
    std::cout << "这是一个半径："+std::to_string(radius)+" 的圆" << std::endl;
}
double Circle::area(){
    return 3.1415926*radius*radius;
}