# C++ Primer Note

*开始时间: 9月4号*

[TOC]



## Sec1 Begin

## Sec2 变量和基本类型

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

  ```c++
  // 注意，如果里面是加了括号的变量，结果将是引用
  decltype((i)) d;	// 错误，d为int&,必须初始化
  decltype(i) e;		// 正确
  ```

   

## Sec3 字符串、向量和数组

### 3.1 using

using namespace::name

### 3.2 string:

* 初始化：
  ```
  string s1;
  string s2(s1);
  string s2 = s1;
  string s3("value");
  string s3 = "value";	// 拷贝初始化 （用了等号 = ）
  string s4(n,"c");
  ```

* 操作
  ```
  os<<s
  is>>s
  getline(is, s)
  s.empty()
  s.size()
  s[n]
  s1+s2
  s1=s2
  s1==s2
  s1!=s2
  <,<=,>=,>
  ```


* cctype头文件
  ```
  isalnum(c)
  isalpha(c)
  iscntrl(c)
  isgraph(c)	ispunct(c)
  islower(c)	tolower(c)
  isupper(c)	toupper(c)
  isxdigit(c)
  ```

* 操作每一个字符
  ```c++
  for(declaration : expression){
  	statement;
  }
  ```

  ```c++
  // 例子：
  string str("swafasgdsvsaefwqa");
  for(auto c : str)
  	cout << c << endl;
  ```

### 3.3 Vector

 `vector<int> ivec;|`
vector是模板，并非类型！

* 初始化：

  1. 列表初始化
     只能用花括号
  2. 拷贝初始化

  3. 创建指定数量的元素
  4. 值初始化
     仅指定元素数量
     但接下来只能用直接初始化，而且有的类一定要初始化指定值！

  ```c++
  // 区别
  vector<int> v1(10);
  vector<int> v2{10};
  vector<int> v3(10,1);
  vector<int> v4{10,1};
  // 注意要是不同类型
  vector<string> v5{"hi"};	// 列表初始化
  vector<string> v6("hi");	// 错误，不能用字符串字面值构建vector对象
  vector<string> v7{10};
  vector<string> v8{10, "hi"};
  ```

* 基本操作
  ```c++
  v.empty()
  v.size()
  v.push_back(t)
  v[n]
  ```

* ```
  vector<int>::size_type // 正确
  vector::size_type; // 错误
  ```

* 不能用下标形式添加元素

### 3.4 迭代器

* ```
  v.begin()
  v.end()			// 尾后迭代器,off the end. 指向容器的一个本不存在的尾后
  若容器为空，则v.begin() == v.end()
  ```

* 迭代运算符
  ```c++
  *iter
  iter->mem
  ++iter
  --iter
  iter1 == iter2
  iter1 != iter2
  ```

* 使用：
  ```c++
  string s("awefdwafefga");
  if(s.begin() != s.end())	// 若容器非空
  {
      auto iter = s.begin();	// 定义迭代器变量
      *iter = touppper(*iter);// 解引用来直接访问
  }
  ```

  ```c++
  // 将第一个单词转换为大写
  for(auto iter = s.begin(); iter != s.end() && !isspace(*iter); ++iter){
      *iter = toupper(*iter);
  }
  ```

* 迭代器类型

  const_iterator: 只读不写
  iterator
  如果vector对象或者string对象是一个常量，则只能使用const_iterator

  ```c++
  vector<int> v;
  const vector<int> cv;
  auto it1 = v.begin()	// it1的类型是vector<int>::iterator
  auto it2 = cv.begin()	// it2的类型是vector<int>::const_iterator
  ```

  * begin和end 返回的具体类型由对象是否为常量决定：
    `const_iterator`
    `iterator`
  * 如果需要是对象只需要读操作而无需写操作。最好使用常量类型。
    `cbegin()`
    `cend()`
    可以返回常量类型迭代器（不管对象是不是常量

* 迭代器的解引用
  ```
  // 注意：
  (*iter).mem 和 *iter.mem结果不同。点运算符的优先级是比解引用运算符更高的
  (*it).empty();	// 解引用，访问empty成员
  *it.empty();	// 错误，it是个迭代器，没有empty成员
  
  简化：
  (*it).mem 等价于 it->mem
  ```

* **某些对vector对象的操作会使迭代器失效**
  * 不能在范围for循环中向vector对象添加元素
  * 任何一种可能改变vector对象容量的操作，比如push_back，都会使该vector对象的迭代器失效。
    （凡是使用了迭代器的循环体，都不要往迭代器所属的容器添加元素）

* 迭代器运算
  ```
  iter+n
  iter-n
  iter1 += n
  iter1 -= n
  iter1 - iter2	// 迭代器相互之间的距离
  ```

  * 例子，得到迭代器中间的元素
    ```
    auto mid = vi.begin() + vi.size() / 2
    ```

    距离的类型：`difference_type`的带符号型整数

  * 例子2：二分搜索：
    ```c++
    // Binary search
    // text 必须是有序的
    // beg和end表示我们搜索的范围
    auto beg = text.begin(), end = text.end();
    auto mid = beg + (beg-end)/2;
    while(mid!=end && *mid!=sought){
        if(sought < *mid)
        	end = mid
        else
            beg = mid + 1
    	mid = beg + (end-beg)/2   
    }
    ```

### 3.5 数组

* 复杂数组的声明
  阅读方法，从内到外
  
  ```c++
  int *ptrs[10];
  int &refs[10];	// 错误
  int (*Parray)[10] = &arr;
  int (&arrRef)[10] = arr;	// arrRef引用一个含有10个整数的数组
  int *(&arry)[10] = ptr;		// array是数组的引用，该数组有10个指针
  ```
  
* 访问数组
  数组下标的类型：`size_t`

  而且数组下标如果不是纯数字，就必须是constexper类型！！！！！
  ```c++
  unsigned cnt = 42;
  constexpr unsigned sz = 42;
  string bad[cnt];	// 错误，cnt不是常量表达式
  int *parr[sz];		// 正确
  ```

  vector允许拷贝，数组不允许拷贝

