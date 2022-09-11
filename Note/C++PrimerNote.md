# C++ Primer Note

*开始时间: 9月4号*

## Sec1 Begin

## Sec2 Basic Built-in Type

### 2.1 基本内置类型

* 符号数:
    * 无符号数和负数相加。会先将负数转化为无符号数再进行相加
    * 无符号数相减，无论如何都不可能为负数，若结果为负数，则会直接按照比特位来读取无符号数
    * 混用无符号和有符号型，比如相乘，得看机器上int所占位数而定
* 转义序列（escape sequence） 
    * \\ 后面跟3个字符。都是转义的内容 
        * 例子：\\1234，表示转义字符\\123和字符4
* 0开头的数为8进制数。以0X开头的为16进制数
* 表示浮点数：
    * 反例：`1024f`。正确应该为`1024.f`

### 2.2 变量

* 初始化

  * 列表初始化

    ```
    long double ld = 3.14159   
    int a{ld}, b = {ld};	// 报错，存在丢失信息风险
    int a(ld), b = ld;    	// 正确，但丢失部分值
    ```

  * 默认初始化
    没有指定初值，默认初始化

    * 定义于任何函数之外的变量被初始化为0
    * 定义在函数体内部的内置类型变量将不被初始化 uninitialized
    * 每个类各自决定初始化对象的方式
      是否不经过初始化就定义对象也由类自己决定
    * 建议初始化每一个内置类型的变量

  * 声明和定义：
    变量声明规定了变量的类型和名字，定义也一样，不同点在于，定义还申请存储空间，也可能会给变量赋一个初始值
    任何包含显示初始化的声明，即成为定义

    ```
    extern int i;	// 声明i，并非定义i
    int j;			// 声明并定义j
    extern double pi = 3.14 // 定义
    ```

    函数内部，如果试图初始化一个由extern关键字标记的变量会引发错误
    变量能且只能被定义一次，但可以被多次声明

  * 作用域
    scope

  ### 2.3 复合类型 (Compound Type)

  * 引用：reference

    * lvalue reference
      一般指：左值引用 \&

      一定要初始化！定义引用时，程序把引用与他的初始值bind绑定在一起，而不是将初始值拷贝给引用。
      一旦初始化完成，引用将和它的初始值对象一直绑定在一起。因为无法令引用重新绑定另外一个对象，因此引用必须初始化。
      （引用只是为一个已经存在的变量起一个别名）

  * 指针 pointer

    \&：取地址符
    \*：解引用符

    * 空指针：
      nullptr可以转化为任意其他的指针类型

      ```
      int *p1 = nullptr; // 建议
      int *p2 = 0;
      int *p3 = NULL; // (预处理变量（preprocessor variable）)
      ```

    * void\* 指针 
      不能直接操作，因为我们不知道是什么类型

    * 指向指针的引用：（不能定义指向引用的指针，因为引用不是对象）
      ```
      int i  = 42;
      int *p;
      int *&r = p; // r是一个对指针p的引用，从右往左看
      
      r = &i;  // r引用了一个指针，因此给r赋值给&i, 就是令p指向i
      ```

  ### 2.4 const限定符

* const对象必须初始化

* 多文件使用同一个const？
  每个文件都用  `extern const int bufSize`  // 例子,都加extern

* **const的引用**
  (reference to const)

  * ```
    const int ci = 1024;
    const int &r1 = ci; 	// 引用及其对应的对象都是常量
    r1 = 42; 	// 错误
    int &r2 = ci;	// 错误。让一个非常量引用指向一个常量对象
    ```

  * ```
    int i = 42;
    const int &r2 = 42;	// 正确，常量引用（甚至可以绑定任意表达式作为初始值，或者字面值）
    const int &r1 = i; 	// 正确，常量引用
    const int &r3 = r1*2;	// 正确，常量引用
    int &r4 = r1 * 2;	// 错误，r4是一个普通的非常量引用
    ```

    为什么r4是错误引用？
    例子：

    ```
    double dval = 3.14;
    const int &ri = dval;
    --> 编译器具体操作，会产生一个temp变量
    const int temp = dval;
    const int &ri = temp;
    所以ri不是引用dval,而是引用了一个隐藏的temp，这显然不好
    ```

  * 对const的引用可能引用一个并非const的对象
    ```
    int i = 42;
    const int &ri = i; 
    // 这表明不能通过ri，来修改i的值。
    ```

  * 常量引用！
    ```
    const int &r = 0;
    // 合法。因为是常量引用，所以可以绑定在常量上。
    ```

  * 非法的情形：不能让引用恒定不变
    例子:`const int &const r2`:
    非法，引用不是对象，所以不能让引用恒定不变！

  * 指针和const
    ```
    const double pi = 3.14;		// 定义一个const常量
    double *ptr = &pi;			// 错误，因为ptr是普通指针，不能指向常量
    const double *cptr = &pi;	// 正确，cptr可以指向一个常量
    *cptr = 42;					// 错误，不能给常量赋值
    ```

    * 指针类型与所指对象不一致的例外：

      1. **允许一个指向常量的指针，指向一个非常量对象**

         ```
         double dval = 3.14;
         cptr = &dval;	// 正确，但是不能通过cptr改变dval的值
         ```

         （指向常量的指针，**仅仅要求不能通过该指针改变对象的值**！）
         （指向常量的引用也是一样！）

      2. 常量指针 const pointer
         必须初始化
         表示不变的是指针的值，而不是指向的那个值（指向不变！）

         ```\
         int errNumb = 0;
         int *const curErr = &errNumb;	// *号放在const之前，说明指针是一个常量
         const double pi = 3.14
         const double *const pip = &pi;	// pip是指向常量对象的常量指针
         ```

         * 如何辨别？
           从右往左阅读！
           例子:

           ```
           const int *const curErr = &errNumb;
           离curErr最近的是const，所以curErr是一个常量对象！
           然后对象是类型，由声明符的其余部分决定
           声明符下一个是*，意思是curErr是一个常量指针，
           最后const int表示常量指针指向的是一个int常量对象。
           ```

           指针是常量，并不意味着不能通过指针修改指向的值，而是要看指向的对象的类型！

         * 非法例子：
           ```
           int *p1;
           const int *const p3;
           p1 = p3;
           // 非法，p1可以修改其指向的值，但是p3不能被修改！语法上错误！
           ```

           

