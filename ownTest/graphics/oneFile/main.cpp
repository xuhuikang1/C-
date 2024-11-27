#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Shape {
public:
    Shape(){};
    virtual void draw() = 0;
    virtual double area() = 0;
};


class Circle : public Shape {
public:
    Circle(double radius): radius_(radius) {};
    void draw() override {
        std::cout << "这是一个半径："+std::to_string(radius_)+" 的圆" << std::endl;
    };
    double area() override {
        return 3.1415926*radius_ * radius_;
    };
private:
    double radius_;
};

class Rectangle : public Shape{
    private:
        double length;
        double width;
    public:
        Rectangle(double length,double width):length(length),width(width){};
        void draw() override{
            std::cout << "这是一个长："+std::to_string(length)+",宽："+std::to_string(width)+"的矩形" << std::endl;
        };
        double area() override{
            return length*width;
        };
         ~Rectangle(){};

};



class Canvas{
    private:
        int capacity;
        int shapeNum=0;
        Shape** shapeList;
    public:
        Canvas(int cap):capacity(cap){
            init();
        };
        void setShape(Shape* shape){
            if(shapeNum>capacity-1){
                std::cout << "容量已满" << std::endl;
            }else{
                shapeList[shapeNum]=shape;
                shapeNum++;
            };
        };
        
        void drawAll(){
            for(int index=0;index<shapeNum;++index){
                shapeList[index]->draw();
            };
        }
        double totalArea(){
            double sum=0;
            for(int index=0;index<shapeNum;index++){
                sum += shapeList[index]->area();
            };
            return sum;
        }
    private:
        void init(){
            shapeList = new Shape*[capacity];
            for(int i=0;i<capacity;i++){
                shapeList[i]=nullptr;
            };
            std::cout << "初始化成功" << std::endl;
        }
};

int main(){
    Canvas Canvas1(100);
    std::cout << "---------------------直接调用类方法--------------------" << std::endl;
    Rectangle* Rectangle1 = new Rectangle(5.0,2.0);
    Rectangle* Rectangle2 = new Rectangle(10.0,2.0);
    Rectangle1 -> draw();
    double recArea = Rectangle1 -> area();
    std::cout << "2*5 的矩形面积：" +std::to_string(recArea) << std::endl;
    Rectangle2 -> draw();
    recArea = Rectangle2 -> area();
    std::cout << "2*10 的矩形面积：" +std::to_string(recArea) << std::endl;
    Circle* Circle1 = new Circle(2.0);
    Circle* Circle2 = new Circle(4.0);
    Circle1 -> draw();
    Circle2 -> draw();
    double cirArea = Circle1 -> area();
    std::cout << "半径为 2 的圆面积：" +std::to_string(cirArea) << std::endl;
    cirArea = Circle2 -> area();
    std::cout << "半径为 4 的圆面积：" +std::to_string(cirArea) << std::endl;
    Canvas1.setShape(Rectangle1);
    Canvas1.setShape(Circle1);
    Canvas1.setShape(Rectangle2);
    Canvas1.setShape(Circle2);
    std::cout << "---------------------调用Canvas类方法--------------------" << std::endl;
    Canvas1.drawAll();
    double areaAll = Canvas1.totalArea();
    std::cout << "所有图形的面积为：" +std::to_string(areaAll) << std::endl;

}