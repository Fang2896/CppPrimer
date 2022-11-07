#include<iostream>
#include<string>
#include<set>

class Message {
    friend class Folder;
public:
    explicit Message(const std::string &str = ""):
        contents(str) { }
    Message(const Message&);
    Message& operator=(const Message&);
    ~Message();

    void save(Folder&);
    void remove(Folder&);
    // swap函数
    void swap(Message &lhs, Message &rhs) {
        using std::swap;
        for(auto f : lhs.folders)
            f->remMsg(&lhs);
        for(auto f : rhs.folders)
            f->remMsg(&rhs);
        swap(lhs.folders, rhs.folders);
        swap(lhs.contents, rhs.contents);
        for(auto f : lhs.folders)
            f->addMsg(&lhs);
        for(auto f : rhs.folders)
            f->addMsg(&rhs);
    }
private:
    std::string contents;
    std::set<Folder*> folders;
    void add_to_Folders(const Message&);
    void remove_from_Folders();
};

void Message::save(Folder &f) {
    folders.insert(&f);
    f.addMsg(this);
}
void Message::remove(Folder &f) {
    folders.erase(&f);
    f.remMeg(this);
}
// 拷贝控制成员
void Message::add_to_Folders(const Message &m) {
    for(auto f : m.folders)
        f->addMsg(this);
}
Message::Message(const Message &m) : 
    contents(m.contents), folders(m.folders)
{
    add_to_Folders(m);  // 将本消息添加到指向m的Folders中
}
// 析构函数
void Message::remove_from_Folders() {
    for(auto f : folders)
        f->remMsg(this);
}
Message::~Message() {
    remove_from_Folders();
}
// 拷贝赋值运算符, 注意，要使得即使左右两边是同一个Message，拷贝赋值运算符也能正确执行
Message& Message::operator=(const Message &rhs) {
    remove_from_Folders();  // 更新已有folders
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_Folders(rhs);
    return *this;
}

class Folder {
public:
    void addMsg(Message *m) {msgs.insert(m)}
    void remMsg(Message *m) {msgs.erase(m)}
    
private:
    set<Message*> msgs;
};