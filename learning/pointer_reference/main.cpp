#include <iostream>
#include <string.h>
#include <string>

int main(){
    //使用指针来进行复用
    std::cout << "---------------------------一级指针-----------------------------" << std::endl;
    std::string s1 = "test";
    std::string *s2 = &s1;
    std::cout << "s1的值" ;
    std::cout << s1 << std::endl;
    std::cout << "s1的地址" ;
    std::cout << &s1 << std::endl;
    std::cout << "s2的值" ;
    std::cout << *s2 << std::endl;
    std::cout << "s2的地址" ;
    std::cout << &s2 << std::endl;
    *s2 = "test1";
    std::cout << "s1的值" ;
    std::cout << s1 << std::endl;
    std::cout << "s1的地址" ;
    std::cout << &s1 << std::endl;
    std::cout << "s2的值" ;
    std::cout << *s2 << std::endl;
    std::cout << "s2的地址" ;
    std::cout << &s2 << std::endl;

    //引用
    std::cout << "---------------------------引用-----------------------------" << std::endl;
    std::string s3 = "test";
    std::string& s4 = s3;
    std::cout << "s3的值" ;
    std::cout << s3 << std::endl;
    std::cout << "s3的地址" ;
    std::cout << &s3 << std::endl;
    std::cout << "s4的值" ;
    std::cout << s4 << std::endl;
    std::cout << "s4的地址" ;
    std::cout << &s4 << std::endl;
    s4 = "test2";
    std::cout << "s3的值" ;
    std::cout << s3 << std::endl;
    std::cout << "s3的地址" ;
    std::cout << &s3 << std::endl;
    std::cout << "s4的值" ;
    std::cout << s4 << std::endl;
    std::cout << "s4的地址" ;
    std::cout << &s4 << std::endl;

    std::cout << "---------------------------const保证原始值不会被修改-----------------------------" << std::endl;
    std::string s5 = "test";
    const std::string *s6 = &s5;
    const std::string& s7 = s5;
    std::cout << "s5的值" ;
    std::cout << s5 << std::endl;
    std::cout << "s5的地址" ;
    std::cout << &s5 << std::endl;
    std::cout << "s6的值" ;
    std::cout << *s6 << std::endl;
    std::cout << "s6的地址" ;
    std::cout << &s6 << std::endl;
    std::cout << "s7的值" ;
    std::cout << s7 << std::endl;
    std::cout << "s7的地址" ;
    std::cout << &s7 << std::endl;
    //*s6 = "test1"; s7 = "1";不允许操作
    //s5原始值可修改
    s5 = "test1";
    std::cout << "s5的值" ;
    std::cout << s5 << std::endl;
    std::cout << "s5的地址" ;
    std::cout << &s5 << std::endl;
    std::cout << "s6的值" ;
    std::cout << *s6 << std::endl;
    std::cout << "s6的地址" ;
    std::cout << &s6 << std::endl;
    std::cout << "s7的值" ;
    std::cout << s7 << std::endl;
    std::cout << "s7的地址" ;
    std::cout << &s7 << std::endl;


    return 0;
}