* 迭代器：
  可以把指针看成是数组的迭代器
  同样 数组也有begin和end

  ```
  c++11 std
  int ia[] = {1,2,3,4,5,65};
  int *beg = begin(ia);
  int *last = end(ia);
  ```

* C风格字符串
  ```
  // function
  strlen(p)
  strcmp(p1,p2)	// 返回p1-p2的长度的正负
  strcat(p1,p2)	// 将p2附加到p1后，返回p1
  strcpy(p1,p2)	// 将p2拷贝给p1，返回p1
  ```

  * string和字符串数组相互转换
    提供了c_str()成员函数

    ```
    string s("dawdadaw");
    char *str = s;	// 错误
    const char *str = s.c_str();	// 正确
    ```

* 多维数组的下标引用
  ```
  int (&row)[4] = ia[1]; // 把row绑定到ia的第二个4元素数组上
  ```

* 多维数组的for语句处理

  * 用范围for语句

  ```c++
  size_t cnt = 0;
  for(auto &row : ia)				// 因为要改变变量，所以要把控制变量row和col设置为引用
  	for(auto &col : row) {
          col = cnt;
          ++cnt;
      }
  先访问ia的所有元素-->即大小为4的数组，再访问大小为4的数组
  ```

  为什么要用引用？？（避免数组被自动转成指针）
  
  声明为引用的另一个好处，如果是string的话，可能会非常大，**声明为引用可以避免对对象的拷贝操作！！！！**
  
  ```
  for(auto row : ia)
  	for(auto col : row)
  		...
  会报错！原因是第一个for循环的auto将row转化为指向整数的指针，而不是指向数组的指针！所以第二个for循环错误！
  ```
  
  **要使用范围for语句处理多维数组，除别最内层的循环外，其他所有循环的控制变量都应该是引用类型**
  
  * 常规for语句
    ```c++
    for(auto p = begin(ia);p!=end(ia); ++p){
    	for(auto q = begin(*p); q!=end(*p); ++q)
    		cout << *q << ' '
    	cout << endl;
    }
    ```
  
    



## Sec4 表达式、逻辑和关系运算符

* `&&`: 只有左边为真才对右边求值
  `||`: 只有左边为假才对右边求值

  * 例子：
    ```c++
    index != s.size() && !isspace(s[index])
    ```

    首先检查index是否达到string对象的末尾，以此才确保只有当index在合理范围之内时，才会计算右侧运算对象的值

* 递增递减运算符

  * 建议：除非必须，否则不用递增递减运算符的后置版本！！！

  * 常用手法：

    ```c++
    cout << *iter++ << endl;
    ```

* 条件运算符
  `cond ? expr1 : expr2`
  注意，该运算符的优先级非常低！
* 移位运算符优先级
  不高不低。比算术运算符低，比关系运算符，赋值、条件运算符高



## Sec5 语句

### 5.1 简单语句

* 空语句
* 分号的使用
* 复合语句
  compound statement

### 5.2 语句作用域

* if, switch, while和for语句的控制结构内定义变量。
  定义在控制结构当中的变量只在相应语句的内部可见

### 5.3 条件语句

* if-else
* switch
  记得写break和default
  别在case里面定义可能会跨case的变量！

### 5.4 迭代语句

* while

* for循环
  ```c++
  for(init-statement; condition; expression)
      	statement;
  ```

  流程：先初始化，再判断条件，再执行statement，最后执行expression
  再判断条件，...，循环往复，直到不满足条件

* **（C++特性）范围for语句**

  ```c++
  for(declaration : expression)
      	statement
  ```

  其中，expression必须为一个序列！（有begin和end成员）
  declaration定义为一个变量，使得序列中的每个元素都能转换为该变量的类型。
  （常常用auto，而且引用是一个好习惯，引用后可以对expression中的序列写操作）

  * 不能通过范围for语句增加vector对象，因为会存储end()值！！！要是增加就会变得无效了！

* do-while语句

* 跳转语句

  * break语句

  * continueyuju

  * goto语句
    尽量别用

    ```
    goto label;
    ```

    labeled statement

### 5.6 try语句块和异常处理

* C++的异常处理：
  * throw:
    异常检测部分使用throw表达式来表示它遇到了无法处理的问题，我们说throw引发(raise)的异常
  * try:
    异常处理部分使用try语句块处理异常。
    以try开始，以catch结束。(异常处理代码 exception handler)
  * 一套异常类 exception class
    用于在throw表达式和相关的catch子句之间传递异常的具体信息

* throw表达式

  ```c++
  if(item1.isbn() != item2.isbn())
      throw runtime_error("Data must refer to same ISBN");
  ```

* try语句块
  ```c++
  try{
      program-statements
  } catch (exception-declaration) {
      handler-statements
  } catch (exception-declaration) {
      handler-statement;
  }
  ```



## Sec6 函数

### 6.1 函数基础

* 分离式编译
  C++开发中广泛使用声明和实现分开的开发形式，其编译过程是**分离式编译**
  就是说各个cpp文件完全分开编译，然后生成各自的obj目标文件，最后**通过链接器link生成一个可执行的exe文件**。不需其他操作。

### 6.2 参数传递

形参的类型决定了形参和实参的交互方式

* 引用传递（passed by reference） 形参是引用类型
  引用形参也是它绑定对象的别名
* 值传递（passed by valued）
  形参和实参是两个独立的对象 

* 指针形参
  注意函数内部可以通过指针的参数来改变外边的值了
  但只改变指针本身，不会影响外边

==

* **当用实参初始化形参的时候会忽略掉顶层const**
  所以允许用字面值或者非常量，来初始化常量引用
  **（标准是不要改变常量）**

**尽量使用常量引用**

#### 6.2.4 数组形参

* 管理方法

  * 使用标记指定数组长度
  * 使用标准库规范
    begin，end
  * 显式传递一个表示数组大小的形参

* 数组形参和const
  当函数不需要对数组元素执行写操作，数组形参应该是指向const的指针

* 数组引用形参

  ```c++
  f(int &arr[10]);	// 错误，不存在引用的数组
  f(int (&arr)[10]);	// 正确，arr是一个具有10个整数的整型数组的引用
  ```

