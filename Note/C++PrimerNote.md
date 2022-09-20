# C++ Primer Note

*��ʼʱ��: 9��4��*

## Sec1 Begin

## Sec2 �����ͻ�������

### 2.1 ������������

* ������:
    * �޷������͸�����ӡ����Ƚ�����ת��Ϊ�޷������ٽ������
    * �޷����������������ζ�������Ϊ�����������Ϊ���������ֱ�Ӱ��ձ���λ����ȡ�޷�����
    * �����޷��ź��з����ͣ�������ˣ��ÿ�������int��ռλ������
* ת�����У�escape sequence�� 
    * \\ �����3���ַ�������ת������� 
        * ���ӣ�\\1234����ʾת���ַ�\\123���ַ�4
* 0��ͷ����Ϊ8����������0X��ͷ��Ϊ16������
* ��ʾ��������
    * ������`1024f`����ȷӦ��Ϊ`1024.f`

### 2.2 ����

* ��ʼ��

  * �б��ʼ��

    ```
    long double ld = 3.14159   
    int a{ld}, b = {ld};	// �������ڶ�ʧ��Ϣ����
    int a(ld), b = ld;    	// ��ȷ������ʧ����ֵ
    ```

  * Ĭ�ϳ�ʼ��
    û��ָ����ֵ��Ĭ�ϳ�ʼ��

    * �������κκ���֮��ı�������ʼ��Ϊ0
    * �����ں������ڲ����������ͱ�����������ʼ�� uninitialized
    * ÿ������Ծ�����ʼ������ķ�ʽ
      �Ƿ񲻾�����ʼ���Ͷ������Ҳ�����Լ�����
    * �����ʼ��ÿһ���������͵ı���

  * �����Ͷ��壺
    ���������涨�˱��������ͺ����֣�����Ҳһ������ͬ�����ڣ����廹����洢�ռ䣬Ҳ���ܻ��������һ����ʼֵ
    �κΰ�����ʾ��ʼ��������������Ϊ����

    ```
    extern int i;	// ����i�����Ƕ���i
    int j;			// ����������j
    extern double pi = 3.14 // ����
    ```

    �����ڲ��������ͼ��ʼ��һ����extern�ؼ��ֱ�ǵı�������������
    ��������ֻ�ܱ�����һ�Σ������Ա��������

  * ������
    scope

  ### 2.3 �������� (Compound Type)

  * ���ã�reference

    * lvalue reference
      һ��ָ����ֵ���� \&

      һ��Ҫ��ʼ������������ʱ����������������ĳ�ʼֵbind����һ�𣬶����ǽ���ʼֵ���������á�
      һ����ʼ����ɣ����ý������ĳ�ʼֵ����һֱ����һ����Ϊ�޷����������°�����һ������������ñ����ʼ����
      ������ֻ��Ϊһ���Ѿ����ڵı�����һ��������

  * ָ�� pointer

    \&��ȡ��ַ��
    \*�������÷�

    * ��ָ�룺
      nullptr����ת��Ϊ����������ָ������

      ```
      int *p1 = nullptr; // ����
      int *p2 = 0;
      int *p3 = NULL; // (Ԥ���������preprocessor variable��)
      ```

    * void\* ָ�� 
      ����ֱ�Ӳ�������Ϊ���ǲ�֪����ʲô����

    * ָ��ָ������ã������ܶ���ָ�����õ�ָ�룬��Ϊ���ò��Ƕ���
      ```
      int i  = 42;
      int *p;
      int *&r = p; // r��һ����ָ��p�����ã���������
      
      r = &i;  // r������һ��ָ�룬��˸�r��ֵ��&i, ������pָ��i
      ```

  ### 2.4 const�޶���

* const��������ʼ��

* ���ļ�ʹ��ͬһ��const��
  ÿ���ļ�����  `extern const int bufSize`  // ����,����extern

