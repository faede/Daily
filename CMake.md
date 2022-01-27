

.PHONY clean

.PHONY表示伪目标，表示目标不是一个文件

如果不加的话 多次clean会显示up to date，无法使用

'JetBrains Mono','Inconsolata LGC','JetBrains Mono NL',Menlo, Monaco, 'Courier New', monospace





vscode 字体改变

```
https://blog.csdn.net/fightsyj/article/details/110144139
```

# Chapter 1

## 01

```cpp
#include <cstdlib>
#include <iostream>
#include <string>

std::string say_hello() { return std::string("Hello, CMake world!"); }

int main() {
  std::cout << say_hello() << std::endl;
  return EXIT_SUCCESS;
}

```



```cmake
# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-01 LANGUAGES CXX) 
# CXX => c++ , beside c++ is default language in cpp , but recommend explicit declare

add_executable(hello-world hello-world.cpp)
```



```shell
mkdir -p build # -p: create the directory and, if required, all parent directories
cd build 
cmake .. # genreate configure , conf file in .. dir
# or us "cmake -H. -Bbuild" replcace above
cmake -H. -Bbuild
# -H -B is CLI optinal, -H represent in present dir search CMakteLists.txt, -Build tail generate in file a build dir


cmake --build .   # compile

# or any dir
$ mkdir -p /tmp/someplace
$ cd /tmp/someplace
$ cmake /path/to/source
$ cmake --build .
```

- `Makefile`: `make`将运行指令来构建项目。
- `CMakefile`：包含临时文件的目录，CMake用于检测操作系统、编译器等。此外，根据所选的生成器，它还包含特定的文件。
- `cmake_install.cmake`：处理安装规则的CMake脚本，在项目安装时使用。
- `CMakeCache.txt`：如文件名所示，CMake缓存。CMake在重新运行配置时使用这个文件。



## 02切换生成器

```shell
cmake -help
...
Generators

The following generators are available on this platform (* marks default):
* Unix Makefiles               = Generates standard UNIX makefiles.
  Ninja                        = Generates build.ninja files.
  Ninja Multi-Config           = Generates build-<Config>.ninja files.
  Watcom WMake                 = Generates Watcom WMake makefiles.
  Xcode                        = Generate Xcode project files.
  CodeBlocks - Ninja           = Generates CodeBlocks project files.
  CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
  CodeLite - Ninja             = Generates CodeLite project files.
  CodeLite - Unix Makefiles    = Generates CodeLite project files.
  Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files.
  Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files.
  Kate - Ninja                 = Generates Kate project files.
  Kate - Unix Makefiles        = Generates Kate project files.
  Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files.
  Sublime Text 2 - Unix Makefiles
                               = Generates Sublime Text 2 project fi
```



>在Unix/Linux下通常使用Makefile来控制代码的编译，但是Makefile对于比较大的项目有时候会比较慢，看看上面那副漫画，代码在编译都变成了程序员放松的借口了。所以这个Google的程序员在开发Chrome的时候因为忍受不了Makefile的速度，自己重新开发出来一套新的控制编译的工具叫作Ninja，Ninja相对于Makefile这套工具更注重于编译速度。除了Chrome现在还有一些其他的比较大的项目也在开始使用Ninja，比如LLVM。我试用了一下感觉还是不错，比如编译Cmake时间大概是原来的1/4。Ninja试用C++实现，其支持的语法非常简单，作者在这里说明了为了控制复杂度。

```shell
cmake -G Ninja ..  # -G change genreate
```

## 03构建和链接静态库和动态库

Message.hpp<--Message.cpp 

Message.cpp <-- hello-world.cpp

```cmake
# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-03 LANGUAGES CXX)

# generate a library from sources
add_library(message # target name, cmake will add "lib" and suffix
  STATIC # static library  => libmessage.a
    Message.hpp
    Message.cpp
  )

add_executable(hello-world hello-world.cpp)

# link
target_link_libraries(hello-world message)

```

- **STATIC**：用于创建静态库，即编译文件的打包存档，以便在链接其他目标时使用，例如：可执行文件。
- **SHARED**：用于创建动态库，即可以动态链接，并在运行时加载的库。可以在`CMakeLists.txt`中使用`add_library(message SHARED Message.hpp Message.cpp)`从静态库切换到动态共享对象(DSO)。
- **OBJECT**：可将给定`add_library`的列表中的源码编译到目标文件，不将它们归档到静态库中，也不能将它们链接到共享对象中。如果需要一次性创建静态库和动态库，那么使用对象库尤其有用。我们将在本示例中演示。
- **MODULE**：又为DSO组。与`SHARED`库不同，它们不链接到项目中的任何目标，不过可以进行动态加载。该参数可以用于构建运行时插件。

CMake还能够生成特殊类型的库，这不会在构建系统中产生输出，但是对于组织目标之间的依赖关系，和构建需求非常有用：

