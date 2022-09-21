#include<iostream>
#include<vector>
#include<string>
#include "../Sec1/Sales_item.h"

int main(){
    Sales_item item1, item2;
    while(cin >> item1 >> item2){
        try{
            // 执行添加两个item对象的代码
            // 添加失败则抛出runtim_error异常
        } catch(runtime_error err) {
            // 提醒isbn不一致，询问是否重新输入
        }
    }
}