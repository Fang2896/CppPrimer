#include<iostream>

using namespace std;

int main()
{
    const int i = 42;               
    auto j = i;                 // j 是整数
    const auto &k = i;          // k是整型常量引用
    auto *p = &i;               // p是指向整型常量的指针
    const auto j2 = i, &k2 = i; // j2是整型常量，k2是整型常量引用
}