#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"

class Rectangle : public Shape{
    private:
        double length;
        double width;
    public:
        Rectangle(double length,double width);
        void draw() override;
        double area() override;
         ~Rectangle();

};
#endif //RECTANGLE_H