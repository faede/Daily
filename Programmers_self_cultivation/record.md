## 3.4 ELF

### 段

```shell
objdump -h SimpleSection.o
```



代码中 global_uninint_var 和 static_var2 存放在 .bss 段，但是该段只有4四字节，

其实我们可以通过符号表看到只有static_var2被放在了.bss段，但是global_uninint_var却没有被存放在任何段，只是一个未定义的“COMMON”符号，这和编译器实现有关，有的编译器会将全局的为初始化变量存放在目标文件.bss段，有的则不存放，只是预留一个未定义的全局变量符号，等到最终连接成可执行文件的时候再在.bss段分配空间。

特例：

```
static int x1 = 0;
static int x2 = 1;
```

x1会在.bss  x2 .data ，因为 值 = 0 未初始化时也是这样的，而.bss 不占磁盘空间 所以编译器会为了节省磁盘空间，优化掉了 = 0。



```shell
size  SimpleSection.o
```



代码段：

```shell
objdump -s -d SimpleSection.o
```



自定义段

gcc 拓展

```
__attribute__( (section("FOO"))) int global = 43;
__attribute__( (section("BAR"))) void foo()
{

}
```



### 魔数

```shell
readelf -h SimpleSection.o
```



 Elf 魔数

32:

7f 45 4c 46 01 01 01 00 00 00 00 00 00 00 00 00 

64:

7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00



7f 45 4c 46 为elf标识符

7f ASCII 的 DEL 控制福

 45 4c 46 为： E L F ASCII码



a.out魔数

0x01 0x07

unix pdp 执行时会从文件开始执行 而人们一般会在开始放置一个jump指令：

0x01 0x07 就是当时unix pdp-11 机器跳转7个机器字的指令，为了和之前的兼容，就一直保留。



### 段表

* Asm

.text   size: 0x5f       offset:0x40

.data

.bss

.rodata

.comment

.note.GNU-stack

.note.gnu.property

.ehframe     size:0x58       offset: 0xf8

asm : .eh_frame       0xf8 + 0x58 =0x 150

Elf 0x40  = 64开始

* elf段描述表:

start at offset  0x4a0  = 1024 + 160 = 1184

观察段表中内容:

 .text size : 0x5f  offset: 0x40

.rela.text size:0x78 offset:0x380   RELA

.data

.bss

.rodata

.comment

.note.GNU-stack

.note.gnu.property

.ehframe

.rela.eh_frame   RELA

.symtab  size: 0x1b0 offset:0x150

.strtab  size: 0x7c offset:0x300

.shstrtab size: 0x74 offset:0x428 这里其实保存了段名，在elf.h 中sh_name定义了字符串在.shstrtab中的偏移量

* readelf :

start of  section of headers = 1184 bytes = 0x4a0

对照段表中的内容 我们可以看到在.shstrtab 之后 ：0x74 + 0x428 = 0x49b

对齐后就是 0x4a0 也就是段表的开始了

.rela.text  0x78  + 0x380 = 0x3f8 这个其实和书上有所不同，现在的elf或许最后一部分时段表了



### 重定位表

.rela.text的类型为SHT_RELA ,它是一个重定位表

链接器在处理目标文件时需要对目标文件中的某些部位进行重定位，即代码段和数据段中那些对绝对地址的引用的位置，这些信息都记录在重定位表里。

### 字符串表

elf文件会把字符串存在一起，然后通过字符串的偏移量来饮用字符串

也以段的形式保存

.strtab 字符串表 ：来保存普通字符串，比如符号的名字

.shstrtab 段字符串表：保存段表中用到的字符串，最常见的就是段名"sh_name"

e_shstrndx存放了.shstrtab 在段表中的下标，即表示 段表字符串表 在段表中的小婊



我们可以得出结论，只要分析ELF文件头，就可以得到段表和段表字符串表的位置，从而分析整个ELF文件。





## 3.5 符号

### Elf64_Sym

在链接中，我们将函数或变量统称为符号，函数名或变量名就是符号名