* 顶层(top-level) const / 底层(low-level) const

  * 顶层const：表示指针本身是常量 （不允许改变对象的值）

  * 底层const：表示指针所指对象是const （允许改变对象的值）
    用于声明引用的const都是底层const

  * 拷贝上的区别：

    * 拷贝操作对顶层const无影响

    * 拷贝操作对底层const来说，左右两边必须具有相同的底层const资格

    * 还有例如：
      ```
      int i = 0;
      const int ci = 42;
      int &r = ci; 			// 错误，普通int不能绑定在一个const int上
      const int &r2 = i;		// 正确，const int可以绑定在普通int上
      ```

  * 顶：自己就是常量
    底：指向的东西是常量

* constexpr和常量表达式

  * 常量表达式：
    值不会改变且**编译过程就能得到计算结果的表达式**
  * constexpr变量
    * 作用于指针，只表示常量指针（顶层const）
    * 需要字面值类型 literal type
    * constexpr指针初始化必须为0或者nullptr

### 2.5 处理类型

* 类型别名 （type alias）
  ```c++
  typedef double wages;
  typedef wages base, *p;
  ```

  *  别名声明 （alias declaration）

    ```
    using SI = Sales_item;
    ```

  * 注意的点：
    ```c++
    typedef char *pstring;	// pstring是指向char的指针
    const pstring cstr = 0;	// cstr 是指向char的常量指针
    const pstring *ps;		// ps是指针，指向指向char的指针
    ```

* auto类型说明符
  目的：常常会将表达式的值赋给变量，但需要知道表达式的类型，所以引入auto，变量就可以自动转换类型了。

  `auto`可以在一条语句重声明多个变量。因为一条声明语句只能有一个基本数据类型，所以该语句中所有变量的初始基本数据类型都必须一致

  ```c++
  auto i = 0, *p = &i;	// 正确，类型一致
  auto sz = 0, pi = 3.14	// 错误
  ```

  * `auto` 一般会忽略顶层const，保留底层const

    ```c++
    const int ci = i, &cr = ci;
    auto b = ci;					// b 是一个整数，ci的顶层const被忽略
    auto c = cr;					// c 是一个整数, cr是ci的别名，ci是一个顶层const，所以也被忽略
    auto d = &i;					// d是一个整型指针，整数的地址就是指向整数的指针
    auto e = &ci;					// e是一个指向整数常量的指针 （对常量对象取地址是一种底层const）
    ```

    如果希望推断出的auto是一个顶层const，需要明确指出
    `const auto f = ci;`

    还可以将引用的类型设置为auto
    ```c++
    auto &g = ci;		// g是一个整型常量引用
    auto &h = 42;		// 错误，不能将非常量引用绑定字面值
    const auto &j = 42;	// 正确，可以将常量引用绑定字面值
    ```

* decltype类型指示符

  作用是选择并返回操作数的数据类型 （得到类型但不实际计算表达式的值）
  `decltype(f()) sum = x;  // sum的类型就是函数f的返回类型`	

  若decltype使用的表达式是一个变量，则decltype返回该变量的类型，包括顶层const和引用在内
  如果表达式是一个解引用，则会得到引用类型

  ```c++
  int i = 42, *p = &i, &r = i;
  decltype(r+0) b;	// 正确，结果是int类型
  decltype(*p) c;	// 错误，c是int&类型，所以必须初始化
  ```

  ```
  // 注意，如果里面是加了括号的变量，结果将是引用
  decltype((i)) d;	// 错误，d为int&,必须初始化
  decltype(i) e;		// 正确
  ```

  
