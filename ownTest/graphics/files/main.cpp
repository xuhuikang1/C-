#include "Rectangle.h"
#include "Circle.h"
#include <iostream>
#include <string>
int main(){
    Rectangle Rectangle1(5.0,2.0);
    Rectangle1.draw();
    double recArea = Rectangle1.area();
    std::cout << "2*5 的矩形面积：" +std::to_string(recArea) << std::endl;
    Circle Circle1(2.0);
    Circle1.draw();
    double cirArea = Circle1.area();
    std::cout << "半径为 2 的圆面积：" +std::to_string(cirArea) << std::endl;
}