* 多维数组
  ```c++
  int *matrix[10];	// 10个指针构成的数组
  int (*matrix)[10];	// 指向含有10个整数的数组的指针
  ```

#### 6.2.5 main: 处理命令行选项

```c++
int main(int argc, char *argv[])
```

argv为一个数组，元素是指向c风格字符串的指针。第一个形参为argc，是表示数组中字符串的数量！
```c++
命令: prog -d -o ofile data0
argv[0]="prog";		// 第一个元素指向程序的名字或者一个空字符串
argv[1]="-d";		// 饥饿下来的元素以此传递命令行提供的参数
argv[2]="-o";
argv[3]="ofile";
argv[4]="data0";
argv[5]=0;			// 最后一个指针之后的元素保证为0
```

#### 6.2.6 含有可变形参的函数

* 编写能处理不同数量实参的函数：

  * 如果所有的实参类型相同，可以传递一个名为initializer_list的标准库类型
  * 如果实参的类型不同，可以编写一种特殊的函数。即可变参数模板

* `initializer_list`
  一种标准库类型，用于表示某种特定类型的值的数组

  ```c++
  initializer_list<T> lst;	// 默认初始化，T类型元素的空列表
  initializer_list<T> lst{a,b,c...}
  							// lst的元素数量和初始值一样多，lst的元素是对应初始值的副本，列表中迭代元素是const
  lst2(lst);					// 拷贝或者赋值不回拷贝列表中的元素，而是原始列表和副本共享元素
  lst2 = lst;
  lst.size();
  lst.begin();lst.end();
  ```
  
  `initializer_list` 永远是常量值

* 省略符形参
  仅仅用于C于C++通用的类型！

  ```c++
  void foo(parm_list,...); // 省略符之后的形参不会执行类型检查
  void foo(...);
  ```

### 6.3 返回类型和returen语句

* 返回
  * 无返回值函数
  * 有返回值函数

* 如何返回值
  返回的值用于初始化调用点的一个临时变量

* 返回的注意事项
  **不要返回局部对象的引用或指针**
  因为函数完成后，所占用的存储空间也随之被释放掉

  ```c++
  const string &manip()
  {
      string ret;
      if(!ret.empty())
          return ret;			// 错误，返回局部对象的引用
     	else
          return "empty";		// 错误，empty是一个局部临时量
  }
  ```

* 返回类类型的函数和调用运算符
  调用运算符的优先级和点和箭头运算符相等。且符合左结合律

* 引用返回左值
  调用一个返回引用的函数得到左值，其他返回类型为右值

  ```c++
  // 例子
  char &get_val(string &str, string::size_type ix){
      return str[ix];
  }
  int main(){
      string s("a value");
      cout << s << endl;
      get_val(s, 0) = "A";
      cout << s << endl;
      return 0;
  }
  ```

* 列表初始化返回值
  很好用。
  返回一个\{\}起来的值，然后用里面的值来初始化！

* main的返回值
  ```c++
  return EXIT_FAILURE;
  return EXIT_SUCCESS;
  ```

#### 6.3.3 返回数组指针

函数可以返回数组的指针或者引用。
```c++
typedef int arrT[10];	
using arrT = int[10];
arrT* func(int i);		// func返回一个指向含有10个整数的数组的指针
```

```c++
int arr[10];
int *p1[10];
int (*p2)[10] = &arr;
```

或者直接定义
```c++
type (*function(parameter_list))[dimension]	// 返回数组指针的函数
```

* 使用尾置返回类型
  trailing return type
  对返回值比较复杂的函数最有效

  ```c++
  auto func(int i) -> int(*)[10];
  // 把函数返回类型放在->之后，并在前面用auto定义
  ```

* 或者用decltype

### 6.4 函数重载 （重要）

pass



### 6.5 特殊用途语言特性

* 三种函数相关的语言特性

  * 默认实参
    一旦某个形参被赋予了默认值，它后面的所有形参都必须有默认值
    只能省略尾部的实参！！！

    ```c++
    window = screen(,,'?');	// 错误
    ```

    而且给定的作用域中，一个形参只能被赋予一次默认实参
    只要表达式的类型可以转换为对应类型，该表达式就可以作为默认实参

  * 内联函数

  * constexper

* 内联函数
  可以避免函数调用的开销
  `inline`

* constexper函数
  指能用于常量表达式（编译过程就能得到结果）的函数
  函数返回类型以及所有形参的类型都得是字面值类型，而且**函数体中必须有且只有一条return语句**
  会被隐式的展开为内联函数

* 建议把内联函数和constexper函数放在头文件里面

#### 6.5.3 调试帮助

头文件保护

* assert预处理宏
  preprocessor marco

  ```c++
  assert(expr);
  ```

  先对expr求值，如果expr为0，则输出信息并终止程序执行。如果为真，则啥也不做

* NDEBUG预处理变量
  如果定义了 NDEBUG，则assert什么也不做。默认状态下没有定义NDEBUG，此时assert将执行运行时检查

  ```c++
  // 对调试有用的名字
  __func__
  __FILE__
  __TIME__
  __LINE__
  __DATE__
  ```

  

### 6.6 函数匹配

```c++
void f();
void f(int);
void f(int, int);
void f(double, double = 3.14);
```

* 确定候选函数和可行函数
  candidate function / viable function

* 寻找最佳匹配
  基本思想是，实参类型与形参类型越接近，匹配得越好

* 含有多个形参的函数匹配
  例如：
  `f(42,2.56)`

  * 可行函数为f(int,int), f(double, double)
  * 确定最佳匹配的条件
    * 该函数每个实参的匹配都不劣于其他可行函数所需要的匹配
    * 至少有一个实参的匹配优于其他可行函数提供的匹配

  * 故该调用具有二义性，拒绝并报错

* 实参类型转换

### 6.7 函数指针

```c++
// 比较两个string对象的长度
bool lengthCompare(const string &, const string &);

// pf指向一个函数，该函数的参数是两个const string的引用，返回值是bool类型
bool (*pf)(const string &, const string &); // 未初始化
```

