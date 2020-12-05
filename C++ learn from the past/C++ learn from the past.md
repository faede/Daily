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

### 探索C++析构函数(部分存疑)

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

并且虽然我们可以通过添加`{}`来改变对象的作用域,但是离开`{}`的作用域的时候不会调用析构函数,当然这也很好理解,不然假设我们在析构函数中要处理一些东西,那结果应该非常反人类.



对于析构函数来说真正的对象销毁工作应该在对象离开对象的作用域之后,但是最终调用的对象析构函数应该是发生在main函数返回(return )前的,所以我推测编译器在最后为代码添加了析构函数的调用,

当然也有可能最终函数的执行会交由外部函数处理,但我觉得并不合理,内外部函数存放的位置不同,如果没有其它未知操作的话,外部执行最后的析构函数会导致相同的代码在不同的段存放两次,这感觉并不是很合理,除非两段会共用,不过具体情况也就不得而知了.

综上所述,就目前来讲,对象的析构函数还是不要显示调用来的好(当然除了数组需要delete的情况).



