// 作业题3.24
#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(){
    vector<int> vInt;
    int iVal;
    cout << "输入一组数字： " << endl;
    while(cin >> iVal)
        vInt.push_back(iVal);
    if(vInt.cbegin() == vInt.cend()){
        cout << "无任何元素！" << endl;
        return -1;
    }
    cout << "相邻两项的和依旧是： " << endl;
    for(auto it=vInt.cbegin(); it != vInt.cend()-1; it++){
        cout << (*it + *(++it)) << " ";             // 这里有一个自加操作
        if(it - vInt.cbegin() + 1 % 10 == 0)
            cout << endl;                           // 控制一行输入5个数字
    }
    // 若元素个数为奇数，直接输出最后一个元素
    if(vInt.size() % 2 != 0)
        cout << *(vInt.cend() - 1);
    return 0;

}