一定要写括号！如果不写的话，返回值就是一个指向bool类型的指针

* 使用函数指针
  当我们把函数名作为一个值使用的时候，该函数自动地转换成指针。

  ```c++
  pf = func;
  pf = &func;	// &是可选的。这两条是等价的,而且func应该是bool类型的！返回类型要一致
  // 调用
  bool b1 = pf("hello", "good");
  bool b2 = (*pf)("hello", "good");	// 这两条也是等价的
  
  ```

* 重载函数的指针
  通过指针类型决定选用哪个函数。指针类型必须与重载函数中的某一个精确匹配

* 函数指针形参
  ```c++
  void useBigger(const string &s1, const string &s2, bool pf(const string &, const string &))
  ```

  * 可以用decltype和typedef来简化操作！
    ```c++
    // Func和Func2是函数类型
    typedef bool Func(const string&, const string&);
    typedef decltype(lengthCompare) Func2;	// 等价的类型
    // FuncP和FuncP2是指向函数的指针
    typedef bool (*FuncP)(const string&, const string&);
    typedef decltype(lengthCompare) *FuncP2;	// 等价声明
    
    void useBigger(const string&, const string&, Func);		// 自动将Func转换为指针
    void useBigger(const string&, const string&, FuncP2);	// 等价
    ```

* 返回指向函数的指针|
  注意，不能返回一个函数！

  ```c++
  using F = int(int*, int);			// F为函数类型
  using PF = int(*)(int*, int);		// PF为指针类型
  ```

  ```c++
  PF f1(int);	// 正确
  F f1(int);	// 错误
  F *f1(int);	// 正确，与第一条等价，返回为指向函数的指针
  
  auto f1(int) -> int (*)(int*, int);	// 尾置返回类型
  ```

  

  

## Sec7 类

* 类的基本思想是：

  * 数据抽象 data abstraction
    依赖接口 (interface) 和 实现 (implementation) 分离的编程技术

  * 封装 encapsulation
    封装实现了类的接口和实现的分离

  类想要实现数据抽象和封装，首席按需要定义一个抽象数据类型 （abstract data type）
  ADT

### 7.1 定义抽象数据类型

#### 7.1.1 / 7.1.2 关于Sales_data类的改进

* 定义成员函数
  可以定义在类内和类外。但是类内一定要有声明

  * 定义在类内部的函数是隐式的inline函数

* 引入`this`
  成员函数通过一个名为`this` 额外隐式参数来访问调用它的哪个对象。当我们调用一个成员函数时，用请求该函数的对象地址初始化this

  ```c++
  // 例子：
  total.isbn();
  // 伪代码，用于说明调用成员函数的实际执行过程
  Sales_data::isbn(&total)
  ```

  在成员函数内部，可以直接使用调用该函数的对象的成员！无须通过成员访问运算符来做到这一点。
  任何对类成员的直接访问都被看作this的隐式引用。
  this的目的总是指向这个对象。所以this是一个**常量指针！**

* 引入`const`成员函数
  ```c++
  std::string isbn() const {return bookNo; }
  ```

  这里的const 的作用是修改隐式this指针的类型
  默认情况下，this的类型是指向类类型非常量版本和常量指针。

  * 因为this是隐式的，所以在哪儿将this声明成指向常量的指针就成为我们必须要面对的问题：
    C++的做法是允许把const关键字放在成员函数的参数列表之后。这时候，紧跟在参数列表后面的const代表this是一个指向常量的指针。这样使用const的成员函数被称为 （const member function）常量成员函数

    ```c++
    // 伪代码，说明隐式的this指针是如何使用的
    // 下面的代码是非法的。因为不能显式定义自己的this指针
    // 此处的this是一个指向常量的指针，因为isbn是一个常量成员
    std::string Sales_data::isbn(const Sales_data *const this)
    {
        return this->isbn;
    }
    ```

    const 成员函数可以使用类中的所有成员变量，但是不能修改它们的值

    * 最后再来区分一下 const 的位置：
      - 函数开头的 const 用来修饰函数的返回值，表示返回值是 const 类型，也就是不能被修改，例如`const char * getname()`。
      - 函数头部的结尾加上 const 表示常成员函数，**这种函数只能读取成员变量的值，而不能修改成员变量的值**，例如`char * getname() const`。

* 类作用域和成员函数
  ```c++
  double Sales_data::avg_price() const {
      if (units_sold)
          return revenue / units_sold;
      else
          return 0;
  }
  ```

* 定义一个返回this对象的函数
  ```c++
  Sales_data& Sales_data::combine(const Sales_data &rhs){
  	units_sold += rhs.units_sold;
      revenue += rhs.revenue;
      return *this;	// 返回调用该函数的对象
  }
  ```

  

#### 7.1.3 定义类相关的非成员函数

类常常需要辅助函数。但这些辅助函数并不属于类本身。



#### 7.1.4 构造函数

constructor

* 默认构造函数 default constructor

  * 如果存在类内的初始值，用它来初始化成员
  * 否则，默认初始化该成员

  当类没有声明任何构造函数时，编译器才会自动地生成默认构造函数

* 定义构造函数
  ```c++
  struct Sales_data {
      Sales_data() = default;	// 默认构造函数
      Sales_data(const std::string &s, unsigned n, double p) :
      			boookNo(s), units_sold(n), revenue(p*n) { }
      Sales_data(std::istream &is);
      ...
  }
  ```

  `:` 后到函数体部分称为“构造函数初始值列表” (constructor initialize list)

* 在类的外部定义构造函数
  ```c++
  Sales_data::Sales_data(std::istream &is)
  {
      read(is, *this);	// read的作用是
  }
  ```

  我们在类的外部定义构造函数时，必须指名该构造函数是哪个类的成员。

#### 7.1.5 拷贝、赋值、析构

当类需要分配类对象之外的资源时，合成的版本常常会失效。（但使用vector或者string的类可以避免分配和释放内存带来的复杂性）

（这章还没到详细讲自定义操作的时候）

### 7.2 访问控制与封装