* **const������**
  (reference to const)

  * ```
    const int ci = 1024;
    const int &r1 = ci; 	// ���ü����Ӧ�Ķ����ǳ���
    r1 = 42; 	// ����
    int &r2 = ci;	// ������һ���ǳ�������ָ��һ����������
    ```

  * ```
    int i = 42;
    const int &r2 = 42;	// ��ȷ���������ã��������԰�������ʽ��Ϊ��ʼֵ����������ֵ��
    const int &r1 = i; 	// ��ȷ����������
    const int &r3 = r1*2;	// ��ȷ����������
    int &r4 = r1 * 2;	// ����r4��һ����ͨ�ķǳ�������
    ```

    Ϊʲôr4�Ǵ������ã�
    ���ӣ�

    ```
    double dval = 3.14;
    const int &ri = dval;
    --> ��������������������һ��temp����
    const int temp = dval;
    const int &ri = temp;
    ����ri��������dval,����������һ�����ص�temp������Ȼ����
    ```

  * ��const�����ÿ�������һ������const�Ķ���
    ```
    int i = 42;
    const int &ri = i; 
    // ���������ͨ��ri�����޸�i��ֵ��
    ```

  * �������ã�
    ```
    const int &r = 0;
    // �Ϸ�����Ϊ�ǳ������ã����Կ��԰��ڳ����ϡ�
    ```

  * �Ƿ������Σ����������ú㶨����
    ����:`const int &const r2`:
    �Ƿ������ò��Ƕ������Բ��������ú㶨���䣡

  * ָ���const
    ```
    const double pi = 3.14;		// ����һ��const����
    double *ptr = &pi;			// ������Ϊptr����ָͨ�룬����ָ����
    const double *cptr = &pi;	// ��ȷ��cptr����ָ��һ������
    *cptr = 42;					// ���󣬲��ܸ�������ֵ
    ```

    * ָ����������ָ����һ�µ����⣺

      1. **����һ��ָ������ָ�룬ָ��һ���ǳ�������**

         ```
         double dval = 3.14;
         cptr = &dval;	// ��ȷ�����ǲ���ͨ��cptr�ı�dval��ֵ
         ```

         ��ָ������ָ�룬**����Ҫ����ͨ����ָ��ı�����ֵ**����
         ��ָ����������Ҳ��һ������

      2. ����ָ�� const pointer
         �����ʼ��
         ��ʾ�������ָ���ֵ��������ָ����Ǹ�ֵ��ָ�򲻱䣡��

         ```\
         int errNumb = 0;
         int *const curErr = &errNumb;	// *�ŷ���const֮ǰ��˵��ָ����һ������
         const double pi = 3.14
         const double *const pip = &pi;	// pip��ָ��������ĳ���ָ��
         ```

         * ��α��
           ���������Ķ���
           ����:

           ```
           const int *const curErr = &errNumb;
           ��curErr�������const������curErr��һ����������
           Ȼ����������ͣ��������������ಿ�־���
           ��������һ����*����˼��curErr��һ������ָ�룬
           ���const int��ʾ����ָ��ָ�����һ��int��������
           ```

           ָ���ǳ�����������ζ�Ų���ͨ��ָ���޸�ָ���ֵ������Ҫ��ָ��Ķ�������ͣ�

         * �Ƿ����ӣ�
           ```
           int *p1;
           const int *const p3;
           p1 = p3;
           // �Ƿ���p1�����޸���ָ���ֵ������p3���ܱ��޸ģ��﷨�ϴ���
           ```

           

* ����(top-level) const / �ײ�(low-level) const

  * ����const����ʾָ�뱾���ǳ��� ��������ı�����ֵ��

  * �ײ�const����ʾָ����ָ������const ������ı�����ֵ��
    �����������õ�const���ǵײ�const

  * �����ϵ�����

    * ���������Զ���const��Ӱ��

    * ���������Եײ�const��˵���������߱��������ͬ�ĵײ�const�ʸ�

    * �������磺
      ```
      int i = 0;
      const int ci = 42;
      int &r = ci; 			// ������ͨint���ܰ���һ��const int��
      const int &r2 = i;		// ��ȷ��const int���԰�����ͨint��
      ```

  * �����Լ����ǳ���
    �ף�ָ��Ķ����ǳ���

