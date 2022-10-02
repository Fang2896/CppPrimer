#include<iostream>
#include<stdexcept>
using namespace std;

istream & f(istream & in){
    int v;
    while(in >> v, !in.eof()){
        if(in.bad())
            throw runtime_error("IOstream error!");
        if(in.fail()){
            cerr << "Data error, pls retry!" << endl;
            in.clear();
            in.ignore(100, '\n');
            continue;
        }
        cout << v << endl;
    }
    in.clear();
    return in;
}   

int main(){
    cout << "Pls input some integers, push Ctrl+z to finish. " << endl;
    f(cin);
    return 0;
}