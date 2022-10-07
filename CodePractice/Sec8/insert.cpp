#include<iostream>
#include<list>
#include<forward_list>
#include<vector>
using namespace std;

int main(){
    vector<int> vInt = {0,1,2,3,4};
    auto vIter = vInt.insert(vInt.begin(), {1,2,3});
    cout << *vIter << endl;
    for(auto &iter : vInt){
        cout << iter ;
    }
    cout << endl;
    
}