* constexpr�ͳ������ʽ

  * �������ʽ��
    ֵ����ı���**������̾��ܵõ��������ı��ʽ**
  * constexpr����
    * ������ָ�룬ֻ��ʾ����ָ�루����const��
    * ��Ҫ����ֵ���� literal type
    * constexprָ���ʼ������Ϊ0����nullptr

### 2.5 ��������

* ���ͱ��� ��type alias��
  ```c++
  typedef double wages;
  typedef wages base, *p;
  ```

  *  �������� ��alias declaration��

    ```
    using SI = Sales_item;
    ```

  * ע��ĵ㣺
    ```c++
    typedef char *pstring;	// pstring��ָ��char��ָ��
    const pstring cstr = 0;	// cstr ��ָ��char�ĳ���ָ��
    const pstring *ps;		// ps��ָ�룬ָ��ָ��char��ָ��
    ```

* auto����˵����
  Ŀ�ģ������Ὣ���ʽ��ֵ��������������Ҫ֪�����ʽ�����ͣ���������auto�������Ϳ����Զ�ת�������ˡ�

  `auto`������һ����������������������Ϊһ���������ֻ����һ�������������ͣ����Ը���������б����ĳ�ʼ�����������Ͷ�����һ��

  ```c++
  auto i = 0, *p = &i;	// ��ȷ������һ��
  auto sz = 0, pi = 3.14	// ����
  ```

  * `auto` һ�����Զ���const�������ײ�const

    ```c++
    const int ci = i, &cr = ci;
    auto b = ci;					// b ��һ��������ci�Ķ���const������
    auto c = cr;					// c ��һ������, cr��ci�ı�����ci��һ������const������Ҳ������
    auto d = &i;					// d��һ������ָ�룬�����ĵ�ַ����ָ��������ָ��
    auto e = &ci;					// e��һ��ָ������������ָ�� ���Գ�������ȡ��ַ��һ�ֵײ�const��
    ```

    ���ϣ���ƶϳ���auto��һ������const����Ҫ��ȷָ��
    `const auto f = ci;`

    �����Խ����õ���������Ϊauto
    ```c++
    auto &g = ci;		// g��һ�����ͳ�������
    auto &h = 42;		// ���󣬲��ܽ��ǳ������ð�����ֵ
    const auto &j = 42;	// ��ȷ�����Խ��������ð�����ֵ
    ```

* decltype����ָʾ��

  ������ѡ�񲢷��ز��������������� ���õ����͵���ʵ�ʼ�����ʽ��ֵ��
  `decltype(f()) sum = x;  // sum�����;��Ǻ���f�ķ�������`	

  ��decltypeʹ�õı��ʽ��һ����������decltype���ظñ��������ͣ���������const����������
  ������ʽ��һ�������ã����õ���������

  ```c++
  int i = 42, *p = &i, &r = i;
  decltype(r+0) b;	// ��ȷ�������int����
  decltype(*p) c;	// ����c��int&���ͣ����Ա����ʼ��
  ```

  ```c++
  // ע�⣬��������Ǽ������ŵı����������������
  decltype((i)) d;	// ����dΪint&,�����ʼ��
  decltype(i) e;		// ��ȷ
  ```

   

## Sec3 �ַ���������������

### 3.1 using

using namespace::name

### 3.2 string:

* ��ʼ����
  ```
  string s1;
  string s2(s1);
  string s2 = s1;
  string s3("value");
  string s3 = "value";	// ������ʼ�� �����˵Ⱥ� = ��
  string s4(n,"c");
  ```

* ����
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


* cctypeͷ�ļ�
  ```
  isalnum(c)
  isalpha(c)
  iscntrl(c)
  isgraph(c)	ispunct(c)
  islower(c)	tolower(c)
  isupper(c)	toupper(c)
  isxdigit(c)
  ```

* ����ÿһ���ַ�
  ```c++
  for(declaration : expression){
  	statement;
  }
  ```

  ```c++
  // ���ӣ�
  string str("swafasgdsvsaefwqa");
  for(auto c : str)
  	cout << c << endl;
  ```

