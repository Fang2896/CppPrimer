// ��ҵ��3.24
#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main(){
    vector<int> vInt;
    int iVal;
    cout << "����һ�����֣� " << endl;
    while(cin >> iVal)
        vInt.push_back(iVal);
    if(vInt.cbegin() == vInt.cend()){
        cout << "���κ�Ԫ�أ�" << endl;
        return -1;
    }
    cout << "��������ĺ������ǣ� " << endl;
    for(auto it=vInt.cbegin(); it != vInt.cend()-1; it++){
        cout << (*it + *(++it)) << " ";             // ������һ���ԼӲ���
        if(it - vInt.cbegin() + 1 % 10 == 0)
            cout << endl;                           // ����һ������5������
    }
    // ��Ԫ�ظ���Ϊ������ֱ��������һ��Ԫ��
    if(vInt.size() % 2 != 0)
        cout << *(vInt.cend() - 1);
    return 0;

}


