#include<iostream>
#include<vector>
#include<string>



class Window_mgr{
public:
    void clear();
};


class Screen {
friend void Window_mgr::clear();

private:
    unsigned height = 0, width = 0;
    unsigned cursor = 0;
    std::string contents;
public:
    Screen() = default;
    Screen(unsigned ht, unsigned wd) : height(ht), width(wd),
        contents(ht*wd, ' ') { }
    Screen(unsigned ht, unsigned wd, char c)
        : height(ht), width(wd), contents(ht*wd, c) { }
public:
    Screen& move(unsigned r, unsigned c){
        cursor = r * width + c;
        return *this;
    }
    Screen& set(char ch){
        contents[cursor] = ch;
        return *this;
    }
    Screen& display(std::ostream& os){
        os << contents;
        return *this;
    }
};

void Window_mgr::clear()
{
    using namespace std;
    Screen myScreen(10, 20, 'X');
    cout << "before clear, the content of myScreen is: " << endl;
    cout << myScreen.contents << endl;
    myScreen.contents = "";
    cout << "after clear, the content is: " << endl;
    cout << myScreen.contents << endl;
}


int main(){
    using namespace std;
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(cout);
    cout << "\n";
    myScreen.display(cout);
    cout<<"\n" << endl;

    Window_mgr w;
    w.clear();
    return 0;

}