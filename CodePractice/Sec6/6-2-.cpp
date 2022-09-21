#include<iostream>
#include<vector>
#include<string>

string::size_type find_char(const string &s, char c, string::size_type &occurs)
{
    auto ret = s.size();    // 第一次出现的位置
    occurs = 0;
    for(decltype(ret) i = 0; i != s.size(); ++i) {
        if(s[i] == c){
            if(ret == s.size())
                ret = i;
            ++occurs;
        }
    }
    return ret;
}