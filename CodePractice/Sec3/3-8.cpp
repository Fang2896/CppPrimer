#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main()
{
    vector<string> vString;
    string s;
    char cont = 'y';
    cout << "Pls enter a word: " << endl;
    while(cin >> s){
        vString.push_back(s);
        cout << "Continue or not? (y or n) " << endl;
        cin >> cont;
        if(cont != 'y' && cont != 'Y')
            break;
        cout << "Pls enter next word: " << endl;
    }
    cout << "Transfer to upper alpha: " << endl;
    for (auto &wo : vString){
        for(auto &cha : wo)
            cha = toupper(cha);
        cout << wo << endl;
    }
    return 0;

}


