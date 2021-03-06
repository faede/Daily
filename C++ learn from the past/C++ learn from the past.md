### mutable

[*lambda-declarator* ](https://en.cppreference.com/w/cpp/language/lambda)that removes `const` qualification from parameters captured by copy (since C++11)

### decltype 

推导规则如下:

1) If the argument is an unparenthesized [id-expression](https://en.cppreference.com/w/cpp/language/identifiers) or an unparenthesized [class member access](https://en.cppreference.com/w/cpp/language/operator_member_access) expression, then decltype yields the type of the *entity* named by this expression. If there is no such entity, or if the argument names a set of overloaded functions, the program is ill-formed.

| If the argument is an unparenthesized [id-expression](https://en.cppreference.com/w/cpp/language/identifiers) naming a [structured binding](https://en.cppreference.com/w/cpp/language/structured_binding), then decltype yields the *referenced type* (described in the specification of the structured binding declaration). | (since C++17) |
| ------------------------------------------------------------ | ------------- |
| If the argument is an unparenthesized [id-expression](https://en.cppreference.com/w/cpp/language/identifiers) naming a [non-type template parameter](https://en.cppreference.com/w/cpp/language/template_parameters#Non-type_template_parameter), then decltype yields the type of the template parameter (after performing any necessary type deduction if the template parameter is declared with a placeholder type). | (since C++20) |

2) If the argument is any other expression of type `T`, and

​	a) if the [value category](https://en.cppreference.com/w/cpp/language/value_category) of *expression* is *xvalue*, then decltype yields `T&&`;

​	b) if the value category of *expression* is *lvalue*, then decltype yields `T&`;

​	c) if the value category of *expression* is *prvalue*, then decltype yields `T`.

