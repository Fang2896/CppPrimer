# 侯捷C++面向对象高级编程

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

