#include<iostream>
#include<list>
#include<forward_list>
#include<vector>

using namespace std;

int main(){
    forward_list<int> fint = {5,1,2,3,4,5,6,7,8,9};
    cout << *(++fint.begin()) << endl;
    
    return 0;
    

}