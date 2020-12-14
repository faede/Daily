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

#### 使用ld链接程序

  ```cpp
ENTRY(nomain)
  
SECTIONS
{
  . = 0x08048000 + SIZEOF_HEADERS;
  tinytext : { *(.text)   *(.data) *(.rodata) }
  /DISCARD/ : { *(.comment) }
}
  ```



#### ld链接脚本语法简介

* 语句之间使用分号“;”作为分割符
* 表达式与运算符
* 注释和字符引用

ENTRY(symbol) : 指定符号symbol的值为入口地址(Entry Point).

ld设置入口地址优先级:

1. ld命令行的-e选项
2. ENTRY(symbol) 
3. 如果定义了符号_start 符号,使用_start符号值
4. 如果存在.text段,使用.text段的第一字节的地址
5. 使用值0

STARTUP(filename) : 将文件filename作为链接过程中的第一个输入文件.

SEARCH_DIR(path) : 将path加入到ld链接器的库查找目录.

INPUT(file, file,....)

INPUT(file  file ....) 将指定文件作为链接过程中的输入文件

INCLUDE filename 将指定文件包含进链接脚本

PROVIDE(symbol) 在链接脚本中定义某个符号.

SETIONS

{

​	...

​	secname :   { contents }

​	...

}

secname后面必须有一个空格 ,防止歧义

contents: filename(sections)

### BFD库

希望通过一种统一的接口来处理不同的目标文件格式.

## Windows PE/COFF

### Windows的二进制文件格式PE/COFF

PE(Protable Executable)

COFF(Common Object File Format)

### 可执行文件的装载与进程

### 进程虚拟地址空间



### 装载的方式

因为无法将所有需要的东西都装入内存:

#### 覆盖装入

把发掘内存潜力的任务交给了程序员,程序员在编写程序时必须手工将程序分成若干块,然后编写一个小的辅助代码来管理这些模块合适应该驻留内存而何时应该被替换掉,这个的辅助代码就是所谓的覆盖管理器.

程序员需要手工将模块按照它们之间的调用依赖关系组织成树状结构.

需要保证:

* 树状结构中从任何一个模块到树的根模块都叫调用路径,当模块被调用时,整个调用路径上的模块必须都在内存中.
* 禁止跨树间调用.

#### 页映射

将代码按页存起来,需要时掉入,不足空间时掉出

### 从操作系统角度看可执行文件的装载

#### 进程的建立

首先创建虚拟地址空间

读取可执行文件头,并且建立虚拟空间与可执行文件的映射关系

将CPU指令寄存器设置成可执行文件入口,启动运行

#### 页错误



### 进程虚拟空间分布

#### ELF文件链接视图和执行视图

由于需要按页存储,又想要节省空间

ELF,文件中断的权限只有为数不多的几种组合,基本是:

* 以代码段为代表的权限为可读可执行的段
* 以数据段和BSS段为代表的权限为可读可写的段
* 以只读数据段为代表的权限为只读的段

对于相同权限的段,把他们合并到一起当作一个段进行映射.

ELF可执行文件中引入了一个概念叫做”Segment“,一个”Segment“包含一个或多个属性类似的”Section“.

”Segment“和”Section“是从不同角度来划分同一个ELF文件,这个在ELF中被称为不同视图,从”Section“的角度来看ELF文件就是链接视图,从”Segment‘角度来看就是执行视图.

对于“LOAD”类型的“Segment”来说,当分配的空间大于实际空间时,那些额外的部分就是BSS,因为BSS段和数据段唯一的区别就是:数据段从文件中初始化内容,而BSS段的内容全部初始化为0.



#### 堆和栈

文件所做设备号和次设备号饥文件节点号都是0,则表示它们没有映射到文件中,这种VMA叫做匿名虚拟存储区域,堆和栈就是.

还有一个匿名虚拟存储区域,vdso内核模块,用来和内核进行一些通信.

VMA:

* 代码VMA,权限只读、可执行;有映像文件
* 数据VMA,权限可读写、可执行;有映像文件
* 堆VMA, 权限可读写、可执行; 无映像文件,匿名,可向上拓展
* 栈VMA, 权限可读写、不可执行; 无映像文件,匿名,可向下拓展

“HACK” : VMA与“Segment”并非完全对应,Linux规定一个VMA可以映射到某个文件的一个区域或者是没有映射到任何文件;而“Segment”要求是,前面的部分映射到文件中,而后面一部分不映射到任何文件,直接为0.

#### 堆的最大申请数量



#### 段地址对齐



### Linux内核装载ELF过程简介

