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
        // constructor function
        Person() = default;
        Person(const string &name, const string &add){
            strName = name;
            strAddress = add;
        }
        Person(std::istream &is) { is >> *this; }
    
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