- **IMPORTED**：此类库目标表示位于项目外部的库。此类库的主要用途是，对现有依赖项进行构建。因此，`IMPORTED`库将被视为不可变的。我们将在本书的其他章节演示使用`IMPORTED`库的示例。参见: https://cmake.org/cmake/help/latest/manual/cmakebuildsystem.7.html#imported-targets
- **INTERFACE**：与`IMPORTED`库类似。不过，该类型库可变，没有位置信息。它主要用于项目之外的目标构建使用。我们将在本章第5节中演示`INTERFACE`库的示例。参见: https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#interface-libraries
- **ALIAS**：顾名思义，这种库为项目中已存在的库目标定义别名。不过，不能为`IMPORTED`库选择别名。参见: https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#alias-libraries

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(recipe-03 LANGUAGES CXX)
add_library(message-objs
    OBJECT
        Message.hpp
        Message.cpp
    )
    
# this is only needed for older compilers
# but doesn't hurt either to have it
set_target_properties(message-objs
    PROPERTIES
        POSITION_INDEPENDENT_CODE 1
    )
    
    
add_library(message-shared
    SHARED
        $<TARGET_OBJECTS:message-objs>
    )
add_library(message-static
    STATIC
        $<TARGET_OBJECTS:message-objs>
    )
add_executable(hello-world hello-world.cpp)
target_link_libraries(hello-world message-static)
```

要注意引用对象库的生成器表达式语法:`$<TARGET_OBJECTS:message-objs>`。生成器表达式是CMake在生成时(即配置之后)构造，用于生成特定于配置的构建输出。

是否可以让CMake生成同名的两个库？换句话说，它们都可以被称为`message`，而不是`message-static`和`message-shared`吗？我们需要修改这两个目标的属性

```cmake
add_library(message-shared
  SHARED
    $<TARGET_OBJECTS:message-objs>
    )
    
# generate and rename
set_target_properties(message-shared
    PROPERTIES
        OUTPUT_NAME "message"
    )
    
add_library(message-static
    STATIC
        $<TARGET_OBJECTS:message-objs>
    )
    
set_target_properties(message-static
    PROPERTIES
        OUTPUT_NAME "message"
    )
```

libmessage.dylib  && libmessage.a

我们可以链接到DSO吗？这取决于操作系统和编译器：

1. GNU/Linux和macOS上，不管选择什么编译器，它都可以工作。
2. Windows上，不能与Visual Studio兼容，但可以与MinGW和MSYS2兼容。

>A ***d**ynamic **s**hared **o**bject* (**DSO**) is an object file that is intended to be used simultaneously (or shared by) multiple [applications](https://www.webopedia.com/definitions/application-software/) while they’re [executing](https://www.webopedia.com/definitions/execute/). A DSO can be used in place of archive [libraries ](https://www.webopedia.com/definitions/library/)and will minimize overall [memory](https://www.webopedia.com/definitions/memory/) usage because code is shared. Two executables that use the same DSO and that run simultaneously have only one copy of the shared components loaded into memory.

## 04 用条件句控制编译

从与上一个示例的的源代码开始，我们希望能够在不同的两种行为之间进行切换：

1. 将`Message.hpp`和`Message.cpp`构建成一个库(静态或动态)，然后将生成库链接到`hello-world`可执行文件中。
2. 将`Message.hpp`，`Message.cpp`和`hello-world.cpp`构建成一个可执行文件，但不生成任何一个库。

```cmake
# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-04 LANGUAGES CXX)

# introduce a toggle for using a library
set(USE_LIBRARY OFF) # define a  bool variant

message(STATUS "Compile sources into a library? ${USE_LIBRARY}")

# BUILD_SHARED_LIBS is a global flag offered by CMake
# to toggle the behavior of add_library
# when is setted off, call add_library and omit second argument (STATIC/SHARED ..) will generate a static library
set(BUILD_SHARED_LIBS OFF)

# list sources
list(APPEND _sources Message.hpp Message.cpp) # local variant

if(USE_LIBRARY)
  # add_library will create a static library
  # since BUILD_SHARED_LIBS is OFF
  add_library(message ${_sources})

  add_executable(hello-world hello-world.cpp)

  target_link_libraries(hello-world message)
else()
  add_executable(hello-world hello-world.cpp ${_sources})
endif()

```

```
objdump -f test
显示test的文件头信息

objdump -d test
反汇编test中的需要执行指令的那些section

objdump -D test
与-d类似，但反汇编test中的所有section

objdump -h test
显示test的Section Header信息

objdump -x test
显示test的全部Header信息