局部符号，这类符号只在编译单元可见，对于链接过程没有作用，链接器也往往忽略它们。

```shell
nm SimpleSection.o
```

ELF文件中符号表往往是文件中的一个段，段名一般叫做".symtab" ，它是一个Elf64_Sym的数组，结构体定义如下：

```cpp
typedef struct{
  Elf64_Word st_name; //符号名，包含了符号名在字符串表中的下标
  unsigned char st_info; // 符号类型和绑定信息 （绑定信息 ：0 ：局部 1:全局 2:弱饮用     类型：0 未知 1 数据对象 2 函数或其他可执行代码 3 段 4 文件名
  unsigned char st_other; // 32位时是0，没有用处
  Elf64_Section st_shndx; // 符号所在的段 0xfff1 表示符号包含了一个绝对的值 0xfff2 “COMMON块”  0 未定义
  Elf64_Addr st_value; // 符号对应的值 如果不是SH_COMMON那就是符号在段中的偏移量
  Elf64_Xword st_size; // 符号大小
}Elf64_Sym;
```

```shell
readelf -s SimpleSection.o
```

Ndx 为所属的段

打印全部信息

```shell
readelf -a SimpleSection.o
```



Ndx的值可以和Section Table 对应来看 main 和 func1 的值都为1，对应Section Table 就是 .text段

Static_var.1920 static_var.1921是两个静态变量，绑定至都是LOCAL，只在编译单元可见，已经被重命名了



### 特殊符号

ld会产生许多特殊符号，这些符号在你的程序中没有定义，但是你可以直接使用

如：

``` 
__executable_start 程序起始地址，不是入口地址而是程序的最开始地址
__etext或_etext或etext 为代码段结束
_edata或edata 为数据段结束
_end 或 end 为程序结束地址
```

以上地址为程序被装载时的虚拟地址。



### 符号修饰与函数签名

开始时为了减少冲突c会在编译之后加上`_` Fortan 前后都加`_`

c++后来有了名字空间

随着不断更新，c语言在Linux gcc也默认不在加`_` 但是 window下的大多保持着加的传统



c++

为了支持类、继承、多态等发明了 符号修饰、符号改编机制

函数签名：包含函数的信息，函数名、参数、所在的类、名称空间等

编译器采用名称修饰的方法，是的每个函数签名对应一个修饰后名称。



extern "C"

c++为了支持C的符号提供的语法，加extern后，cpp的名称修饰机制将不再起作用。

例如对于c的函数

```c
void * memset(void *, int ,size_t );
```

如果是c程序编译器肯定能正确处理，但是C++语言瑰酱它进行符号修饰成`_Z6memsetPvii`

那么连接器就无法正确的链接，于是就会利用宏`__cplusplus`，采用宏定义的方式解决冲突

```cpp
#ifdef __cplusplus
extern "C" {
#endif
void * memset(void *, int ,size_t );
#ifdef __cplusplus
}
#endif 
```

### 强符号和弱符号

如果A 、 B文件中都定义了一个全局整型变量global 并将他们都初始化，那么链接器就会在将两者链接时报错：

```
b.o (.data+0x0):multiple definition of 'global'
a.o (.data+0x0):first defined here
```

这种符号的定义被称为强符号。

对于C/C++编译器默认函数和初始化了的全局变量为强符号，为初始化的全局变量为弱符号，我们可以通过`__attribute__((weak))`来定义任何一个强符号为弱符号。强符号和弱符号是针对定义来说的，并不是针对符号的引用。

```cpp
extern int ext; // 非强非弱，是外部符号的引用

int weak; //弱
int strong = 1; //强
__attribute__((weak)) weak2 = 2; //弱

int main(){
  return 0;
}
/*
readelf -a
但是实测中int weak; 和 int test = 0; 都是强符号
这是因为-fno-common选项,GCC10.0 之后默认开启,未初始化的全局变量不以COMMON块的形式处理
更为奇怪的是加上-fcommon的选项之后gcc还是不会正常处理,但是clang会将weak判定为Common,或许是-fcommon已经失效,又或者编译器有其它的考量
*/
```