* 访问说明符（access specifiers）
  * public：
    之后的成员在整个程序内可以被访问
  * private：
    之后的成员可以被类内的成员函数访问，但是不能被使用该类的代码访问

* 使用class或struct关键字
  * 区别：
    默认访问权限不一样。
    类可以在它的第一个访问说明符之前定义成员，对这种成员的访问权限依赖于类定义的方式，如果我们使用struct关键字，则定义在第一个访问说明符之前的成员是public的，相反，如果使用class关键字，则这些成员是private的
    * 建议：
      出于统一编程风格的考虑，当我们希望定义的类所有成员是public，用struct，反之，希望成员是private的，使用class

#### 7.2.1 友元(friend)

类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元。

```c++
friend Sales_data add(const Sales_data&, const Sales_data&);
```

友元声明只能出现在类定义的内部！但是在类内出现的具体位置不限！

### 7.3 类的其他特性

* 用来定义类型的成员必须先定义后使用。
  
* 令成员作为内联函数
  可以在类的内部声明为inline，也可以在类的外部用inline关键字修饰函数的定义
  inline成员函数也应该跟相应的类，在同一个头文件中定义

* 重载成员函数
  跟函数的重载类似

* 可变数据成员
  mutable data member。
  永远不会是const，即使它是const对象的成员。因此，一个const成员函数可以改变一个可变成员的值。

* 类数据成员的初始值
  最好的方式就是把这个默认值声明成一个类内初始值

  ```c++
  class Window_mgr {
      private:
      	// 这个Window_mgr追踪的Screen
      	// 默认情况下，一个Window_mgr包含一个标准尺寸的空白Screen
      	std:vector<Screen> screens{Screen(24, 80, ' ')};
  }
  ```

* 含有指针数据成员的类，一般不宜使用默认的拷贝和赋值操作。如果类的数据成员都是内置类型，则不受干扰



#### 7.3.2 返回`*this`的成员函数

* 从const成员函数返回\*this
  注意，可能会不能把返回const 的引用的函数，嵌入到一组动作的序列中去
  例如：如果disply是一个返回const的引用
  则下面这个代码是错误的：

  ```c++
  myScreen.display(cout).set('*');
  ```

  

* 基于const的重载
  通过区分成员函数是否为const，我们可以对其进行重载。

  不知道重新看看就行

  当我们在某个对象上调用display时，该对象是否是const决定了应该调用display的哪个版本

#### 7.3.4 友元再探

* 类之间的友元关系：
  如果一个类指定了友元类，则友元类的成员函数可以访问此类包括非公有成员在内的所有成员。

* 令成员函数作为友元：
  当把一个成员函数声明成友元时，我们必须明确指出该成员函数属于哪个类

  ```c++
  friend void Window_mgr::clear(ScreenIndex);
  ```

  * 设计的流程：
    1. 首先定义Window_mgr类，其中声明clear函数，但不能定义它。在clear使用Screen的成员之前必须先声明Screen
    2. 接下来定义Screen，包括对于clear的友元声明
    3. 最后定义clear，此时它才可以使用Screen的成员

* 函数重载及其友元
  需要逐个声明友元

* 友元声明及其作用域
  ```c++
  struct X {
      friend void f() { /* 友元函数可以定义在类的内部 */}
      X() { f(); }		// 错误，f还没有被声明
      void g();
      void h();
  };
  void X::g()	{return f();}	// 错误，f还没声明
  void f();
  void X::h(){return f();}	// 正确
  ```

  友元声明的作用，仅仅是影响访问权限！并非普通意义上的声明



### 7.4 类的作用域

```c++
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    ...
}
```

返回类型使用的名字都在类的作用域之外，所以要声明返回类型在哪个作用域！

#### 7.4.1 名字查找与类的作用域

* name lookup(名字查找)

  * 过程：
    1. 在名字所在块中寻找其声明语句，只考虑在名字的使用之前出现的声明
    2. 如果没找到，继续查找外层作用域
    3. 如果最终没有找到匹配的声明，则程序报错

  * 类的定义分两步处理
    1. 首先，编译成员的声明
    2. 直到类全部可见后才编译函数体
  * 注意：
    编译器处理完类中的全部声明后才会处理成员函数的定义

* 类型名要特殊处理
  在类中，如果成员使用了外层作用域中的某个名字，而该名字代表一种类型，则类不能在之后重新定义该名字。

  ```c++
  using Money = double;
  class Account {
  public:
      Money balance() {return bal;}
  private:
      typedef double Money;	// 错误，不能重新定义money
      Money bal;
      ...
  }
  ```

* 成员定义的普通块作用域的名字查找

* 类作用域之后，在外围的作用域中查找
  ```c++
  void Screen::dummy_fcn(pos height){
      cursor = width * ::height;	// 这个height是全局的height
  }
  ```

  

### 7.5 构造函数再探

#### 7.5.1 构造函数初始值列表

* 遇到引用，const等，构造函数的初始值有时必不可少
  建议养成使用构造函数初始值的习惯。

* 成员初始化的顺序：
  成员初始化的顺序，与他们类定义中出现的顺序一致！与构造函数初始值列表中的顺序无关！

  所以最好他们的顺序一致。

* 默认实参和构造函数
  如果一个构造函数为所有参数都提供了默认实参，则它实际上就定义了默认构造函数。
  此时，=default类型的默认构造函数应该删除！

  ```c++
  Sales_data(std::istream &is = std::cin) {is >> *this};
  此时该函数具有了默认构造函数的作用！所以应该删去原来声明的默认构造函数=default，不然会有
  ```

#### 7.5.2 委托构造函数

delegating constructor

```c++
class Sales_data {
public:
    Sales_data(std::string s, unsigned cnt, double price) : 
    			bookNo(s), units_sold(cnt), revenue(cnt*price) { }	// 若函数体有内容，则先执行函数体中的代码，再将控制权交还给委托者的函数体
    // 其余构造函数全都委托给另一个构造函数
    Sales_data() : Sales_data("",0,0) { }	// 默认构造函数
    Sales_data(std::string s) : Sales_data(s, 0, 0) {}
    Sales_data(std::istream &is) : Sales_data() { read(is, *this);}
}
```