| If *expression* is a function call which returns a prvalue of class type or is a [comma expression](https://en.cppreference.com/w/cpp/language/operator_other) whose right operand is such a function call, a temporary object is not introduced for that prvalue. | (until C++17) |
| ------------------------------------------------------------ | ------------- |
| If *expression* is a prvalue other than a (possibly parenthesized) [immediate invocation](https://en.cppreference.com/w/cpp/language/consteval) (since C++20), a temporary object is not [materialized](https://en.cppreference.com/w/cpp/language/implicit_cast#Temporary_materialization) from that prvalue: such prvalue has no result object. | (since C++17) |

The type need not be [complete](https://en.cppreference.com/w/cpp/language/incomplete_type) or have an available [destructor](https://en.cppreference.com/w/cpp/language/destructor), and can be [abstract](https://en.cppreference.com/w/cpp/language/abstract_class). This rule doesn't apply to sub-expressions: in decltype(f(g())), g() must have a complete type, but f() need not.

```cpp
#include <iostream>
 
struct A { double x; };
const A* a;
 
decltype(a->x) y;       // type of y is double (declared type)
decltype((a->x)) z = y; // type of z is const double& (lvalue expression)
 
template<typename T, typename U>
auto add(T t, U u) -> decltype(t + u) // return type depends on template parameters
                                      // return type can be deduced since C++14
{
    return t + u;
}
 
int main() 
{
    int i = 33;
    decltype(i) j = i * 2;
 
    std::cout << "i = " << i << ", "
              << "j = " << j << '\n';
 
    auto f = [](int a, int b) -> int
    {
        return a * b;
    };
 
    decltype(f) g = f; // the type of a lambda function is unique and unnamed
    i = f(2, 2);
    j = g(3, 3);
 
    std::cout << "i = " << i << ", "
              << "j = " << j << '\n';
}
```

### 如何禁用vs安全检查

#define _CRT_SECURE_NO_WARNINGS

### 友元函数

类的友元函数是定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数。

### constexpr

The `constexpr` specifier declares that it is possible to evaluate the value of the function or variable at compile time. Such variables and functions can then be used where only compile time [constant expressions](https://en.cppreference.com/w/cpp/language/constant_expression) are allowed (provided that appropriate function arguments are given). A constexpr specifier used in an object declaration or non-static member function (until C++14) implies const. A constexpr specifier used in a function or [static](https://en.cppreference.com/w/cpp/language/static) member variable (since C++17) declaration implies inline. If any declaration of a function or function template has a `constexpr` specifier, then every declaration must contain that specifier.

### lambda



### Memory Layout of C Programs

A typical memory representation of C program consists of following sections.

1. Text segment
2. Initialized data segment
3. Uninitialized data segment
4. Stack
5. Heap

![memoryLayoutC](./memoryLayoutC.jpg)

 **1. Text Segment:**

A text segment , also known as a code segment or simply as text, is one of the sections of a program in an object file or in memory, which contains executable instructions.

As a memory region, a text segment may be placed below the heap or stack in order to **prevent heaps and stack overflows from overwriting it**.

Usually, the text segment is sharable so that only a single copy needs to be in memory for frequently executed programs, such as text editors, the C compiler, the shells, and so on. Also, the text segment is **often read-only**, to prevent a program from accidentally modifying its instructions.

**2. Initialized Data Segment:**

Initialized data segment, usually called simply the Data Segment. A data segment is a portion of virtual address space of a program, which contains the global variables and static variables that are initialized by the programmer.

Note that, data segment is **not read-only**, since the values of the variables can be altered at run time.

This segment can be further classified into **initialized read-only area** and **initialized read-write area**.

For instance the **global** string defined by **char s[] = “hello world”** in C and a C statement **like int debug=1** outside the main (i.e. global) would be stored **in initialized read-write area**. And a **global** C statement like **const char* string = “hello world”** makes the **string literal “hello world” to be stored in initialized read-only area** and the **character pointer variable string in initialized read-write area**.

Ex: static int i = 10 will be stored in data segment and global int i = 10 will also be stored in data segment

**3. Uninitialized Data Segment:**

Uninitialized data segment, often called the **“bss” segment**, named after an ancient assembler operator that stood for “block started by symbol.” Data in this segment is **initialized by the kernel to arithmetic 0 before the program starts executing**

uninitialized data starts at the end of the data segment and contains all global variables and static variables that are initialized to zero or do not have explicit initialization in source code.

For instance a variable declared **static int i**; would be contained in the BSS segment.

For instance a global variable declared **int j**; would be contained in the BSS segment.

**4. Stack:**

The stack area traditionally **adjoined the heap area and grew the opposite direction**; when the stack **pointer met the** heap pointer, **free memory was exhausted**. (With modern large address spaces and virtual memory techniques they may be placed almost anywhere, but they still typically grow opposite directions.)

The stack area contains the program stack, a LIFO structure, typically located in the higher parts of memory. On the **standard PC x86 computer architecture** it **grows toward address zero**; on some other architectures it grows the opposite direction. A **“stack pointer”** register tracks the top of the stack; it is **adjusted each time a value is “pushed” **onto the stack. The **set of values pushed** for one function call is termed **a “stack frame”**; A stack frame consists at minimum of a return address.

Stack, where **automatic variables** are stored, along with information that is saved each time a function is called. Each time a function is called, the address of where to return to and certain information about the caller’s environment, such as some of the machine registers, are saved on the stack.**The newly called function then allocates room on the stack for its automatic and temporary variables**. This is how recursive functions in C can work. Each time a recursive function calls itself, a new stack frame is used, so one set of variables doesn’t interfere with the variables from another instance of the function.

**5. Heap:**

Heap is the segment where **dynamic memory allocation usually takes place**.

The heap area begins at the **end of the BSS segment** and **grows to larger addresses** from there.The Heap area is **managed by malloc, realloc, and free**, which may use the brk and sbrk system calls to adjust its size (note that the use of brk/sbrk and a single “heap area” is not required to fulfill the contract of malloc/realloc/free; they **may** also be implemented using **mmap** to **reserve potentially non-contiguous regions of virtual memory into the process’ virtual address space**). **The Heap area is shared by all shared libraries and dynamically loaded modules in a process**.

Examples.

The size(1) command reports the sizes (in bytes) of the text, data, and bss segments. ( for more details please refer man page of size(1) )

1. Check the following simple C program

```c
#include <stdio.h> 
  
int main(void) 
{ 
    return 0; 
} 
```

```shell
[narendra@CentOS]$ gcc memory-layout.c -o memory-layout
[narendra@CentOS]$ size memory-layout
text       data        bss        dec        hex    filename
960        248         8          1216       4c0    memory-layout
```

2. Let us add one global variable in program, now check the size of bss (highlighted in red color).

```c
#include <stdio.h> 
  
int global; /* Uninitialized variable stored in bss*/
  
int main(void) 
{ 
    return 0; 
} 
```

```shell
[narendra@CentOS]$ gcc memory-layout.c -o memory-layout
[narendra@CentOS]$ size memory-layout
text       data        bss        dec        hex    filename
960        248         12         1220       4c4    memory-layout
#last
960        248         8          1216       4c0    memory-layout
```

3. Let us add one static variable which is also stored in bss.

```c
#include <stdio.h> 
  
int global; /* Uninitialized variable stored in bss*/
  
int main(void) 
{ 
    static int i; /* Uninitialized static variable stored in bss */
    return 0; 
} 

```

```shell
[narendra@CentOS]$ gcc memory-layout.c -o memory-layout
[narendra@CentOS]$ size memory-layout
text       data        bss        dec        hex    filename
960        248         16         1224       4c8    memory-layout
#last
960        248         12         1220       4c4    memory-layout
```

4. Let us initialize the static variable which will then be stored in Data Segment (DS)

```c
#include <stdio.h> 
  
int global; /* Uninitialized variable stored in bss*/
  
int main(void) 
{ 
    static int i = 100; /* Initialized static variable stored in DS*/
    return 0; 
} 
```

```shell
[narendra@CentOS]$ gcc memory-layout.c -o memory-layout
[narendra@CentOS]$ size memory-layout
text       data        bss        dec        hex    filename
960        252         12         1224       4c8    memory-layout
#last
960        248         12         1220       4c4    memory-layout
```

5. Let us initialize the global variable which will then be stored in Data Segment (DS)

```c
#include <stdio.h> 
  
int global = 10; /* initialized global variable stored in DS*/
  
int main(void) 
{ 
    static int i = 100; /* Initialized static variable stored in DS*/
    return 0; 
} 
```

```shell
[narendra@CentOS]$ gcc memory-layout.c -o memory-layout
[narendra@CentOS]$ size memory-layout
text       data        bss        dec        hex    filename
960        256         8          1224       4c8    memory-layout
#last
960        248         8          1216       4c0    memory-layout
```

### 字符串转换

c = > c++

```cpp
string s;
char a[10];
s = a;
```



c++ => c

```cpp
string str("test");
const char *s = str.c_str(); // const不能省略
// 进一步？
string s2 = s;
```



输出到字符串

```cpp
char buf[10];
sprintf(buf,"test");
cout<<buf;
```



### inplace_merge

```cpp
#include <vector>
#include <iostream>
#include <algorithm>
 
template<class Iter>
void merge_sort(Iter first, Iter last)
{
    if (last - first > 1) {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle);
        merge_sort(middle, last);
        std::inplace_merge(first, middle, last);
    }
}
 
int main()
{
    std::vector<int> v{8, 2, -2, 0, 11, 11, 1, 7, 3};
    merge_sort(v.begin(), v.end());
    for(auto n : v) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}
```



### C语言中的强符号与弱符号

https://blog.csdn.net/astrotycoon/article/details/8008629

### %i

scanf读入数字 将0开头解析为8进制,0x开头16进制

### C语言数组下标可以为负数

个人觉得[]被实现为*(array+i)的话那自然要和i为负数的时候统一.

并且似乎将指针索引隐式转换成正数并不能带来什么好处, 访问一个很大的索引未必比访问一个绝对值小的负数来的更加安全(虽然可能都是危险行为)

### 探索C++析构函数

深度探索c++对象模型:

```
如果class没有定义destructor,那么只有在class内含有member object(异或class自己的bass class)拥有destructor 的情况下,编译器才会合成一个出来.否则,destructor被视为不需要,也就不需被合成(当然更不需要被调用).
```

如果我们定义了其它构造函数,但是没有定义默认构造函数,是不允许的

比如

```cpp
class A{
  public:
  ~A(int i){}
};//错误
```

如下正确:

```cpp
class A{
  public:
  ~A(int i){}
  ~A(){}
};
```



在函数体中我们可以显示的调用析构函数,但是显示调用析构函数并不会释放对象的空间,(其实我们不应该显示调用析构函数). (当然vs下可能不同 合情(一贯风格)推理vs做了骚操作)

并且我们可以通过添加`{}`来改变对象的作用域,并且离开`{}`的作用域的时候会调用析构函数,并且如果离开的是我们定义的函数那么对象会被销毁.其他对象main函数前



总的来说编译器会在对象离开作用域前添加对析构函数的调用.

进一步举证如下:



曾经想法:

```
对于析构函数来说真正的对象销毁工作应该在对象离开对象的作用域时,但是最终调用的对象析构函数应该是发生在main函数返回(return )前的,所以我推测编译器在最后为代码添加了析构函数的调用,

当然也有可能最终函数的执行会交由外部函数处理,但我觉得并不合理,内外部函数存放的位置不同,如果没有其它未知操作的话,外部执行最后的析构函数会导致相同的代码在不同的段存放两次,这感觉并不是很合理,除非两段会共用,不过具体情况也就不得而知了.

综上所述,就目前来讲,对象的析构函数还是不要显示调用来的好(当然除了数组需要delete的情况).
```

实践:

确实是编译器添加了析构函数的调用

我用了在线汇编

```cpp
#include<iostream>
using namespace std;
class A{
int a;
int b;
public:
	~A(){
	}
};
int main(){
	A a;
}

```



```
A::~A() [base object destructor]:
        push    rbp
        mov     rbp, rsp
        mov     QWORD PTR [rbp-8], rdi
        nop
        pop     
        ret
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        lea     rax, [rbp-8]
        mov     rdi, rax
        call    A::~A() [complete object destructor]
        mov     eax, 0
        leave
        ret
__static_initialization_and_destruction_0(int, int):
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16
        mov     DWORD PTR [rbp-4], edi
        mov     DWORD PTR [rbp-8], esi
        cmp     DWORD PTR [rbp-4], 1
        jne     .L6
        cmp     DWORD PTR [rbp-8], 65535
        jne     .L6
        mov     edi, OFFSET FLAT:_ZStL8__ioinit
        call    std::ios_base::Init::Init() [complete object constructor]
        mov     edx, OFFSET FLAT:__dso_handle
        mov     esi, OFFSET FLAT:_ZStL8__ioinit
        mov     edi, OFFSET FLAT:_ZNSt8ios_base4InitD1Ev
        call    __cxa_atexit
.L6:
        nop
        leave
        ret
_GLOBAL__sub_I_main:
        push    rbp
        mov     rbp, rsp
        mov     esi, 65535
        mov     edi, 1
        call    __static_initialization_and_destruction_0(int, int)
        pop     rbp
        ret
```

clang(只截取一部分):

```assembly
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	leaq	-8(%rbp), %rdi
	callq	__ZN1AD1Ev
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN1AD1Ev              ## -- Begin function _ZN1AD1Ev
	.weak_def_can_be_hidden	__ZN1AD1Ev
	.p2align	4, 0x90
__ZN1AD1Ev:                             ## @_ZN1AD1Ev
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdi
	callq	__ZN1AD2Ev
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	__ZN1AD2Ev              ## -- Begin function _ZN1AD2Ev
	.weak_def_can_be_hidden	__ZN1AD2Ev
	.p2align	4, 0x90
```



```cpp
#include<iostream>
using namespace std;
class A{
int a;
int b;
public:
	~A(){
	}
};
int main(){
	A a;
    A a2;
    {
        A b;
    }
    int c = 1;
    c += 2;
}

```

```assembly
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 32
        lea     rax, [rbp-28]
        mov     rdi, rax
        call    A::~A() [complete object destructor]
        mov     DWORD PTR [rbp-4], 1
        add     DWORD PTR [rbp-4], 2
        lea     rax, [rbp-20]
        mov     rdi, rax
        call    A::~A() [complete object destructor]
        lea     rax, [rbp-12]
        mov     rdi, rax
        call    A::~A() [complete object destructor]
        mov     eax, 0
        leave
        ret
```

### 函数指针

```cpp
#include <iostream>
using namespace std;
void foo(){
    std::cout << 2 << endl;
}
int add(int a,int b){
    return a+b;
};
int main(){
    int c;
    void (* p1) () = foo;
    typedef void (*fp)();
    fp p2 = foo;
    p1();
    int (*a1)(int,int) = add;
    c = a1(1,3);
    std::cout << c <<endl;
    typedef int(*af) (int,int) ;
    af a2 = add;
    c = a2(5,6);
    std::cout << c <<endl;
}
```

### 初始化

类的成员变量有三个位置进行初始化：

声明时初始化:

初始化列表初始化（ 成员变量初始化的顺序是按照在那种定义的顺序）

以下三种情况下必须使用初始化成员列表
一、需要初始化的数据成员是对象，且该对象不能默认构造。(这里包含了继承情况下，通过显示调用父类的构造函数对父类数据成员进行初始化)；因为使用初始化列表可以不必调用默认构造函数来初始化，而是直接调用拷贝构造函数初始化。
二、需要初始化const修饰的类成员；（C++11后，声明时初始化也可以）
三、需要初始化引用成员数据；

 对于一补充:

c++ primer P258

```
如果没有构造函数的初始化列表中显式地初始化成员,
则该成员将在构造函数体之前执行默认初始化.
```

所以对于类成员,我们需要定义默认初始化,或者在初始化列表中初始化



变量初始化顺序:

c++ primer

```cpp
不过稍让人意外的是,构造函数初始值列表只用于初始化成员的值,而不限定初始化执行的顺序.
成员的初始化顺序与它们在类定义中的出现顺序一致:第一个成员先被初始化,然后第二个,以此类推. 构造函数初始化列表中初始化值的前后位置关系不会影响实际的初始化顺序.
一般情况下初始化的顺序没什么要求,如果如果一个成员使用另一个成员来初始化的,那么这两个成语啊你的初始化顺序就很关键了.
  举个例子,考虑下面这个类
class X{
  int i;
  int j;
  public:
  //未定义的,i在j之前初始化
  X(int val):j(val),i(j){}
  
  // 补充:  X(int val):i(val),j(i){}   OK
};
有些编译器具备一项比较友好的功能,即当构造函数和初始化列表中的数据成员顺序与这些成员声明的顺序不符时会生成一条警告信息.
```



构造函数内赋值初始化成员变量:

对于内置类型（char，int……指针等）:

> 基本上是没有区别的，效率上也不存在多大差异

对于自定义类对象的成员初始化

- 初始化列表是直接调用拷贝函数构造；
- 构造函数内赋值是先调用默认构造函数构造（当然，你得保证你定义的类有无参构造函数），在调用重载赋值函数赋值
  所以使用初始化列表效率高很多。**能使用初始化列表的时候尽量使用初始化列表**



### 委托构造函数

一个委托构造函数使用它所属类的其他构造函数执行它自己的初始化过程,或者说把它自己的一些(或者全部)指责委托给了其他函数

```cpp
class Sales_data{
  // 非委托构造函数
  Sales_data(string s,int a):name(s),num(a){
  }
  // 委托构造函数
  Sales_data():Sales_data("",0){}
}
```

### 指针与数组并不相同

《C专家编程》

对于

```cpp
char a[9]  = "abcdefg";       c = a[i];
编译器符号表具有一个地址9980
  运行时步骤1:取i的值,并将它与9980相加
  运行时步骤2:取地址(9980+i)的内容
```



```cpp
char *p;       c = *[p];
编译器符号表具有一个符号p,它的地址为4624
  运行时步骤1:取地址4624的值,就是 '5081'
  运行时步骤2:取地址5081的内容
```

多了一次额外的提取



当你定义为指针,但以数组方式引用

```cpp
char *p  = "abcdefg";       c = p[i];
编译器符号表具有一个p,地址为4624
  运行时步骤1:取地址4624的内容,就是 '5081'
  运行时步骤2:取得i的值,并将它与5081相加.
  运行时步骤3:取地址(5081+i)的内容
```





### 什么时候数组和指针是一样的

The C Programming Language  ed. 2 ,P99

```cpp
as format parameters in function definition
  char s[];
and 
  char* s;
are equivalent;
```

1.表达式中的数组名(与声明不同)被编译器当作指向该数组第一个元素的指针

2.下标总是与指针的偏移量相同

3.在函数参数的生命中,数组名被编译器当作指向该数组第一个元素的指针.

### 可以返回一个数组首地址吗?

局部数组不可以:

```cpp
int temp[arrlen]; 
```

动态数组可以:

```cpp
int *temp = new int[arrlen];
```

这自然是因为两个数组中变量存储的位置不同

### void main 与 main(void)

第二个答案:

`https://www.zhihu.com/question/358133724`

![voidmain](./voidmain.jpg)

```
Returns:  a pointer to void if successful, or NULL if not.
```



void main似乎是一个遗留问题,

在之后void main应该是个ub ,编译器不会执行类型检查,汇编正常执行

有的编译器或许会添加上return 0;

而对于main(void):

取自:https://www.zhihu.com/question/358133724

C语言是调用者清栈，所以main函数不写参数也可以，比如 main(void)，不会运行出错，只是函数里拿不到命令行参数，但是压栈的参数还是会被正确处理



但如今实现:

```cpp
result = main (argc, argv, __environ MAIN_AUXVEC_PARAM); 
exit(result);
```

 如今应该都会补上return 0 或者直接报错了.

### NULL and nullptr

```cpp
#if defined(__need_NULL)
#undef NULL
#ifdef __cplusplus
#  if !defined(__MINGW32__) && !defined(_MSC_VER)
#    define NULL __null
#  else
#    define NULL 0
#  endif
#else
#  define NULL ((void*)0)
#endif
#ifdef __cplusplus
#if defined(_MSC_EXTENSIONS) && defined(_NATIVE_NULLPTR_SUPPORTED)
namespace std { typedef decltype(nullptr) nullptr_t; }
using ::std::nullptr_t;
#endif
#endif
#undef __need_NULL
#endif /* defined(__need_NULL) */
```

Test code:

clang :

注意下面的 NULL 其实被上方define成了 __null，在MINGW和MSC中其实被定义成了0，在后两者中是不会造成歧义的，但是前面不行。

```cpp
#include<iostream>
#include<set>
#include <cstring>
using namespace std;
void func(int * a){
    cout << "test 1 :" << endl;
}
void func(int a){
    cout << "test 2 : " << endl;
}
int main(){
    func(nullptr); // "test 1 :"
    func(0);    // "test 2 : "
    //func(NULL); error: ambiguous
}
```

剩下部分基本可以看：`https://blog.csdn.net/qq_18108083/article/details/84346655?utm_source=app` 了。

以下部分源自博客：

**一、C程序中的NULL**

在C语言中，NULL通常被定义为：**#define NULL ((void \*)0)**

所以说NULL实际上是一个空指针，如果在C语言中写入以下代码，编译是没有问题的，因为在C语言中把空指针赋给int和char指针的时候，发生了隐式类型转换，把void指针转换成了相应类型的指针。

```c
int  *pi = NULL;
char *pc = NULL;
```

**二、C++程序中的NUL**

但是问题来了，以上代码如果使用C++编译器来编译则是会出错的，因为C++是强类型语言，void*是不能隐式转换成其他类型的指针的，所以实际上编译器提供的头文件做了相应的处理：

```c
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
```

可见，在C++中，NULL实际上是0.因为C++中不能把void*类型的指针隐式转换成其他类型的指针，所以为了结果空指针的表示问题，C++引入了0来表示空指针，这样就有了上述代码中的NULL宏定义。

**其他：在没有C++ 11的nullptr的时候，我们怎么解决避免这个问题呢？**

```cpp
const class nullptr_t
{
public:
    template<class T>
    inline operator T*() const
        { return 0; }
 
    template<class C, class T>
    inline operator T C::*() const
        { return 0; }
 
private:
void operator&() const;
} nullptr = {};
```

//系统把NULL定位为int，把nullptr定位为void*



### 缓冲区溢出

`https://docs.microsoft.com/zh-cn/windows/win32/SecBP/avoiding-buffer-overruns`

Buffer overruns can occur in a variety of ways. The following list provides a brief introduction to a few types of buffer overrun situations and offers some ideas and resources to help you avoid creating new risks and mitigate existing ones:

- Static buffer overruns

  A static buffer overrun occurs when a buffer, which has been declared on the stack, is written to with more data than it was allocated to hold. The less apparent versions of this error occur when unverified user input data is copied directly to a static variable, causing potential stack corruption.

- Heap overruns

  Heap overruns, like static buffer overruns, can lead to memory and stack corruption. Because heap overruns occur in heap memory rather than on the stack, some people consider them to be less able to cause serious problems; nevertheless, heap overruns require real programming care and are just as able to allow system risks as static buffer overruns.

- Array indexing errors

  Array indexing errors also are a source of memory overruns. Careful bounds checking and index management will help prevent this type of memory overrun.

Preventing buffer overruns is primarily about writing good code. Always validate all your inputs and fail gracefully when necessary. For more information about writing secure code, see the following resources:

- Maguire, Steve [1993], *Writing Solid Code*, ISBN 1-55615-551-4, Microsoft Press, Redmond, Washington.
- Howard, Michael and LeBlanc, David [2003], *Writing Secure Code*, 2d ed., ISBN 0-7356-1722-8, Microsoft Press, Redmond, Washington.



