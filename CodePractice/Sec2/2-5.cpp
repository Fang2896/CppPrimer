#include<iostream>

using namespace std;

int main()
{
    const int i = 42;               
    auto j = i;                 // j ������
    const auto &k = i;          // k�����ͳ�������
    auto *p = &i;               // p��ָ�����ͳ�����ָ��
    const auto j2 = i, &k2 = i; // j2�����ͳ�����k2�����ͳ�������
}