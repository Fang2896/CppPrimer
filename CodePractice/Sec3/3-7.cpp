#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    vector<string> vStr;
    string str;
    char cont = 'y';
    while(cin >> str){
        vStr.push_back(str);
        cout << "Continue or not? (y or n) " << endl;
        cin >> cont;
        if(cont != 'y' && cont != 'Y')
            break;
    }
    for(auto i : vStr){
        cout << i << " ";
    }
    cout << endl;
}