在用户层面,bash进程会调用fork()系统调用创建一个新的进程,然后新的今晨调用execve() ->sys_execve() -> do_execve() -> seach_binary_handle ,

如果是elf文件 -> load_elf_binary()  / a.out可执行文件: ->load_aout_binary

### Windows PE的装载

RVA:相对虚地址.



## 动态链接

### 为什么要动态链接

* 内存和磁盘空间

* 程序开发和发布

* 动态链接

把链接过程推迟到执行时再执行,这就是动态链接的基本思想.

降低耦合度.

* 程序可拓展性和兼容性



Linux中,ELF动态链接文件被称为动态共享对象(DSO, Dynamic Shared Objects),简称共享对象,一般以
“.so”结尾,Windows中,称为动态链接库(Dynamic Linking Library), “ddl”.

### 地址无关代码

#### 固定装载地址的困扰

#### 装载时重定位



#### 地址无关代码

共享对象模块中的地址引用四种情况:

1. 模块内部的函数调用、跳转

2. 模块内部的数据访问,比如模块中定义的全局变量、静态变量.

3. 模块外部的函数调用、跳转

4. 模块外部的数据访问,比如其他模块中定义的全局变量.

   

```cpp
static int a;
extern int b;
extern void ext();

void bar()
{
  a = 1;// 2
  b = 2;// 4
}

void foo()
{
  bar(); // 1
  ext(); // 3
}
```

编译时其实并不能确定b和ext是模块外部还是内部,所以只能把它们都当做模块外部的函数和变量来处理.

##### 类型一 模块内部的调用和跳转

 ```asm
8048344 <bar>:
8048344: 55 		push %ebp
8048345: 89 e5 	mov %esp, %ebp
8048347: 5d			pop %ebp
8048348: c3			ret

8048349:<foo>:
...
8048357: e8 e8 ff ff ff call 8048344<bar>
804835c: b8 00 00 00 00	mov $0x0, %eax
 ```

Cal 是相对偏移调用,指令的后四个字节是目的地址相对于当前指令的下一条指令的偏移量,即0xFFFFFFE8(Little-endian), 0xFFFFFFE8是-24的补码,即bar的地址为804835c + (-24) = 8048344

只要bar和foo的相对位置不变就有效

但还有个问题叫做共享对象全局符号介入问题.

##### 类型二 模块内部数据访问

只能采用相对寻址,但是现代体系结构中,数据的相对寻址往往没有相对于当前指令地址(PC)的寻址方式,所以ELF用了一种巧妙的方法获取PC值(其中一种如下):

```asm
44f: e8 40 00 00 00 call 494 	<__i686.get_pc_thunk.cx>
454: 81 c1 8c 11 00 00 				add $0x118c,%ecx
45a: c7 81 28 00 00 00 01 		movl $0x1,0x28(%ecx) //a = 1
461: 00 00 00
```

"__i686.get_pc_thunk.cx"把返回地址的值放到ecx寄存器,即把call的下一条指令的地址放到ecx寄存器.

##### 类型三 模块间数据访问

模块间的数据访问目标地址要等到装载时才决定.

要使代码地址无关,基本思想就是把跟地址相关的部分放到数据段里面,这些模块的全局变量地址显然是和模块装载地址相关的.

ELF的做法是在数据段里面建立一个指向这些变量的指针数组,也被称为全局偏移表(Global Offset Table,GOT), 当代码需要引用该全局变量时,可以通过GOT中相对应的项间接引用.

##### 类型四 模块间调用、跳转

同样可以用GOT表解决.

##### PIE

地址无关可执行文件(PIE, Position-Independent Executable)

#### 共享模块的全局变量问题

当一个模块引用了一个定义在共享对象的全局变量时, 比如一个共享对象定义了一个全局变量global,

而module.c这么引用

```cpp
extern int global;
int foo;
{
  global = 1;
}
```

编译时无法判断global是否是跨模块间调用

如果module.c是可执行程序的一部分,那么程序主模块不是地址无关代码,就会在.bss创建一个副本



解决办法: 所有的使用这个笔亲来那个的指令都指向对于可执行文件中的那个副本. ELF共享库在编译时,默认都把定义在模块内部的全局变量当做定义在其他模块的全局变量,通过GOT表访问.

#### 数据地址无关性

```cpp
static int a;
static int *p = &a;
```

重定位

### 延迟绑定(PLT)

在一个程序运行过程中,可能很多函数在程序执行完时都不会被用到,如果一开始就把所有函数都链接好实际上是一种浪费,所以ELF采用了一种叫做延迟绑定的做法,基本思想就是当函数第一次被用到时才进行绑定.

ELF使用PLT(Procedure Linkage Table)实现.



