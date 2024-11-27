#ifndef SHAPE_H
#define SHAPE_H
class Shape
{
private:
    /* data */
public:
    Shape(/* args */);
    virtual void draw()=0;
    virtual double area() = 0;
    ~Shape();
};


#endif // SHAPE_H
