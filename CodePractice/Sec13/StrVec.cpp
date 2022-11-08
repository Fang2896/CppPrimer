#include<iostream>
#include<memory>

using namespace std;

class StrVec {
public:
    StrVec():
     elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const StrVec&);              // 拷贝构造函数
    StrVec &operator=(const StrVec&);   // 拷贝赋值函数
    ~StrVec();
    void push_back(const std::string&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; } 
    // ...

private:
    static std::allocator<std::string> alloc;
    void chk_n_alloc() 
        { if (size() == capacity()) reallocate(); }
    std::pair<std::string*, std::string*> alloc_n_copy
        (const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

void StrVec::push_back(const std::string& s) {
    chk_n_alloc();
    alloc.construct(first_free++, s);   // 由于allocator分配的内存是未构造的，所以调用construc
}
pair<string*, string*>
StrVec::alloc_n_copy(const string *b, const string *e) {
    auto data = alloc.allocate(e-b);
    return {data, uninitialized_copy(b, e, data)};
}
void StrVec::free() {
    if(elements) {
        for(auto p = first_free; p!=elemts; )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}
StrVec::StrVec(const StrVec &s) {
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}
Str::~StrVec() { free(); }
StrVec &StrVec::operator=(const StrVec &rhs) {
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}
void Str::reallocate() {
    auto newcapacity = size() ? 2*size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;    // 指向新数组下一个空闲位置
    auto elem = elements;   // 指向旧数组下一个元素
    for(size_t i = 0; i != size(); ++i) 
        alloc.construct(dest++, std::move(*elem++));
    free(); // 移动完元素则释放旧内存空间
    elements = newdata;
    first_free = dest;
    cap = elements + newcapacity;
}