针对强弱符号的概念，链接器就会按如下规则处理和选择被多次定义的全局符号

规定：

```
规则1: 不允许强符号被多次定义。报错。
规则2: 如果一个符号在某个目标文件中是强符号，在其它文件中都是弱符号，那么选择强符号。
规则3: 若果一个符号在所有目标文件中都是弱符号，那么炫额占用空间最大的一个。
```



### 强引用和弱饮用

如果没找到符号的定义，那么链接器就会报符号未定义错误，这种被称为强引用。

弱饮用，如果符号有定义，则链接器处理该符号的引用决议，未定义不报错。

一般对于未定义的弱饮用链接器默认其为0，或是一个特殊的值，以便识别。

gcc下`__attribute__((weakref))`

```cpp
__attribute__((weakref)) void foo();
int main(){
  foo();
}
```

编译成可执行文件不报错，但是运行会报错。

改进：

```
__attribute__((weakref)) void foo();
int main(){
  if(foo()) foo();
}
```

弱符号和弱饮用对于库来说十分有用，库中定义弱符号可以被用户定义的强符号所覆盖，从而使得程序可以使用自定义版本的苦函数；或者程序可以为某些拓展功能模块的饮用定义为弱饮用，当我们将拓展模块和程序连接在一起时，功能可以正常使用，去掉了也能正常链接。

在Linux程序中，如果一个程序被设计陈可以支持多线程或者单线程的模式就可以通过弱引用的方法来判断当前程序是否链接到了单线程的`Glibc`库，或者多线程的`Glibc`库（是否存在`-lpthread`选项）。

我们可以定义一个pthrea_create函数的弱饮用，然后根据程序在运行时动态判断是否链接到pthread库从而决定执行单线程还是多线程版本：

```cpp
#include <stdio.h>
#include <phread.h>
int pthread_create(
pthread_t *,
  const pthread_attr_t *,
  void * (*) (void *),
  void *) __attribute__ ((weak));
int main()
{
  if(pthread_create){
    printf("This is multi-thread version!\n");
    // run the multi-thread version
    // main_multi_thread()
  }else{
    printf("This is single-thread version!\n");
    // run the single-thread version
    // main_single_thread()
  }
}
```

```shell
gcc pthread.c -o pt
./pt
This is single-thread version!

gcc pthread.c -lpthread -o pt
./pt
This is multi-thread version!
```

### 调试信息

-g选项



strip可以去掉elf文件中的调试信息。

```shell
strip foo
```



## 静态链接

### 空间地址分配

#### 按序叠加



#### 相似段合并

链接器为目标文件分配地址和空间:

地址和空间:

 1.在输出的可执行文件中的空间

2.在装载后的虚拟地址中的虚拟地址空间

谈到的空间分配只涉及虚拟地址空间.



#### 两步链接

第一步 空间地址分配

第二步 符号解析与定位



Linux下 ELF可执行文件默认地址0x08048000开始分配

### 重定位表

#### 符号解析

#### 指令修正

#### COMMON块

在目标文件中,编译器为什么不直接把未初始化的全局变量变成未初始化的局部静态变量一样处理,为它在BSS段分配空间,而是标记为一个COMMON类型变量?

编译器将一个编译单元编译成目标文件的时候,如果编译单元包含弱符号,那么该弱符号最终所占的大小在此时是未知的,因为有可能其他编译单元中该符号所占用的空间比所需要的空间要大. 但是链接器在链接过程中可以确定弱符号的大小,因为当链接器读取所有输入目标文件之后,任何一个弱符号的最终大小都可以确定了,所以说它可以在最终输出文件的BSS段为其分配空间. 所以总体来看,未初始化的全局变量最终还是被放在BSS段.

#### 重复代码消除

C++会为每个模板的实例化代码放在一个段里,每个段只包含一个模板实例.

