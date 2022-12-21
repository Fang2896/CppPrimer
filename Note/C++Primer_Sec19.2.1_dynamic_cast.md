# C++ Primer

## Sec19 特殊工具与技术

### 19.2 运行时类型识别

**运行时类型识别（run-time type identification，RTTI）**的功能由两个运算符实现：

*   `typeid`运算符
    用于返回表达式的类型。
*   `dynamic_cast`运算符
    用于将基类的指针或引用安全地转换成派生类的指针或引用。

当我们将这两个运算符用于某种类型的指针或引用，并且该类型含有虚函数时，运算符将使用指针或引用所绑定对象的动态类型。

**适用情况：想适用基类对象的指针或引用执行某个派生类操作，但该操作不是虚函数。** （当然最好使用虚函数）

#### 19.2.1 `dynamic_cast` 运算符

* 使用形式：
    ```c++
    dynamic_cast<type*> e;	// 有效的指针
    dynamic_cast<type&> e;	// 左值
    dynamic_cast<type&&> e; // 不能为左值
    ```

    其中，type必须是一个类类型，并通常情况下类型需要含有虚函数。

    *   e的类型必须符合三个条件中的一个
        1.   e的类型是目标type的公有派生类
        2.   e的类型是目标type的公有基类
        3.   e的类型就是目标类型

    转换失败返回0。若转换目标是引用类型，且转换失败，则抛出bad_cast异常。

* 指针类型的`dynamic_cast`
    例子：`Base`至少含有一个虚函数，`Derived`是`Base`的公有派生类。`bp`为指向`Base`的指针，则我们可以将`bp`转换为指向`Derived`的指针（向下转换）

    ```c++
    if(Derived *dp = dynamic_cast<Derived*> (dp)) {
        // 使用dp指向的Derived对象
    } else {
        // 使用dp指向的Base对象
    }
    // 这样些可以同时完成类型转换和条件检查
    ```

    注意：我们可以对一个空指针进行转换！条件部分执行dynamic_cast的操作可以确保类型转换和结果检查在同一条表达式中完成！

* 引用类型的`dynamic_cast`
    转换失败返回bad_cast异常。

    ```c++
    void f(const Base &b) {
        try {
            const Derived &d = dynamic_cast<const Derived&> (b);
          	// 使用引用对象
        } catch (bad_cast) {
            // 失败情况
        }
    }
    ```

* 转换情况：

    *   向上转型：
        派生类指针或引用类型转换为其基类类型。本身就是安全的，尽管可以使用`dynamic_cast`进行转换，但这是没必要的， 普通的转换已经可以达到目的，**毕竟使用`dynamic_cast`是需要开销的**。

    *   `dynamic_cast` 与继承层次的指针
        向下转型有两种情况：

        1.   基类指针所指对象是派生类类型的，这种转换是安全的

        2.   基类指针所指对象为基类类型，在这种情况下`dynamic_cast`在运行时做检查，转换失败，返回结果为0

             （这就是为什么CMU15-445第一个项目用`dynamic_cast`的原因）

    *   `dynamic_cast`和引用类型
        可以使用`dynamic_cast`将基类引用转换为派生类引用。引用的向上转换总是安全的。**与指针不同的是，并不存在空引用，所以引用的dynamic_cast检测失败时会抛出一个bad_cast异常：**

* 注意事项：

    *   使用dynamic_cast转换的Base类至少带有一个虚函数
        当一个类中拥有至少一个虚函数的时候，编译器会为该类构建出一个虚函数表（virtual method table），虚函数表记录了虚函数的地址。如果该类派生了其他子类，且子类定义并实现了基类的虚函数，那么虚函数表会将该函数指向新的地址。虚表是C++多态实现的一个重要手段，也是dynamic_cast操作符转换能够进行的前提条件。当类没有虚函数表的时候（也即一个虚函数都没有定义）,dynamic_cast无法使用RTTI，不能通过编译（可能）



## Reference

[1] [[C++强制类型转换操作符 dynamic_cast](https://www.cnblogs.com/QG-whz/p/4517336.html)](https://www.cnblogs.com/QG-whz/p/4517336.html)

[2] *C++ Primer*