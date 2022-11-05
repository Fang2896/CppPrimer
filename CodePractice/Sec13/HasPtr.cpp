#include<iostream>
#include<string>

using namespace std;

class HasPtr {
public:
    HasPtr(const string &s = string()) :
     ps(new string(s)), i(0) { }

    HasPtr(const HasPtr &p) :           
     ps(new string(*p.ps)), i(p.i) { }  // 拷贝构造
    HasPtr& operator=(const string&);   // 拷贝赋值
    HasPtr& operator=(const string&);   // 赋予新string
    string& operator*();                // 解引用
    ~HasPtr();
private:
    string *ps;
    int         i;
};

HasPtr::~HasPtr() {
    delete ps;          // 释放string 内存
}

inline
HasPtr& HasPtr::operator=(const HasPtr &rhs) { 
    auto newps = new string(*rhs.ps);   // 拷贝指针指向的对象
    delete ps;                          // 销毁原string
    ps = newps;
    i = rhs.i;
    return *this;
}

HasPtr& HasPtr::operator=(const string &rhs) {
    *ps = rhs;
    return *this;
}

string& HasPtr::operator*() {
    return *ps;
}

int main(int argc, char **argv) {
    // test

    // test
    return 0;
}