GCC把这种类似的须要在最终链接时合并的段叫“Link Once”,它的做法是将这种类型的段命名为“.gnu.linkonce.name”



但是还是存在一些问题,比如相同名称的段可能拥有不同的内容,这可能是由于不同编译单元是用来不同编译版本或者编译优化选项,导致同一个函数编译出来的实际代码不同,那么这种情况下链接器可能会做出一个选择,那就是随便选择一个副本作为链接的输入并提供一个警告信息.

#### 函数级别链接

VISUAL C++编译器提供了一个编译选项叫做函数级别链接,这个选项的作用是让所有函数都想前面模板函数一样,保存到单独的一个段中.

#### 全局构造与析构

Linux下程序的一般入口是_start,是Linux系统库(Glibc)的一部分.

程序一些特定的操作必须在main函数之前被执行,还有一些操作必须在main函数执行后执行,其中很具有代表性的就是c++的全局对象的析构函数和构造函数,因此ELF文件中还定义了两种特殊的段.

.init 该段里保存的是可执行指令,它构成了进程的初始化代码. 因此当一个程序开始运行时,在main函数被调用前,Glibc的初始化部分安排执行这个段中的代码.

.fini 该段保存着进程终止代码指令. 因此当一个程序的main函数正常退出时,Glibc会安排执行这个段中的代码.

#### ABI

我们把符号修饰标准、变量内存布局、函数调用方式等这些和可执行二进制兼容性相关的内容称为ABI(Application Binary Interface)

### 静态库链接

Linux中最常用的C语言静态链接库libc位于/usr/lib/libc.a

.o文件通常经过“ar”压缩程序将这些目标文件压缩在一,并对其进行行编号和索引,以便于查找和检索,就形成了libc.a这静态链接库

查看文件中包含哪些目标文件

```shel
ar -t libc.a
```

Visual C++ => 类似ar的工具叫做lib.exe

如何在这么多文件中找到printf函数所在的目标文件呢,答案是使用 obdjump或者readlf加上grep

用“obdjump” 查看libc.a的符号可以看到

```shell
obdjump -t libc.a
```

printf被定义在了printf.o这个文件

这样就找到了printf的定义

```shell
gcc -c -fno-builtin hello.c
```

用-fno-builtin是因为 默认会将printf换成puts函数以提高运行效率,我们用-fno-builtin关闭内敛函数优化.

但是加上printf.o依然不行,我们加上缺少的文件后还是不行,因为还需要一些辅助的目标文件和库

我们可以将整个编译链接过程的中间打印出来

```shell
gcc -static --verbose -fno-builtin hello.c
```

#### 链接过程控制

显示默认链接脚本:

```shell
ld -verbose
```



自己写一个脚本来链接:

```cpp
ld -T link.script
```

#### 最小的程序

```c
char* str = "Hello world!\n";

void print(){
	asm(
	"movl $13, %%edx \n\t"
	"movl %0, %%ecx \n\t"
	"movl $0, %%ebx \n\t"
	"movl $4, %%eax \n\t"
	::"r"(str):"edx","ecx","ebx");
}

void exit()
{
	asm( "movl $42, %ebx \n\t" 
		"movl $1, %eax \n\t"
		"int $0x80 \n\t ");
}

void nomain()
{
	print();
	exit();
}
```



Int 0x80系统调用,eax为调用号,ebx、ecx、edx等通用寄存器来传递参数

```c
int write(int filedsec,char *buffer,int size);
```

* WRITE调用的调用号为4,所以eax=4

* filedesc表示被写入文件的句柄,使用ebx寄存器传递,这里我们要向默认终端(stdout)输出,它的文件句柄是0,即ebx=0

* buffer表示要写入的缓冲区地址,使用ecx寄存器传递,这里我们要输出字符串str,所以ecx=str
* size 表示要写入的字节数,使用edx寄存器传递,字符串“Hello world!\n”,长度为13字节,所以edx=13

同理,EXIT系统调用中,ebx表示退出码,EXIT系统调用号为1,即eax=1