objdump -s test
除了显示test的全部Header信息，还显示他们对应的十六进制文件代码
```

`hello-world`可执行文件将使用所有源文件来编译。可以通过在GNU/Linux上，运行`objdump -x`命令进行验证。



我们介绍了两个变量：`USE_LIBRARY`和`BUILD_SHARED_LIBS`。这两个变量都设置为`OFF`。如CMake语言文档中描述，逻辑真或假可以用多种方式表示：

- 如果将逻辑变量设置为以下任意一种：`1`、`ON`、`YES`、`true`、`Y`或非零数，则逻辑变量为`true`。
- 如果将逻辑变量设置为以下任意一种：`0`、`OFF`、`NO`、`false`、`N`、`IGNORE、NOTFOUND`、空字符串，或者以`-NOTFOUND`为后缀，则逻辑变量为`false`。

`USE_LIBRARY`变量将在第一个和第二个行为之间切换。`BUILD_SHARED_LIBS`是CMake的一个全局标志。因为CMake内部要查询`BUILD_SHARED_LIBS`全局变量，所以`add_library`命令可以在不传递`STATIC/SHARED/OBJECT`参数的情况下调用；如果为`false`或未定义，将生成一个静态库。

这个例子说明，可以引入条件来控制CMake中的执行流。但是，当前的设置不允许从外部切换，不需要手动修改`CMakeLists.txt`。原则上，我们希望能够向用户开放所有设置，这样就可以在不修改构建代码的情况下调整配置，稍后将展示如何做到这一点。

**NOTE**:*`else()`和`endif()`中的`()`，可能会让刚开始学习CMake代码的同学感到惊讶。其历史原因是，因为其能够指出指令的作用范围。例如，可以使用`if(USE_LIBRARY)…else(USE_LIBRARY)…endif(USE_LIBIRAY)`。这个格式并不唯一，可以根据个人喜好来决定使用哪种格式。*

>
>
>??? 

**TIPS**:*`_sources`变量是一个局部变量，不应该在当前范围之外使用，可以在名称前加下划线。*

## 05向用户显示选项

```cmake
# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-05 LANGUAGES CXX)

# expose options to the user
# don't use set, use option !!!!!!!!!!!!!!!!!!!!!!!
option(USE_LIBRARY "Compile sources into a library" OFF)

message(STATUS "Compile sources into a library? ${USE_LIBRARY}")

include(CMakeDependentOption)

# second option depends on the value of the first
cmake_dependent_option(
  MAKE_STATIC_LIBRARY "Compile sources into a static library" OFF
  "USE_LIBRARY" ON
  )

# third option depends on the value of the first
cmake_dependent_option(
  MAKE_SHARED_LIBRARY "Compile sources into a shared library" ON
  "USE_LIBRARY" ON
  )

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# list sources
list(APPEND _sources Message.hpp Message.cpp)

if(USE_LIBRARY)
  message(STATUS "Compile sources into a STATIC library? ${MAKE_STATIC_LIBRARY}")
  message(STATUS "Compile sources into a SHARED library? ${MAKE_SHARED_LIBRARY}")

  if(MAKE_SHARED_LIBRARY)
    add_library(message SHARED ${_sources})

    add_executable(hello-world hello-world.cpp)

    target_link_libraries(hello-world message)
  endif()

  if(MAKE_STATIC_LIBRARY)
    add_library(message STATIC ${_sources})

    add_executable(hello-world hello-world.cpp)

    target_link_libraries(hello-world message)
  endif()
else()
  add_executable(hello-world hello-world.cpp ${_sources})
endif()

```

```cmake 
option(USE_LIBRARY "Compile sources into a library" OFF)
```

now we can use -D , CLI argument

```shell
mkdir -p build
cd build
cmake -D USE_LIBRARY=ON ..

-- Compile sources into a library? ON

```

`option`可接受三个参数：

```
option(<option_variable> "help string" [initial value])
```

- `<option_variable>`表示该选项的变量的名称。

- `"help string"`记录选项的字符串，在CMake的终端或图形用户界面中可见。

- `[initial value]`选项的默认值，可以是`ON`或`OFF`。

  

有时选项之间会有依赖的情况。示例中，我们提供生成静态库或动态库的选项。但是，如果没有将USE_LIBRARY逻辑设置为ON，则此选项没有任何意义。CMake提供cmake_dependent_option()命令用来定义依赖于其他选项的选项：

```cmake
include(CMakeDependentOption) # must inculde

# second option depends on the value of the first
cmake_dependent_option(
    MAKE_STATIC_LIBRARY "Compile sources into a static library" OFF
    "USE_LIBRARY" ON
    )
# third option depends on the value of the first
cmake_dependent_option(
    MAKE_SHARED_LIBRARY "Compile sources into a shared library" ON
    "USE_LIBRARY" ON
    )
   
# focus : cmake -D USE_LIBRARY=OFF -D MAKE_SHARED_LIBRARY=ON ..
# also will not genreate lib, beacuse USE_LIBRARY == OFF 
```

**TIPS**:*手册中的任何模块都可以以命令行的方式使用`cmake --help-module <name-of-module>`。例如，`cmake --help-module CMakeDependentOption`将打印刚才讨论的模块的手册页(帮助页面)。*

## 06指定编译器

