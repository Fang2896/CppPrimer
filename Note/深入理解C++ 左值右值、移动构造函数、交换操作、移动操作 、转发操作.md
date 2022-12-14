# 深入理解C++ 左值右值、移动构造函数、交换操作 `swap`、移动操作 `std::move` 、转发操作 `std::forward`

---

*本文基于C++ primer。基本上是对C++ primer相关内容的一个摘录和总结。仅供个人(M1kanN)学习使用*

---

> 简介：
>
> string类的拷贝有时候是不必要的。所以C++11新标准库引入了两种机制，我们可以避免对string的拷贝。首先是移动构造函数，标准库保证“移后源”(moved-from) string仍然是一个有效、可析构的状态。可以理解为，只是对指向原理啊string的指针进行了拷贝，而不是为字符分配内存空间，然后拷贝字符。
>
> 第二个机制是叫 `move` 的标准库函数。定义在`utility` 头文件中。目前我们只需要理解两个关键点：首先，当reallocate在新内存中构造string时，它必须调用`move`来表示希望使用string 的移动构造函数。如果没有则会使用拷贝构造函数。再者，通常不用`move`而是直接用`std::move` 。   ---- 469 Page of *C++ Primer*



## Sec4 基础

### 4.1 基础

#### 4.1.1 基本概念

* **左值和右值：**
  C++的表达式只有两种：左值(lvalue)和右值(rvalue)。

  * **归纳：当一个对象被用作右值的时候，用的是对象的值（内容）。当对象被用作左值的时候，用的是对象的身份（内存中的位置）。**
  * 需要右值的地方可能用`std::move`来将左值当成右值用，但是绝不能把右值当左值用！
  * 用到左值的几个熟悉的运算符：
    * 赋值运算符需要一个（非常量）左值作为其左侧的运算对象，得到的结果也是一个左值
    * 取地址运算符作为一个左值运算对象，返回一个指向该运算对象的指针，这个指针是一个右值。
      **(& 作用左值，返回右值)**
    * 内置解引用运算符、下标运算符、迭代器解引用运算符、string和vector的下标运算符的求值结果都是左值。
      **(\* 作用右值，返回左值)**
    * 内置类型和迭代器的递增递减运算符用于左值运算对象。前置版本所得结果也是左值。

* 粗略总结：

  * 左值右值：
    `var = 4`

    * 左值是可寻址的变量，有持久性
    * 右值一般是不可寻址的常量，或在表达式求值过程中创建的无名临时对象，短暂性的

    **左值和右值主要的区别之一是左值可以被修改，而右值不能**