当我们调用某个外部模块的函数时,如果按照通常的做法应该是通过GOT中的相应的项进行间接跳转. PLT为了实现延迟绑定,在这个过程中又增加了一层间接跳转.调用函数并不直接通过GOT跳转,而是通过一个叫做PLT项的结构来进行跳转. 每个外部函数在PLT中都有一个相应的项,比如bar()

```asm
bar@plt:
jmp *(bar@GOT)
push n
push moduleID
jump _dl_runtime_resolve
```

开始时为了延迟绑定,没有将bar()的地址填到GOT中,而是填了“push n”的地址

n 是bar这个符号在重定位表“.rel.plt”中的下标._dl_runtime_resolve完成解析和重定位工作.



一旦bar()这个函数被解析完毕,当我们再次调用bar@plt时,第一条jmp指令就能够跳转到真正的bar()函数中,bar()函数返回时会根据堆栈中保存的EIP直接返回到调用者,而不会在执行bar@plt中第二条执行开始的代码.



实际上:

ELF将GOT拆分成了两个表,叫做“.got”和“.got.plt”,  “.got”用来保存全局变量引用的地址,“.got.plt”用来保存函数引用的地址.也就是说,对于所有外部函数的引用全部被分离出来放到了“.got.plt”里,另外“.got.plt”前三项是有特殊意义的:

* 第一项保存的是“.dynamic”段的地址,这个段描述了本模块动态链接相关的信息

* 第二项保存的是本模块ID

* 第三项保存的是_dl_runtime_resolve()的地址

  

第二、三项由链接器在装载共享模块的时候负责将它们初始化.

ELF为了减少代码重复, 把`push moduleID jump _dl_runtime_resolve` 两条指令放到了PLT中的第一项,并且规定每一个项的长度是16个字节,刚好用来存放3条指令.

实际PLT的基本结构代码:

```asm
PLT0:
push *(GOT + 4)
push *(GOT + 4)
...
bar@plt:
jmp *(bar@GOT)
push n
jump PLT0
```

### 动态链接相关结构

动态链接装载完,许多外部符号还处于无效地址的状态,还需要先启动一个动态链接器

#### “.interp”段

动态链接器的路径

#### “.dynamic”段

动态链接器所需要的基本信息

#### 动态符号表

静态链接中符号表: “.symtab”

为了表示动态链接这些模块之间的符号导入、导出关系,ELF专门有一个叫做动态符号表

(Dynamic Symbol Table)的段用来保存这些信息,这个段的段名通常叫做“.dynsym”(DynamicSymbol)

“.dynsym”只保存了与动态链接相关的符号

静态链接的辅助表:“strtab”

动态链接: “dynstr”

用于动态链接下,我们需要在程序运行时查找符号,为了加快符号的查找过程,往往还有辅助的符号哈希表“.hash”

#### 动态链接重定位表

基地址重置

#### 动态链接时进程堆栈初始化信息



### 动态链接的步骤和实现

基本分3步: 先是启动动态链接器本身,然后装载所有需要的共享对象,最后是重定位和初始化

#### 动态链接器自举





## 运行库

### 入口函数和程序初始化

#### 程序从main开始吗

在main函数前准备环境

* 操作系统在创建进程后,把控制权交到了程序的入口,这个入口往往是运行库中的某个入口函数
* 入口函数对运行库和程序运行环境进行初始化,包括堆、I/O、线程、全局变量构造等等
* 入口函数在完成初始化之后,调用main函数,正式开始执行程序主体部分.
* main函数执行完成初始化之后,调用main函数,正式开始执行程序主体部分
* main函数执行完毕后.返回到入口函数,入口函数进行清理工作,包括全局变量析构、堆销毁、关闭I/O等,然后进行系统调用结束进程.

#### 入口函数如何实现

##### GLIBC入口函数

静态glibc:

I386 精简后:

```assembly
libc\sysdeps\i386\elf\Start.S
_start:
	xorl %ebp, %ebp
	popl %esi
	movl %esp, %ecx
	
	pushl %esp
	pushl %edx
	pushl $__libc_csu_fini
	pushl $__libc_csu_init
	pushl %ecx
	pushl %esi
	pushl main
	call __libc_start_main
	
	hlt
```

popl %esi将argc存入了%esi , 而movl %esp, %ecx 将栈顶地址(此时就是argv 和 环境变量(env)数组的起始地址)传给%ecx. 

综上_start可以被改写成:

```cpp
void _start()
{
  %ebp = 0;
  int argc = pop from stack
  char ** argv = top from stack
  __libc_start_main(main,argc,argv,__libc_csu_init,__libc_csu_fini,edx,top of stack);
}
```