#### 7.5.4 默认构造函数的作用

* 使用默认构造函数
  ```c++
  Sales_data obj();						// 正确。定义了一个函数并非对象
  if(obj.isbn() == Primer_5th_ed.isbn());	// 错误，obj是一个函数
  
  Sales_data obj;	// 正确，定义了一个对象，且使用默认初始化
  ```

* 抑制构造函数的隐式转换
  可以通过将构造函数声明为`explicit`加以阻止

  注意：编译器只会自动地执行一步类型转换
  ```c++
  item.combine(s);	// s是string类型
  item.combine("saswdsaw");	// 错误,要两步类型转换
  
  explicit Sales_data(const std::string &s) : bookNo(s) { }
  item.combine(s);	// 错误，需要explicit匹配
  ```

* explicit构造函数只能用于直接初始化
  ```c++
  Sales_data item1(null_book);	// 正确，直接初始化
  Sales_data item2 = null_book;	// 错误，不能将explicit构造函数用于拷贝形式的初始化过程
  ```

* 为转换显示地使用构造函数
  ```c++
  item.combine(Sales_data(null_book));
  item.combine(static_cast<Sales_data>(cin));
  ```

  

#### 7.5.5 聚合类

aggregate class 聚合类可以使得用户直接访问其成员，并且具有特殊的初始化语法形式。
当一个类为：

1. 所有成员都是public时
2. 没有定义任何构造函数
3. 没有类内初始值
4. 没有基类，也没有virtual函数

```c++
struct Data{
    int ival;
    string s;
}
```

#### 7.5.6 字面值常量类

* 定义：字面值常量类
  * 数据成员必须是字面值类型
  * 类必须至少含有一个constexpr构造函数
  * 如果一个数据成员含有类内初始值，则内置类型成员的初始值必须是一条常量表达式。或者如果成员属于某种类类型，则初始值必须使用成员自己的constexpr构造函数
  * 类必须使用析构函数的默认定义，该成员负责销毁类的对象

* constexper构造函数
  虽然构造函数不能是const，但是字面值常量类的构造函数可以是constexpr函数

### 7.6 类的静态成员

`static`
静态成员的类型可以是常量、引用、指针、类类型等

类的静态成员存在于任何对象之外，对象中不包含任何与静态数据成员有关的数据。
静态成员函数页不予任何对象绑定在一起，不包含this指针！所以静态成员函数不能声明为const。而且不能使用this指针。

* 使用类的静态成员
  跟其他的没区别。

* 定义静态成员
  内外都行
  但在外部定义静态成员时，不能重复static关键字。该关键字只能出现在类内部的声明语句中

  必须在外部定义和初始化每个静态成员。一个静态数据成员只能定义一次
  要想确保对象之定义一次，最好的方法是把静态数据成员的定义与其他非内联函数的定义放在同一个文件中

* 静态成员的类内初始化
  通常情况不能再类内部初始化。然而可以为静态成员提供const整数类型的类内初始值。不过要求静态成员必须是字面值常量类型的constexpr。初始值必须是常量表达式。

  ```c++
  static constexpr int period = 30;
  ```

  即使一个常量静态数据成员在类内部被初始化了。通常情况下页应该在类的外部定义一下该成员

* 静态成员可以是不完全类型。
  还可以使用静态成员作为默认实参



## Sec8 IO库

### 8.1 IO类

* `wchar_t`:
  宽字符版本（对应函数为前面加一个w）

* IO对象无拷贝或赋值
  不能初始化ofstream参数
  不能拷贝流对象

* 条件状态
  确定一个流对象的状态的最简单的方法是将它作为一个条件来使用的

  ```c++
  while(cin >> word)
  	// ok: 读操作成功
  ```

* 查询流的状态
  `iostate`

* 管理条件状态



* 管理输出缓冲
  每个输出流都管理一个缓冲区，用来保存程序读写的数据。
  * endl
  * flush：刷新缓冲区但不输出任何额外的字符
  * ends
    想缓冲区插入一个空字符，然后刷新缓冲区
  * 崩溃：输出缓冲区不会被刷新！
* 关联输入和输出流 

### 8.2 文件输入输出

* 可以继承istream和ostream对象

* 成员函数open、close
  对open的成功与否进行检测是一个好习惯

  ```c++
  ifstream in(ifile);	// 构筑一个ifstream并打开给定文件
  ofstream out;		// 输出文件流未与任何文件相关联
  out.open(ifile + ".copy");
  
  
  if (out)	// 检测
  ```

  如果open失败，条件会未为假，就不会使用out
  一旦一个文件流已经打开，它就保持与对应文件的关联。
  要将文件流关联到另一个文件，必须先关闭已经关联的文件。一旦成功关闭，就可以打开新文件。



### 8.3 stringstream





## Sec9 顺序容器





### 9.4 Vector对象如何增长？

一次两倍





## Sec10 泛型算法

### 10.2 初识

* `find(iter1, iter2, val)`

* `accumulate(iter1, iter2, init_val)`

* `equal(iter1_begin, iter1_end, iter2_begin)`

* `fill(iter1, iter2, val)`
  `fill_n(iter, size, val)`

* `auto it = back_inserter(container);  // 创建一个迭代器`
  `*it = val;  // 等价于直接调用push_back`

  ```c++
  vector<int> vec;
  auto it = back_inserter(vec);	// 通过它赋值会将元素添加到vec
  fill_n(it, 10, 0);
  ```

* `copy(iter_begin, iter_begin, iterDestination_begin)`
  返回的是其目的位置迭代器(递增后)的值

* `replace`
  读入一个序列，将其中所有等于给定值的元素都改为另一个值
  前俩为迭代器，表示输入序列，后俩个一个是要搜索的值，另一个是新值
  `replace(iter_begin,iter_end,val_before,val_replace)`
  如果希望原序列不变，可以用
  `replace_copy(iter_begin, iter_end, save_iter, val_before, val_replace)`

