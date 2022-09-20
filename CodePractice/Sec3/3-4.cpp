// 将每个字符转化为大写字母
// 用for循环处理每一个字符

#include<iostream>
#include<string>
using namespace std;

int main(){
    string s("Hello World!");
    for (auto &c : s){
        c = toupper(c);
    }
    cout << s << endl;
    return 0;
}