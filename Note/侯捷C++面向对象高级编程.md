# 侯捷C++面向对象高级编程

[TOC]





## （上）



## （下）

### 1. conversion function 

```c++
class Fraction{
public:
    Fraction(int num, int den =  1)
        : m_numerator(num), m_denominator(den) { }
    operator double() const {
        return (double)(m_numerator / m_denominator)
    }
private:
    int m_numerator;
    int m_denominator;
}
```

### 2. non-explicit-one-argument ctor

```c++
class Fraction{
public:
    Fraction(int num, int den =  1)
        : m_numerator(num), m_denominator(den) { }
    operator double() const {
        return (double)(m_numerator / m_denominator)
    }
    Fraction operator+(const Fractor& f) {
        return Fraction(...)
    }
private:
    int m_numerator;
    int m_denominator;
}
```

有俩条路径可行，报错！

要是加上explicit:
```c++
lass Fraction{
public:
    explicit Fraction(int num, int den =  1)
        : m_numerator(num), m_denominator(den) { }
    // 其他一致
}

Fraction f(3,5);
Fraction d2 = f + 4;	// 报错，因为有explicit，两边都得Fraction
```

**注意：explicit基本只在构造函数的前面用**



### 3. pointer-like class

```c++
template<class T>
class shared_ptr {
public:
    T& operator*() const
        { return *px;}
    T* operator->() const 
    	{ return px; }
    shared_ptr(T* p) : px(p) { }
private:
    T* 		px;
    long*	pn;
}
```

注意行为：

```c++
shared_ptr<Foo> sp(n);
Foo f(*sp);
sp->method;	// == px->method;
```

**->箭头作用的东西，得到的东西会继续作用下去，所以经过替换后，仍然还有一个->**

* 关于迭代器
  是一个更加特别的智能指针！

  ```c++
  T&
  reference operator*() const 
  	{ return (*node).data; }
  T*
  pointer operator->() const
  	{ return &(operator*()); }
  	
  list<Foo>::iterator iter;
  *iter;	// 获得一个Foo obj
  iter->method();
  // 意思是调用Foo::method
  // 相等于(*iter).method
  // 相当于(&(*iter))->method;
  ```



### 4. function-like class

仿函数

像函数的类。略



### 5. 关于namespace

做测试的时候，可以考虑将不同的测试函数写在不同的命名空间里面，方便命名，而且互不冲突！



### 6. class template 类模板

```c++
template<typename T>
class complex {
public:
    complex (T r = 0, T i = 0)
        : re (r), im(i) { }
    complex& operator += (const complex&);
    T real () const { return re; }
    T imag () const { return im; }
private:
    T re, im;
}

// 使用
complex<double> c1;	// 要指明type类型
```



### 7. function template 函数模板

```c++
template<class T>
inline
const T& min(const T& a, const T& b) {
    return b < a ? b : a;
}

// 使用
// 不必指明type,会自动推算type
// 从而调用相应class的重载（如果有）的操作符
```

### 8. member template 成员模板

就是外面有模板，里面也有模板

```C++
template<class T1, class T2>
struct pair{
    ...
	T1 first;
	T2 second;
    pair() : first(T1()), second(T2()) { }
    pair(const T1& a, const T2& b) first(a), second(b) { }
    
    template<class U1, class U2>
	pair(const pair<U1, U2>& p) :
    	first(p.first), second(p.second) { }	//     
};
class Base1 { };
class Derived1 : public Base1 { };
class Base2 { };
class Derived2 : public Base2 { };

pair<Derived1, Derived2> p;
pair<Base1, Base2> p2(p);
pair<Base1, Base2> p2(pair<Derived1, Derived2>())
```

* 另一个例子：智能指针
  ```c++
  template<typename Tp>
  class shared_ptr : public __shared_ptr<_Tp> {
      ...
  	template<typename _Tp1>
  	explicit shared_ptr(_Tp1* __p)
          : __shared_ptr<_Tp>(__p) { }
  	...
  };
  // 使用
  Base1* ptr = new Derived1;
  shared_ptr<Base1> sptr(new Derived1);
  ```



### 9. specialization 模板特化

