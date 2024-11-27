#include "Rectangle.h"
#include <iostream>
#include <string>

Rectangle::Rectangle(double length,double width):length(length),width(width){};
Rectangle::~Rectangle(){};
void Rectangle::draw(){
    std::cout << "这是一个长："+std::to_string(length)+",宽："+std::to_string(width)+"的矩形" << std::endl;
    // std::cout << "这是一个矩形" << std::endl;
};
double Rectangle::area(){
    return length*width;
};