* 很详细的一篇博文翻译参考：
  [理解 C/C++ 中的左值和右值](https://nettee.github.io/posts/2018/Understanding-lvalues-and-rvalues-in-C-and-C/)



## Sec13 拷贝控制

### 13.6 对象移动

​	移动而非拷贝可以大幅提升性能。有时候从就内存将元素拷贝到新内存是不必要的，更好的方式是移动元素。另一个原因是源于IO类或者`unique_ptr`这样的类。这些类都包含不能被共享的资源（如指针或者IO缓冲）。因此这些类型的对象不能拷贝但是可以移动。

#### 13.6.1 右值引用

​	为了支持移动操作，新标准引入了一种新的引用类型 -- 右值引用(rvalue reference)。右值引用就是必须绑定到右值的引用。通过`&&`来实现。**右值引用有一个重要的性质：只能绑定到一个将要销毁的对象。**

* **左值持久、右值短暂：**
  右值要么是字面常量、要么是表达式在求职过程中创建的临时对象。

  * 所引用的对象将要被销毁
  * 该对象没有其他用户

  这两个特性意味着，**使用右值引用的代码可以自由地接管所引用的对象的资源。**

* **变量是左值：**

  **因为变量表达式都是左值，所以我们不能将一个右值引用绑定到一个右值引用类型的变量上。**

  ```c++
  int &&rr1 = 42;		// 正确
  int &&rr2 = rr1;	// 错误，表达式rr1是左值
  ```

* **标准库`move`函数**： 
  `move`可以用来获得绑定到左值上的右值引用。即，**显示地将一个左值转换为对应的右值引用类型。**

  ```c++
  int &&rr3 = std::move(rr1);	// 正确
  ```

  注意：使用move就意味着承诺，除了对rr1赋值或者销毁它以外，我们将不再使用它。在调用move后，我们不能对移后源对象的值做任何假设。



#### 13.6.2 移动构造函数和移动赋值运算符

​	移动构造函数的第一个参数应该是该类类型的一个引用。不同于拷贝构造函数**，这个引用参数在移动构造函数中是一个右值引用**。
​	除了完成资源移动，移动构造函数还需要保证移后源对象处于这样一个状态---销毁它是无害的。

* 例子：
  ```c++
  StrVec::StrVec(StrVec &&s) noexcept			// 表示移动操作不应该抛出任何异常
      : elements(s.elements), first_free(s.first_free), cap(s.cap)
  {	
  	// 令s进入无害状态。（运行析构函数是安全的）
  	s.elements = s.first_free = s.cap = nullptr;        
  }
  ```

  注意：如果我们忘记改变`s.frist_free`，s的析构函数会把我们需要的资源释放掉！

* **移动操作、标准库容器和异常：**

  因为移动操作通常不分配任何资源，所以移动操作通常不会抛出任何异常
  `noexcept`就是承诺函数不抛出异常的方法。**出现在参数列表和初始化列表开始的冒号之间。**

  * 为什么要在移动构造函数中用 `noexcept` ?
    如果是拷贝构造函数，如果发生异常，旧元素不变，只需要释放新元素即可。但是在移动构造函数如果发生异常，会导致新旧数据的不一致性，即旧空间中的移动源元素已经改变，而新空间中未构造的元素还不存在，此时vector将不能保证自身保持不变。
    为了避免这种问题，除非vector知道元素类型的移动构造函数不会抛出异常，**否则在重新分配内存中，它必须使用拷贝构造函数而不是移动构造函数。**如果我们希望vector在重新分配内存这类情况用移动，则必须指定`noexcept`！

* **移动赋值运算符：**
  与移动构造函数一样，如果我们的移动复制运算符不抛出任何异常，则我们应该将它标记为`noexcept`

  ```c++
  StrVec &StrVec::operator=(StrVec && rhs) noexcept
  {
      // 直接检测自赋值
      if(this != &rhs) {
          free();	// 释放已有元素！
          elements = rhs.elements;
          first_free = rhs.first_free;
          cap = rhs.cap;
          // 将rhs置于可析构状态
          rhs.elements = rhs.first_free = rhs.cap = nullptr;
      }
      return *this;
  }
  ```

* **移后源对象必须可析构：**
  除了将移后源对象置为析构安全的状态之外，移动操作还必须保证对象仍然是有效的。

* **合成的移动操作：**
  如果一个类定义了自己的拷贝构造函数、拷贝赋值运算符或者析构函数，编译器就不会为它合成移动构造函数和移动赋值函数了。
  只有一个类没有定义任何自己版本的拷贝控制成员，且类的每个非`static`数据成员都可以移动时，编译器才会为它合成移动构造函数或移动赋值运算符。

  ```c++
  struct X {
      int i;	// 可移动
      std::string s;	// string定义了自己的移动操作
  };
  struct hasX {
      X men;	// X有合成的移动操作
  };
  X x, x2 = std::move(x);	// 使用合成的移动构造函数
  hasX hx, hx2 = std::move(hx);	// 使用合成的移动构造函数
  ```

* **移动右值、拷贝左值：**
  如果又有移动又有拷贝构造函数，则用普通函数匹配规则来确定使用哪个构造函数！

* **如果没有移动构造函数，右值也被拷贝**
  即使用move来调用也一样。

* **拷贝并交换赋值运算符和移动操作：**
  HasPtr定义了一个拷贝并交换赋值运算符，它是函数匹配和移动操作间相互关系的一个很好的实力。如果我们为此类添加一个移动构造函数，**它实际上也会获得一个移动构造运算符**

  ```c++
  class HasPtr {
  public:
  	HasPtr(HasPtr &&p) noexcept : ps(p.ps), i(p.i) { p.ps = 0; }
      HasPtr& operator=(HasPtr rhs) { swap(*this, rhs); return *this; }
  }
  ```

  ```c++
  hp = hp2;	// hp2是左值。hp2通过拷贝构造函数来拷贝
  hp = std::move(hp2);	// 移动构造函数移动hp2
  ```

  * 不管使用的是拷贝构造函数还是移动构造函数，赋值运算符的函数体都swap两个运算对象的状态。rhs的指针将指向原来左侧对象所拥有的string。当rhs离开其作用域后，这个string将会被销毁。





## Sec16 模板与泛型编程

### 16.2 模板实参推断

#### 16.2.6 理解 std::move

```c++
template <typename T>
typename remove_reference<T>::type&& move(T&& t) {
    return static_cast<typename remove_reference<T>::type&&>(t);
}
```

#### 16.2.7 转发

某些函数需要将其一个或多个实参连同类型不变地转发给其他函数，在此情况下，我们需要保持被转发实参的所有性质。包括实参类型是非是const的以及实参是左值还是右值。

* 例子：
  ```c++
  template <typename F, typename T1, typename T2>
  void flip1(F f, T1 t1, T2 t2) {
      f(t2, t1);
  }
  void f(int v1, int &v2) {
      cout <, v1 << "  " << ++v2 << endl;
  }
  
  f(42, i);
  flip1(f, j, 42);
  ```

* 在调用中使用`std::forward` 保持类型信息
  ```c++
  template <typename Type> intermediary(Type &&arg) {
      finalFcn(std::forwar<Type>(arg));
      // ...
  }
  ```

  