```c++
// 一般的泛化
template <class Key>
struct hash { };
// 特化， 如果是char就会用下面这段代码
template<>
struct hash<char> {
  	size_t operator() (char x) const { return x; }  
};
// 特化，如果是int就应用这段代码
template<>
struct hash<int> {
  	...
};
```



### 10. partial specialization 模板偏特化

* 个数上的偏
  ```c++
  template<typename T, typename Alloc=...>
  class vector {
    	...  
  };
  // 偏特化，指定了第一个T为bool类型
  template<typename Alloc=...>
  class vector<bool, Alloc> {
      
  }
  ```

* 范围上的偏

  ```c++
  template<typename T>
  class C {
    	...  
  };
  // 偏特化版本，使用指针就用这一套代码
  template<typename T>
  class C<T*> {
    	...  
  };
  
  ```

  

### 11. template template parameter, 模板模板参数

(注意，在< >里面，class和typename共通！)

```c++
template<typename T, 
		typename <typename T>
      		class Container
		>
class XCls {
private:
    Container<T> c;
public:
    ...
};
// 应用
XCls<string, list> mylst1;	// 错误！标准库容器不能这么用
// 正确应用
template<typename T>
using Lst = list<T, allocator<T>>;
XCls<string, Lst> mylst2;
// 传入string，string作为第二个模板模板参数的类型！
```

### 12. 关于C++标准库

### 13. 三个主题

* variadic template
  数量不定的模板参数

  ```c++
  void print() {
      // 0个的版本！当参数为0则调用这个版本！
  }
  
  template<typename T, typename... Types>
  void print(const T& firstArg, const Types&... args) {
      cout << firstArg << endl;
      print(args...);
  }
  ```

  在variadic template中，`sizeof...(args)` 返回参数的数量！

  * `...` : 就是所谓的pack（包）
    * 用于template parameters就是模板参数包 template parameter pack
    * 用于function parameter types就是function parameter types pack 函数参数类型包
    * 用于function parameters 就是function parameters pack，函数参数类型包

* `auto`
  略

* range base `for`
  ```c++
  fpr(decl : coll) {
      statement
  }
  ```

### 14. Reference

感觉就是`int* const ptr;` 即，常量指针的解引用就是引用！因为引用不能变，常量指针指向的也不能变，但是引用可以改变值，常量指针指向的值也可以改变 ！

reference通常不用于声明变量，而是用于参数类型parameters type和返回类型 return type的描述。

* 函数签名：

  函数名字+参数
  

### 15. 复合、继承关系下的构造和析构

* Inheritance 继承关系下的构造和析构

  * 构造由内而外
    Derived的构造函数首先调用Base的default构造函数，然后才执行自己
    `Derived::Derived(...) : Base() { ... };`

  * 析构由外而内

    Derived的析构函数首先执行自己，然后才调用Base的析构函数

    `Derived::~Derived(...) { ... ~Base() };`

* Composition（复合） 关系下的构造和析构

  * 构造由内而外
    Container的构造函数首先调用Component的default构造函数，然后才执行自己
    `Container::Container(...) : Component() { ... };`
  * 析构由外而内
    Container的析构函数首先执行自己，然后才调用Component的析构函数
    `Container::~Container(...) { ... ~Component() };`

* Inheritance + Composition关系下的构造和析构
  * 构造由内而外
    Derived的构造函数首先调用Base的default构造函数，然后调用Component的default构造函数，然后执行自己
  * 析构由外而内
    Derive的析构函数首先执行自己，然后调用Component的析构函数，然后调用Base的析构函数

### 16. 关于vptr和vtbl

虚指针 / 虚表

动态绑定！

虚函数很有用



### 17. 关于Dynamic Binding

* 谈谈const
  常量成员函数

  当成员函数的const和non-const版本同时存在，const object只能调用const版本！
  non-const object只能调用non-const 版本！



### 18，19. 关于new和delete

* new
  先分配memory，再调用ctor
* delete
  先调用dtor，再释放memory

* 如何重载`::operator new, ::operator delete, ::operator new[], ::operator delete[]`

(重载的是全局的东西)

* 重载`member operator new/delete`
* 重载``member operator new[]/delete[]`

* 示例：
  ::new
  ::delete
  强制调用全局的函数

  