### 3.3 Vector

 `vector<int> ivec;|`
vector��ģ�壬�������ͣ�

* ��ʼ����

  1. �б��ʼ��
     ֻ���û�����
  2. ������ʼ��

  3. ����ָ��������Ԫ��
  4. ֵ��ʼ��
     ��ָ��Ԫ������
     ��������ֻ����ֱ�ӳ�ʼ���������е���һ��Ҫ��ʼ��ָ��ֵ��

  ```c++
  // ����
  vector<int> v1(10);
  vector<int> v2{10};
  vector<int> v3(10,1);
  vector<int> v4{10,1};
  // ע��Ҫ�ǲ�ͬ����
  vector<string> v5{"hi"};	// �б��ʼ��
  vector<string> v6("hi");	// ���󣬲������ַ�������ֵ����vector����
  vector<string> v7{10};
  vector<string> v8{10, "hi"};
  ```

* ��������
  ```c++
  v.empty()
  v.size()
  v.push_back(t)
  v[n]
  ```

* ```
  vector<int>::size_type // ��ȷ
  vector::size_type; // ����
  ```

* �������±���ʽ���Ԫ��

### 3.4 ������

* ```
  v.begin()
  v.end()			// β�������,off the end. ָ��������һ���������ڵ�β��
  ������Ϊ�գ���v.begin() == v.end()
  ```

* ���������
  ```c++
  *iter
  iter->mem
  ++iter
  --iter
  iter1 == iter2
  iter1 != iter2
  ```

* ʹ�ã�
  ```c++
  string s("awefdwafefga");
  if(s.begin() != s.end())	// �������ǿ�
  {
      auto iter = s.begin();	// �������������
      *iter = touppper(*iter);// ��������ֱ�ӷ���
  }
  ```

  ```c++
  // ����һ������ת��Ϊ��д
  for(auto iter = s.begin(); iter != s.end() && !isspace(*iter); ++iter){
      *iter = toupper(*iter);
  }
  ```

* ����������

  const_iterator: ֻ����д
  iterator
  ���vector�������string������һ����������ֻ��ʹ��const_iterator

  ```c++
  vector<int> v;
  const vector<int> cv;
  auto it1 = v.begin()	// it1��������vector<int>::iterator
  auto it2 = cv.begin()	// it2��������vector<int>::const_iterator
  ```

  * begin��end ���صľ��������ɶ����Ƿ�Ϊ����������
    `const_iterator`
    `iterator`
  * �����Ҫ�Ƕ���ֻ��Ҫ������������д���������ʹ�ó������͡�
    `cbegin()`
    `cend()`
    ���Է��س������͵����������ܶ����ǲ��ǳ���

* �������Ľ�����
  ```
  // ע�⣺
  (*iter).mem �� *iter.mem�����ͬ��������������ȼ��ǱȽ�������������ߵ�
  (*it).empty();	// �����ã�����empty��Ա
  *it.empty();	// ����it�Ǹ���������û��empty��Ա
  
  �򻯣�
  (*it).mem �ȼ��� it->mem
  ```

* **ĳЩ��vector����Ĳ�����ʹ������ʧЧ**
  * �����ڷ�Χforѭ������vector�������Ԫ��
  * �κ�һ�ֿ��ܸı�vector���������Ĳ���������push_back������ʹ��vector����ĵ�����ʧЧ��
    ������ʹ���˵�������ѭ���壬����Ҫ���������������������Ԫ�أ�

* ����������
  ```
  iter+n
  iter-n
  iter1 += n
  iter1 -= n
  iter1 - iter2	// �������໥֮��ľ���
  ```

  * ���ӣ��õ��������м��Ԫ��
    ```
    auto mid = vi.begin() + vi.size() / 2
    ```

    ��������ͣ�`difference_type`�Ĵ�����������

  * ����2������������
    ```c++
    // Binary search
    // text �����������
    // beg��end��ʾ���������ķ�Χ
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

* 





