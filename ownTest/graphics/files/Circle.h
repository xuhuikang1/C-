#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
class Circle : public Shape{
    private:
        double radius;
    public:
        Circle(double radius);
        void draw() override;
        double area() override;
        ~Circle();
};

#endif //CIRCLE_H