* `sort`

  用  `<`  运算符来排序

  消除重复单词
  先用sort排序，将重复的元素相邻，再用`unique`标准库算法。使得不重复的元素出现在vector的开始部分。
  用vector的erase成员来完成真正的删除操作

  ```c++
  void elimDups(vector<string> &words){
      sort(words.begin(), words.end());
      auto end_unique = unique(word.begin(), words.end());
      words.erase(end_unique, words.end());
  }
  ```



### 10.3 定制操作

* 向算法传递函数
  sort的第二个版本，第三个参数为一个**谓词  predicate**

  * 谓词：一个可调用的表达式，返回结果是一个能用作条件的值。

    * 分类：一元谓词 unary predicate(单一参数)  二元谓词 binary predicate(两个参数)

    * 例子：
      ```c++
      bool isShorter(const string &s1, const string &s2){
          return s1.size() < s2.size();
      }
      sort(words.begin(), words.end(), isShorter);
      ```

      

* `stable_sort(iter1, iter2, func)`
  稳定排序算法维持相等元素的原有顺序
* `find_if(iter_begin, iter_end, func)`第三个参数必须是一元谓词
  对输入序列每一个元素调用谓词，返回第一个使得谓词返回非0值的元素。如果不存在则返回尾迭代器 



* lambda表达式
  我们可以向一个算法传递任何类别的可调用对象 callable object

  ```c++
  [capture list](parameter list) -> return type { function body }
  ```

  一个lambda表达式表示一个可调用的代码单元。即未命名的内联函数

  * capture list: 函数内定义的局部变量的列表，通常为空

  * return type， parameter list 和 function body 与任何普通函数一样，分别表示返回类型、参数列表和函数体。
    lambda必须用到尾置返回来指定返回类型
    可以忽略**参数列表和返回类型**，但必须**永远包含捕获列表和函数体**

    ```c++
    auto f = [] {return 42};
    f();	// 调用
    ```

  * 传递参数：
    ```c++
    [] (const string &a, const string &b)
    	{ return a.size() < b.size(); }
    ```

  * 使用捕获列表

    * 编写一个传递给find_if的可调用表达式，希望这个表达式能将输入序列中的每个string的长度与biggies函数中的sz参数的值进行比较
      一个lambda将局部变量包含在其捕获列表中来指出将会使用这些变量，捕获列表指引lambda在其内部包含访问局部变量所需要的信息
      ```c++
      [sz] (const string &a) { return a.size() >= sz; }
      ```

      []中可以使用逗号分隔的名字列表，这些名字都是它所在函数中定义的。
      一个lambda只有在其捕获列表中捕获一个它所在函数中的局部变量，才能在函数体中

    * ```c++
      auto wc = find_if(words.begin(), words.end(),
      	[sz](const string &a)
      		{ return a.size() >= sz; } )
      ```

* for_each:
  此算法接受一个可调用对象，并对输入序列中每个元素调用此对象

  ```c++
  for_each(wc, words_end(), 
          [](const string &s) {cout << s << " ";});
  cout << endl;
  ```

#### 10.3.3 lambda捕获与返回

当向函数传递一个lambda时，同时定义了一个新类型和该类型的一个对象，传递的参数就是此编译器生成的类类型的未命名对象。

* 捕获方式

  * 值捕获
    前提是变量可以拷贝
    `[v1] { return v1; };`

  * 引用捕获
    `[&v1] { return v1; };`

    ```c++
    void biggies(vector<string> &words, 
                vector<string>::size_type sz.
                ostream &os = cout, char c = ' ')
    {
        for_each(words.begin(), words.end(), 
                [&os, c](const string &s) { os << s << c});
    }
    ```

    若函数返回一个lambda，则不能包含引用捕获

  * 隐式捕获
    `[=](cosnt string &s){return s.size() >= sz; };`
    用=或者&，&告诉编译器采用捕获引用方式，=则采用值捕获方式，可以混合使用！
    `[&, c]`  `[=-, &os]`

* 可变lambda
  值拷贝变量不会改变其值，如果希望改变一个被捕获的变量的值，就必须再参数列表首加上关键字mutable
  `[v1] () mutable {return ++v1;}`  所以可变lambda可以省略参数列表

* 指定lambda返回类型：
  如果lambda体是单一的return语句，则返回一个条件表达式的结果，无须指定返回类型。若有多条，且没指定返回类型，就会被编译器推定为返回void。
  定义lambda返回类型一定要用尾置返回类型

  ```c++
  [](int i) -> int 
  { if (i < 0) return -i; else return i; }
  ```

* 参数绑定
  如果捕获列表为空，可以用函数代替lambda。
  但如果对于捕获局部变量的lambda，用函数来替换旧不是那么容易了。比如find_if的第三个参数

* 标准库函数`bind`
  可以将bind堪称一个通用的函数适配器，接受一个可调用对象，生成一个新的可调用对象来适应原对象的参数列表。
  `auto newCallable = bind(callable, arg_list);`
  arg_list为参数列表，对应给定的callable参数
  其中，`_n`类型的名字，为占位符，表示newCallable的参数，占据了传递给newCallable的参数的位置，数值n表示生成的可调用对象中参数的位置，`_1`为newCallable的第一个参数。

  * 例子:
    ```c++
    auto check6 = bind(check_size, _1, 6);
    // 只有一个占位符表示check6只接受单一参数，占位符出现再arg_list的第一个位置，表示对应check_size函数的第一个参数，check6会将这个参数传递给check_size。
    // 如：
    string s = "dwafda";
    bool b1 = check6(s);	// 调用check_size(s, 6)
    // 此时因为只有一个参数，所以可以将check6用于基于lambda的find_if端调用
    ```

  * bind的参数
    ```c++
    auto g = bind(f, a, b, _2, c, _1);
    // 生成一个新的可调用对象，有2个参数，分别用占位符_2和_1表示。这个新的可调用对象将它自己的参数作为第三个和第五个参数传递给f。 f的第一个第二个和第四个参数为a，b，c
    // 即：
    g(_1, _2);
    // 等价于
    f(a,b,_2,c,_1);
    ```

  * 实际应用例子

    用bind重排参数顺序
    ```c++
    sort(words.begin(),words.end(), isShorter);
    sort(words.begin,words.end(), bing(isShorter, _2, _1));
    ```

  * 注意：
    bind拷贝其参数。如果我们希望传递给bind一个对象而又不拷贝它，那必须使用标准库函数ref
    例子：

    ```c++
    // 错误！
    for_each(words.begin(), words.end(), bind(print, os, _1, ' '));
    // 正确
    for_each(words.begin(), words.end(), bind(print, ref(os), _1, ' '));
    ```

