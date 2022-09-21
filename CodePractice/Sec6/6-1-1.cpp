//func.cpp---包含头文件：声明头文件、标准库
#include “test.h”       //作用是让编译器检查声明语句与定义语句是否相同
#include <iostream>     //必要，若没有，编译的时候std::cout未声明
void fun()
{
    std::cout<<"分离式编译"<<std::endl;
}