其中argv除了指向参数表外,还隐含着接着环境变量表,这个环境变量表要在__libc_start_main里从argv中提取出来.



实际执行代码的函数是__libc_start_main由于代码很长,我们一段段看:

_start - >__libc_start_main:

```cpp
int __libc_start_main(
	int (*main)(int argc, char **, char **),
  int argc,
  char * __unbounded * __unbounded ubp_av,
  __typeof (main) init,
  void (*fini) (void),
  void (*rtld_fini) (void),
  void * __unbounded stack_end )
{
#if __BOUNDED_POINTERS
  char ** argv;
#else
# define argv ubo_av
#endif
  int result;

```

ubp_av 是argc和argv并且包含环境变量表

* init : main调用前的初始化工作

* fini: main结束后的收尾工作

* rtld_fini: 和动态加载有关的收尾工作,rtld是runtime loader的缩写.

  最后的stack_end标明了栈底的地址,即最高的栈地址.

gcc 支持 bounded类型的指针,普通指针 unbounded , 这种指针占用3个指针空间,在第一个可空间里存储原指针的值, 第二个空间里存储下限值,第三个空间里存储上限值. `__ptrvalue , __ptrlow,__ptrhigh`分别返回这3个值,有这3个值,内存越界便很容易查出来了,但是在2003年被关闭了.



接下里:

```cpp
char ** ubp_ev = &ubp_av[argc + 1];
INIT_ARGV_and_ENVIRON;
__libc_stack_end = stack_end;
```

INIT_ARGV_and_ENVIRON展开后:

```cpp
char ** ubp_ev = &ubp_av[argc + 1];
__environ = ubp_ev;
__libc_stack_end = stack_end;
```

分两步赋值给__environ的原因是为了兼容bounded



接下来有另一个宏:

```asm
DL_SYSDEP_OSCHECK (__libc_fatal);
```

这是用来检查操作系统的版本.



接下来的代码比较复杂,过滤掉大量信息后,一些关键函数调用:

```cpp
__pthread_initialize_minimal();
__cxa_atexit(rtld_fini, NULL, NULL);
__libc_init_first (argc, argv, __environ);
__cxa_atexit(fini, NULL, __environ);
(*init)(argc,argv,__environ);
```

__cxa_atexit是glic的内部函数,等同于atexit,用于将参数指定的函数在main结束之后调用. 所以参数传入的fini

和rtld_fini均是main结束之后调用. 在__libc_start_main的末尾,关键的是这两行代码:

```cpp
result = main(argc, argv, __environ);
exit(result);
}
```

咋最后,main函数终于被调用,并推出.我们来看看exit的实现:

_start -> __libc_start_main - > exit:

 ```cpp
void exit (int status)
{
  while(__exit_funcs != NULL)
  {
    ...
      __exit_funcs = __exit_funcs->next;
  }
  ...
    _exit(status);
}
 ```

其中__exit_funcs是存储由 `__cxa_atexit`和atexit注册的函数链表,这里的这个whiel循环则便利该链表并逐个调用这些注册的函数,由于其中琐碎的代码过多,这里就不具体列出了.

最后的_exit由汇编函数实现,且与平台有关,下面列出i386的实现

_start -> __libc_start_main -> exit -> _exit:

```asm
_exit:
	movl 4(%esp), %eax
	movl $__NR_exit, %eax
	int $0x80
	
	hlt
```

可见`_exit`的作用仅仅是调用了exit这个系统调用. 也就是说,`_exit` 之后, 程序就会直接结束.程序正常退出有两种情况,一种是main函数的正常返回,一种是程序中用exit退出. 在libc_start_main中我们可以看到,即使main返回了,exit也会被调用, exit是进程正常退出的必经之路,因此把调用用atexit注册的函数的任务交给exit来完成可以说万无一失.

(在程序中执行exit(0)就不会执行exit(reslut)了, 但是程序最后都是执行exit函数)



我们看到`_exit` 和`_start`的末尾都有一个hlt指令,这是用做什么? 在Linux里,进程必须使用eixt系统调用结束. 一旦exit被调用,程序的运行就会终止,因此实际上`_exit` 末尾的hlt不会执行,从而 `__libc_start_main`永远不会返回, 以至 `_start` 末尾的hlt指令也不会执行.`_exit` 里的hlt指令是为了检测exit系统调用是否成功.如果失败,程序就不会终止,hlt指令就可以发挥作用强行把程序给停下来, 而`_start` 里的hlt的用处也是如此, 此处是为里预防某种没有调用exit,就会到_start 的情况.