### 10.4 再探迭代器

* 种类
  * 容器定义的迭代器
  * 插入迭代器
  * 流迭代器
  * 反向迭代器：除了forward_list都有反向迭代器
  * 移动迭代器

#### 10.4.1 插入迭代器

```c++
it = t;			// it指的位置插入t
*it, ++it, it++	// 不会做任何事，只会返回it
```

* `back_inserter`   (push_back)

* `fornt_inserter` （push_front）

* `inserter`创建一个使用insert的迭代器。此函数接受第二个参数，此参数必须是一个指定给定容器的迭代器。
  然后元素插入到**给定迭代器所表示元素之前**

* 工作过程:
  ```c++
  it = inserter(c, iter);	// 得到一个迭代器
  *it = val;	// 插入到指定元素之前
  // 相同的工作：
  it = c.insert(it, val);	// it指向新加入的元素
  ++it;					// 递增it使之指向原来的元素
  ```

  ```c++
  list<int> lst == {1,2,3,4};
  list<int> lst2, lst3; // 空list
  // lst2包含4，3，2，1
  copy(lst.cbegin(), lst.cend(), front_inserter(lst2));	// 插入迭代器
  // lst3包含1，2，3，4
  copy(lst.cbegin(), lst.cend(), inserter(lst3, lst3.begin()));
  ```

#### 10.4.2 iostream迭代器

`istream_iterator`和`ostream_iterator`

* 使用：

  * 从迭代器范围构造vec
    ```c++
    istream_iterator<int> in_iter(cin), eof;	// 从cin读取int
    vector<int> vec(in_iter, eof);
    ```

  * 使用算法操作流迭代器
    ```c++
    istream_iterator in(cin), eof;
    cout << accumulate(in, eof, 0) << endl;
    ```

  * istream_iterator允许使用懒惰求值
    当绑定到一个流时，标准库并不保证迭代器立刻从流读取数据，具体实现可以推迟从流中读取数据，知道我们使用迭代器时才真正读取。

* ostream_iterator操作

  * 输出值的序列
    ```c++
    ostream_iterator<int> out_iter(cout, " ");
    for(auto e : vec)
        *out_iter++ = e;	// 将元素写到cout
    cout << endl;
    ```

    注意：out_iter可以忽略解引用和递增运算
    ++，\* 实际上不做任何工作

  * 或者直接调用copy来打印vec中的元素
    ```c++
    copy(vec.begin(), vec.end(), outer_iter);
    cout << endl;	// 比循环打印简单
    ```

* 可以为任何定义了>> 的对象创建istream_iteraotr，同理<<

#### 10.4.3 反向迭代器

（除forward_list之外都支持）

调用rbegin，rend，crbegin，crend来获得反向迭代器

* 需要递减运算符

* ```c++
  // 在逗号分隔的列表中查找最后一个元素
  auto rcomma = find(line.crbegin(), line.crend(),',');
  ```

* 注意，正常打印别用反向迭代器，不然会逆序输出
  ```c++
  cout << string(line.crbegin(), rcomma) << endl;
  // 用base成员函数可以让rcomma转换为普通迭代器，能正向移动
  ```

  

### 10.5 泛型算法结构

* 依照算法所要求的迭代器操作，可以分为5个迭代器类别(iterator category)

  * 输入迭代器
    读取序列中的元素
  * 输出迭代器
    只写不读
  * 前向迭代器
    读写，一个方向，而且课已多次读写一个元素
  * 双向迭代器
    双向++--
  * 随机访问迭代器
    提供常量时间内访问序列中任意元素的额能力

* 算法形参模式：
  ```c++
  arg(beg, end, other args);
  arg(beg, end, dest, other args);
  arg(beg, end, beg2, other args);	// 假定两个范围大小相同
  arg(beg, end, beg2, end2, other args);
  ```

* 算法命名规范

  * 使用重载形式传递一个谓词
    ```c++
    unique(beg, end);	// ==
    unique(beg, end, comp);	// comp
    ```

  * `_if` 版本的算法

    ```c++
    find(beg, end, val);	// val第一次出现的位置
    find(beg, end, pred);	// 查找第一个令pred为真的元素
    ```

  * 区分拷贝元素的版本和不拷贝的版本
    ```c++
    reverse(beg, end);
    reverse_copy(beg, end, dest);	// 逆序拷贝进dest
    ```

  * 同时提供:
    ```c++
    remove_copy_if(v1.begin(), v1.end(), back_inserter(v2), 
                  [](int i){ return i % 2; });
    ```

* 特定容器算法

  list, forward_list
  ```c++
  lst.merege(lst2);	// 必须两个有序
  lst.merge(lst2.comp);	 // 用给定的比较操作
  lst.remove(val);
  lst.remove_if(pred);
  lst.reverse();
  lst.sort();
  lst.sort(cmp);
  lst.unique();	// 使用 ==
  lst.unique(pred);	// 使用给定的二元谓词
  ```

* splice 成员
  链表数据结构所特有的

  ```
  lst.splice(args) （之前）或者 flst.splice_after(args) （之后）
  args:
  (p, lst2)
  (p, lst2, p2)
  (p, lst2, b, e)
  ```

  链表特有操作会改变容器。

## Sec13 拷贝控制

当定义一个类，我们显示或者隐式指定此类型的对象拷贝、移动、赋值或者销毁时做什么

* 五种特殊成员函数
  * 拷贝构造函数 copy constructor
  * 拷贝赋值运算符 copy-assignment operator
  * 移动构造函数 move constructor
  * 移动赋值运算符 move-assignment operator
  * 析构函数 destructor
