#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Person
{
    private:
        string strName;
        string strAddress;

    public:
        string getName() const { return strName; }
        string getAddress() const { return strAddress; }
}


istream &read(istream &is, Person &per){
    is >> per.strName >> per.strAddress;
    return is;
}

ostream &print(ostream &os, const Person &per){
    os << per.getName() << per.getAddress();
    return os;
}