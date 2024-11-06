#include<dynamicTest.h>
#include<staticTest.h>
#include<iostream>


int main(int argc, char const *argv[])
{
    int addRes = op1::add(1,2);
    std::cout << "1 op1 add 2 res is: " << addRes << std::endl;
    int subRes = op2::add(addRes,1);
    std::cout << "addRes op2 add 1 res is: " << subRes << std::endl;
    return 0;
}
