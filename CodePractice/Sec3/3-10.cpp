#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main()
{
    string text = "dawdawdawdawdaw";
    char sought = 'w';
    // Binary search
    // text �����������
    // beg��end��ʾ���������ķ�Χ
    auto beg = text.begin(), end = text.end();
    auto mid = beg + (beg-end)/2;
    while(mid!=end && *mid!=sought){
        if(sought < *mid)
            end = mid;
        else
            beg = mid + 1;
        mid = beg + (end-beg)/2;
    }
}