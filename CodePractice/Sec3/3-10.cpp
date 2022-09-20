#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main()
{
    string text = "dawdawdawdawdaw";
    char sought = 'w';
    // Binary search
    // text 必须是有序的
    // beg和end表示我们搜索的范围
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