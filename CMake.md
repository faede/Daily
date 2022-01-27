

.PHONY clean

.PHONY表示伪目标，表示目标不是一个文件

如果不加的话 多次clean会显示up to date，无法使用

'JetBrains Mono','Inconsolata LGC','JetBrains Mono NL',Menlo, Monaco, 'Courier New', monospace

vscode 字体改变

```
https://blog.csdn.net/fightsyj/article/details/110144139
```



???? ===>  don't understand: remember to fix it

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



>在Unix/Linux下通常使用Makefile来控制代码的编译，但是Makefile对于比较大的项目有时候会比较慢，看看上面那副漫画，代码在编译都变成了程序员放松的借口了。所以这个Google的程序员在开发Chrome的时候因为忍受不了Makefile的速度，自己重新开发出来一套新的控制编译的工具叫作Ninja，Ninja相对于Makefile这套工具更注重于编译速度。除了Chrome现在还有一些其他的比较大的项目也在开始使用Ninja，比如LLVM。我试用了一下感觉还是不错，比如编译Cmake时间大概是原来的1/4。Ninja使用C++实现，其支持的语法非常简单，作者在这里说明是为了控制复杂度。

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

1. 使用CLI中的`-D`选项，例如：

   ```shell
   $ cmake -D CMAKE_CXX_COMPILER=clang++ ..
   ```

2. 通过导出环境变量`CXX`(C++编译器)、`CC`(C编译器)和`FC`(Fortran编译器)。例如，使用这个命令使用`clang++`作为`C++`编译器：

   ```shell
   $ env CXX=clang++ cmake ..
   ```

到目前为止讨论的示例，都可以通过传递适当的选项，配置合适的编译器。

**NOTE**:*CMake了解运行环境，可以通过其CLI的`-D`开关或环境变量设置许多选项。前一种机制覆盖后一种机制，但是我们建议使用`-D`显式设置选项。显式优于隐式，因为环境变量可能被设置为不适合(当前项目)的值。*

我们在这里假设，其他编译器在标准路径中可用，CMake在标准路径中执行查找编译器。如果不是这样，用户将需要将完整的编译器可执行文件或包装器路径传递给CMake。

**TIPS**:*我们建议使用`-D CMAKE_<LANG>_COMPILER`CLI选项设置编译器，而不是导出`CXX`、`CC`和`FC`。这是确保跨平台并与非POSIX兼容的唯一方法。为了避免变量污染环境，这些变量可能会影响与项目一起构建的外部库环境。*

我们的平台上的CMake，在哪里可以找到可用的编译器和编译器标志？CMake提供`--system-information`标志，它将把关于系统的所有信息转储到屏幕或文件中。要查看这个信息，请尝试以下操作：

```shell
$ cmake --system-information information.txt
```

文件中(本例中是`information.txt`)可以看到`CMAKE_CXX_COMPILER`、`CMAKE_C_COMPILER`和`CMAKE_Fortran_COMPILER`的默认值，以及默认标志。我们将在下一个示例中看到相关的标志。

CMake提供了额外的变量来与编译器交互：

- `CMAKE_<LANG>_COMPILER_LOADED`:如果为项目启用了语言`<LANG>`，则将设置为`TRUE`。
- `CMAKE_<LANG>_COMPILER_ID`:编译器标识字符串，编译器供应商所特有。例如，`GCC`用于GNU编译器集合，`AppleClang`用于macOS上的Clang, `MSVC`用于Microsoft Visual Studio编译器。注意，不能保证为所有编译器或语言定义此变量。
- `CMAKE_COMPILER_IS_GNU<LANG>`:如果语言`<LANG>`是GNU编译器集合的一部分，则将此逻辑变量设置为`TRUE`。注意变量名的`<LANG>`部分遵循GNU约定：C语言为`CC`, C++语言为`CXX`, Fortran语言为`G77`。
- `CMAKE_<LANG>_COMPILER_VERSION`:此变量包含一个字符串，该字符串给定语言的编译器版本。版本信息在`major[.minor[.patch[.tweak]]]`中给出。但是，对于`CMAKE_<LANG>_COMPILER_ID`，不能保证所有编译器或语言都定义了此变量。

我们可以尝试使用不同的编译器，配置下面的示例`CMakeLists.txt`。这个例子中，我们将使用CMake变量来探索已使用的编译器(及版本)：

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(recipe-06 LANGUAGES C CXX)
message(STATUS "Is the C++ compiler loaded? ${CMAKE_CXX_COMPILER_LOADED}")
if(CMAKE_CXX_COMPILER_LOADED)
    message(STATUS "The C++ compiler ID is: ${CMAKE_CXX_COMPILER_ID}")
    message(STATUS "Is the C++ from GNU? ${CMAKE_COMPILER_IS_GNUCXX}")
    message(STATUS "The C++ compiler version is: ${CMAKE_CXX_COMPILER_VERSION}")
endif()
message(STATUS "Is the C compiler loaded? ${CMAKE_C_COMPILER_LOADED}")
if(CMAKE_C_COMPILER_LOADED)
    message(STATUS "The C compiler ID is: ${CMAKE_C_COMPILER_ID}")
    message(STATUS "Is the C from GNU? ${CMAKE_COMPILER_IS_GNUCC}")
    message(STATUS "The C compiler version is: ${CMAKE_C_COMPILER_VERSION}")
endif()
```

## 07切换构建类型

CMake可以配置构建类型，例如：Debug、Release等。配置时，可以为Debug或Release构建设置相关的选项或属性，例如：编译器和链接器标志。控制生成构建系统使用的配置变量是`CMAKE_BUILD_TYPE`。该变量默认为空，CMake识别的值为:

1. **Debug**：用于在没有优化的情况下，使用带有调试符号构建库或可执行文件。
2. **Release**：用于构建的优化的库或可执行文件，不包含调试符号。
3. **RelWithDebInfo**：用于构建较少的优化库或可执行文件，包含调试符号。
4. **MinSizeRel**：用于不增加目标代码大小的优化方式，来构建库或可执行文件。

> https://stackoverflow.com/questions/48754619/what-are-cmake-build-type-debug-release-relwithdebinfo-and-minsizerel

  ```cmake
  # set minimum cmake version
  cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
  
  # project name and language
  project(recipe-07 LANGUAGES C CXX)
  
  # we default to Release build type
  if(NOT CMAKE_BUILD_TYPE)
  	# set it as a cache object, we can edit it by cache
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
  endif()
  
  # print falgs
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
  
  message(STATUS "C flags, Debug configuration: ${CMAKE_C_FLAGS_DEBUG}")
  message(STATUS "C flags, Release configuration: ${CMAKE_C_FLAGS_RELEASE}")
  message(STATUS "C flags, Release configuration with Debug info: ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
  message(STATUS "C flags, minimal Release configuration: ${CMAKE_C_FLAGS_MINSIZEREL}")
  
  message(STATUS "C++ flags, Debug configuration: ${CMAKE_CXX_FLAGS_DEBUG}")
  message(STATUS "C++ flags, Release configuration: ${CMAKE_CXX_FLAGS_RELEASE}")
  message(STATUS "C++ flags, Release configuration with Debug info: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
  message(STATUS "C++ flags, minimal Release configuration: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
  
  ```

defakut:

```shell
-- Build type: Release
-- C flags, Debug configuration: -g
-- C flags, Release configuration: -O3 -DNDEBUG
-- C flags, Release configuration with Debug info: -O2 -g -DNDEBUG
-- C flags, minimal Release configuration: -Os -DNDEBUG
-- C++ flags, Debug configuration: -g
-- C++ flags, Release configuration: -O3 -DNDEBUG
-- C++ flags, Release configuration with Debug info: -O2 -g -DNDEBUG
-- C++ flags, minimal Release configuration: -Os -DNDEBUG
```

`cmake -H. -Bbuild -D CMAKE_BUILD_TYPE=Debug`

```shell
-- Build type: Debug
-- C flags, Debug configuration: -g
-- C flags, Release configuration: -O3 -DNDEBUG
-- C flags, Release configuration with Debug info: -O2 -g -DNDEBUG
-- C flags, minimal Release configuration: -Os -DNDEBUG
-- C++ flags, Debug configuration: -g
-- C++ flags, Release configuration: -O3 -DNDEBUG
-- C++ flags, Release configuration with Debug info: -O2 -g -DNDEBUG
-- C++ flags, minimal Release configuration: -Os -DNDEBUG
-- Configuring done
```



## 08设置编译器选项

in compute-areas:

```cpp
#include "geometry_circle.hpp"
#include "geometry_polygon.hpp"
#include "geometry_rhombus.hpp"
#include "geometry_square.hpp"
```

CMake为调整或扩展编译器标志提供了很大的灵活性，您可以选择下面两种方法:

- CMake将编译选项视为目标属性。因此，可以根据每个目标设置编译选项，而不需要覆盖CMake默认值。
- 可以使用`-D`CLI标志直接修改`CMAKE_<LANG>_FLAGS_<CONFIG>`变量。这将影响项目中的所有目标，并覆盖或扩展CMake默认值。

```cmake
# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-08 LANGUAGES CXX)

message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")

list(APPEND flags "-fPIC" "-Wall")
if(NOT WIN32)
  list(APPEND flags "-Wextra" "-Wpedantic")
endif()

add_library(geometry
  STATIC
    geometry_circle.cpp
    geometry_circle.hpp
    geometry_polygon.cpp
    geometry_polygon.hpp
    geometry_rhombus.cpp
    geometry_rhombus.hpp
    geometry_square.cpp
    geometry_square.hpp
  )

# complie option for library
target_compile_options(geometry
  PRIVATE
    ${flags}
  )

add_executable(compute-areas compute-areas.cpp)

# complie option for executable object
target_compile_options(compute-areas
  PRIVATE
    "-fPIC"
  )

target_link_libraries(compute-areas geometry)

```

可见性的含义如下:

- **PRIVATE**，编译选项会应用于给定的目标，不会传递给与**目标相关的目标**。我们的示例中， 即使`compute-areas`将链接到`geometry`库，`compute-areas`也不会继承`geometry`目标上设置的编译器选项。
- **INTERFACE**，给定的编译选项将只应用于**指定目标**，并传递给与**目标相关的目标**。
- **PUBLIC**，编译选项将应用于**指定目标**和**使用它的目标**。

目标属性的可见性CMake的核心，我们将在本书中经常讨论这个话题。以这种方式添加编译选项，不会影响全局CMake变量`CMAKE_<LANG>_FLAGS_<CONFIG>`，并能更细粒度控制在哪些目标上使用哪些选项。

 ?????

链接到 => links in

https://cmake.org/pipermail/cmake/2016-May/063400.html

>- When A links in B as *PRIVATE*, it is saying that A uses B in its
   implementation, but B is not used in any part of A's public API. Any code
    that makes calls into A would not need to refer directly to anything from
    B. An example of this could be a networking library A which can be built to
    use one of a number of different SSL libraries internally (which B
    represents). A presents a unified interface for client code which does not
    reference any of the internal SSL data structures or functions. Client code
    would have no idea what SSL implementation (B) is being used by A, nor does
    that client code need to care.
   - When A links in B as *INTERFACE*, it is saying that A does not use B
   in its implementation, but B is used in A's public API. Code that calls
      into A may need to refer to things from B in order to make such calls. One
      example of this is an interface library which simply forwards calls along
      to another library but doesn't actually reference the objects on the way
      through other than by a pointer or reference. Another example is where A is
      defined in CMake as an interface library, meaning it has no actual
      implementation itself, it is effectively just a collection of other
      libraries (I'm probably over-simplifying here, but you get the picture).
   - When A links in B as *PUBLIC*, it is essentially a combination of
   PRIVATE and INTERFACE. It says that A uses B in its implementation and B is
      also used in A's public API.
>

我们如何验证，这些标志是否按照我们的意图正确使用呢？或者换句话说，如何确定项目在CMake构建时，实际使用了哪些编译标志？一种方法是，使用CMake将额外的参数传递给本地构建工具

```shell
cmake --build . -- VERBOSE=1
```

|      | Flag     | Description                                                  |
| :--- | :------- | ------------------------------------------------------------ |
| 1    | -g       | Produced debugging information in the operating system’s native format. |
| 2    | -Os      | Optimize for size.                                           |
| 3    | -O2      | GCC performs nearly all supported optimizations that do not involve a space-speed trade-off. |
| 4    | -O3      | Turns on all optimizations specified by -O2 in addition to other various optimization options. |
| 5    | -DNDEBUG | Disables assertions for GCC and Clang.                       |

控制编译器标志的第二种方法，不用对`CMakeLists.txt`进行修改。如果想在这个项目中修改`geometry`和`compute-areas`目标的编译器选项，可以使用CMake参数进行配置：

```
$ cmake -D CMAKE_CXX_FLAGS="-fno-exceptions -fno-rtti" ..
```

这个命令将编译项目，禁用异常和运行时类型标识(RTTI)。

也可以使用全局标志，可以使用`CMakeLists.txt`运行以下命令：

```
$ cmake -D CMAKE_CXX_FLAGS="-fno-exceptions -fno-rtti" ..
```

这将使用`-fno-rtti - fpic - wall - Wextra - wpedantic`配置`geometry`目标，同时使用`-fno exception -fno-rtti - fpic`配置`compute-areas`。

**NOTE**:*本书中，我们推荐为每个目标设置编译器标志。使用`target_compile_options()`不仅允许对编译选项进行细粒度控制，而且还可以更好地与CMake的更高级特性进行集成。*控制编译器标志的第二种方法，不用对`CMakeLists.txt`进行修改。如果想在这个项目中修改`geometry`和`compute-areas`目标的编译器选项，可以使用CMake参数进行配置：

```
$ cmake -D CMAKE_CXX_FLAGS="-fno-exceptions -fno-rtti" ..
```

这个命令将编译项目，禁用异常和运行时类型标识(RTTI)。

>https://docs.microsoft.com/en-us/cpp/cpp/run-time-type-information?view=msvc-170#:~:text=Run%2Dtime%20type%20information%20(RTTI)%20is%20a%20mechanism%20that,were%20implementing%20this%20functionality%20themselves.
>
>Run-time type information (RTTI) is a mechanism that allows the type of an object to be determined during program execution. RTTI was added to the C++ language because many vendors of class libraries were implementing this functionality themselves. This caused incompatibilities between libraries. Thus, it became obvious that support for run-time type information was needed at the language level.
>
>For the sake of clarity, this discussion of RTTI is almost completely restricted to pointers. However, the concepts discussed also apply to references.
>
>There are three main C++ language elements to run-time type information:
>
>- The [dynamic_cast](https://docs.microsoft.com/en-us/cpp/cpp/dynamic-cast-operator?view=msvc-170) operator.
>
>  Used for conversion of polymorphic types.
>
>- The [typeid](https://docs.microsoft.com/en-us/cpp/cpp/typeid-operator?view=msvc-170) operator.
>
>  Used for identifying the exact type of an object.
>
>- The [type_info](https://docs.microsoft.com/en-us/cpp/cpp/type-info-class?view=msvc-170) class.
>
>  Used to hold the type information returned by the **`typeid`** operator.
>
>

也可以使用全局标志，可以使用`CMakeLists.txt`运行以下命令：

```
$ cmake -D CMAKE_CXX_FLAGS="-fno-exceptions -fno-rtti" ..
```

这将使用`-fno-rtti - fpic - wall - Wextra - wpedantic`配置`geometry`目标，同时使用`-fno exception -fno-rtti - fpic`配置`compute-areas`。

注： 这里应该是说如果使用(定义了)全局标志（CMAKE_CXX_FLAGS），直接设置也没有问题

**NOTE**:*本书中，我们推荐为每个目标设置编译器标志。使用`target_compile_options()`不仅允许对编译选项进行细粒度控制，而且还可以更好地与CMake的更高级特性进行集成。*

大多数时候，编译器有特性标示。当前的例子只适用于`GCC`和`Clang`；其他供应商的编译器不确定是否会理解(如果不是全部)这些标志。如果项目是真正跨平台，那么这个问题就必须得到解决，有三种方法可以解决这个问题。

最典型的方法是将所需编译器标志列表附加到每个配置类型CMake变量`CMAKE_<LANG>_FLAGS_<CONFIG>`。标志确定设置为给定编译器有效的标志，因此将包含在`if-endif`子句中，用于检查`CMAKE_<LANG>_COMPILER_ID`变量，例如：

```cmake
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  list(APPEND CMAKE_CXX_FLAGS "-fno-rtti" "-fno-exceptions")
  list(APPEND CMAKE_CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")
  list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  list(APPEND CMAKE_CXX_FLAGS "-fno-rtti" "-fno-exceptions" "-Qunused-arguments" "-fcolor-diagnostics")
  list(APPEND CMAKE_CXX_FLAGS_DEBUG "-Wdocumentation")
  list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()
```

更细粒度的方法是，不修改`CMAKE_<LANG>_FLAGS_<CONFIG>`变量，而是定义特定的标志列表：

```cmake
set(COMPILER_FLAGS)
set(COMPILER_FLAGS_DEBUG)
set(COMPILER_FLAGS_RELEASE)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  list(APPEND CXX_FLAGS "-fno-rtti" "-fno-exceptions")
  list(APPEND CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-override")
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  list(APPEND CXX_FLAGS "-fno-rtti" "-fno-exceptions" "-Qunused-arguments" "-fcolor-diagnostics")
  list(APPEND CXX_FLAGS_DEBUG "-Wdocumentation")
  list(APPEND CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()
```

稍后，使用生成器表达式来设置编译器标志的基础上，为每个配置和每个目标生成构建系统:

```cmake
target_compile_option(compute-areas
  PRIVATE
    ${CXX_FLAGS}
    "$<$<CONFIG:Debug>:${CXX_FLAGS_DEBUG}>"
    "$<$<CONFIG:Release>:${CXX_FLAGS_RELEASE}>"
  )
```

当前示例中展示了这两种方法，我们推荐后者(特定于项目的变量和`target_compile_options`)。

两种方法都有效，并在许多项目中得到广泛应用。不过，每种方式都有缺点。`CMAKE_<LANG>_COMPILER_ID`不能保证为所有编译器都定义。此外，一些标志可能会被弃用，或者在编译器的较晚版本中引入。与`CMAKE_<LANG>_COMPILER_ID`类似，`CMAKE_<LANG>_COMPILER_VERSION`变量不能保证为所有语言和供应商都提供定义。尽管检查这些变量的方式非常流行，但我们认为更健壮的替代方法是检查所需的标志集是否与给定的编译器一起工作，这样项目中实际上只使用有效的标志。结合特定于项目的变量、`target_compile_options`和生成器表达式，会让解决方案变得非常强大。

## 09为语言设定标准

???

```cpp
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Factory.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>

typedef std::function<std::unique_ptr<Animal>(const std::string &)> CreateAnimal;

int main() {
  Factory<CreateAnimal> farm;
  farm.subscribe("CAT",
                 [](const std::string &n) { return std::make_unique<Cat>(n); });
  farm.subscribe("DOG",
                 [](const std::string &n) { return std::make_unique<Dog>(n); });

  std::unique_ptr<Animal> simon = farm.create("CAT", "Simon");
  std::unique_ptr<Animal> marlowe = farm.create("DOG", "Marlowe");

  std::cout << simon->name() << std::endl;
  std::cout << marlowe->name() << std::endl;

  return EXIT_SUCCESS;
}

```

```cmake
# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-09 LANGUAGES CXX)

# print all lib symbol on windows
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(animals
  SHARED
    Animal.cpp
    Animal.hpp
    Cat.cpp
    Cat.hpp
    Dog.cpp
    Dog.hpp
    Factory.hpp
  )

set_target_properties(animals
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
    POSITION_INDEPENDENT_CODE 1
  )

add_executable(animal-farm animal-farm.cpp)

set_target_properties(animal-farm
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )

target_link_libraries(animal-farm animals)

```

步骤4和步骤5中，我们为动物和动物农场目标设置了一些属性:

- **CXX_STANDARD**会设置我们想要的标准。
- **CXX_EXTENSIONS**告诉CMake，只启用`ISO C++`标准的编译器标志，而不使用特定编译器的扩展。
- **CXX_STANDARD_REQUIRED**指定所选标准的版本。如果这个版本不可用，CMake将停止配置并出现错误。当这个属性被设置为`OFF`时，CMake将寻找下一个标准的最新版本，直到一个合适的标志。这意味着，首先查找`C++14`，然后是`C++11`，然后是`C++98`。（译者注：目前会从`C++20`或`C++17`开始查找）

通过引入编译特性，CMake对语言标准提供了更精细的控制。这些是语言标准引入的特性，比如`C++11`中的可变参数模板和`Lambda`表达式，以及`C++14`中的自动返回类型推断。可以使用`target_compile_features()`命令要求为特定的目标提供特定的特性，CMake将自动为标准设置正确的编译器标志。也可以让CMake为可选编译器特性，生成兼容头文件。

>https://cliutils.gitlab.io/modern-cmake/chapters/features/cpp11.html
>
>https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html
>
>```cmake
>target_compile_features(<target> <PRIVATE|PUBLIC|INTERFACE> <feature> [...])
>```
>
>target_compile_features(myTarget PUBLIC cxx_std_11)
>set_target_properties(myTarget PROPERTIES CXX_EXTENSIONS OFF)

## 10使用控制流

```cmake
# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(recipe-10 LANGUAGES CXX)

add_library(geometry
  STATIC
    geometry_circle.cpp
    geometry_circle.hpp
    geometry_polygon.cpp
    geometry_polygon.hpp
    geometry_rhombus.cpp
    geometry_rhombus.hpp
    geometry_square.cpp
    geometry_square.hpp
  )

# we wish to compile the library with the optimization flag: -O3
target_compile_options(geometry
  PRIVATE
    -O3
  )

list(
  APPEND sources_with_lower_optimization
    geometry_circle.cpp
    geometry_rhombus.cpp
  )

# set
# we use the IN LISTS foreach syntax to set source properties
message(STATUS "Setting source properties using IN LISTS syntax:")
foreach(_source IN LISTS sources_with_lower_optimization)
  set_source_files_properties(${_source} PROPERTIES COMPILE_FLAGS -O2)
  message(STATUS "Appending -O2 flag for ${_source}")
endforeach()

# check
# we demonstrate the plain foreach syntax to query source properties
# which requires to expand the contents of the variable
message(STATUS "Querying sources properties using plain syntax:")
foreach(_source ${sources_with_lower_optimization})
  get_source_file_property(_flags ${_source} COMPILE_FLAGS)
  message(STATUS "Source ${_source} has the following extra COMPILE_FLAGS: ${_flags}")
endforeach()

add_executable(compute-areas compute-areas.cpp)

target_link_libraries(compute-areas geometry)

```



```shell
$ mkdir -p build
$ cd build
$ cmake ..

-- Setting source properties using IN LISTS syntax:
-- Appending -O2 flag for geometry_circle.cpp
-- Appending -O2 flag for geometry_rhombus.cpp
-- Querying sources properties using plain syntax:
-- Source geometry_circle.cpp has the following extra COMPILE_FLAGS: -O2
-- Source geometry_rhombus.cpp has the following extra COMPILE_FLAGS: -O2
```



```shell
$ cmake --build . -- VERBOSE=1

.....-O3 -O2 -MD -MT CMakeFiles/geometry.dir/geometry_circle.cpp.o
```

**NOTE**: *CMake中，列表是用分号分隔的字符串组。列表可以由`list`或`set`命令创建。例如，`set(var a b c d e)`和`list(APPEND var a b c d e)`都创建了列表`a;b;c;d;e`。*

**TIPS**: *为了对一组文件降低优化，将它们收集到一个单独的目标(库)中，并为这个目标显式地设置优化级别，而不是附加一个标志，这样可能会更简洁，不过在本示例中，我们的重点是`foreach-endforeach`。*



`foreach()`的四种使用方式:

- `foreach(loop_var arg1 arg2 ...)`: 其中提供循环变量和显式项列表。当为`sources_with_lower_optimization`中的项打印编译器标志集时，使用此表单。注意，如果项目列表位于变量中，则必须显式展开它；也就是说，`${sources_with_lower_optimization}`必须作为参数传递。
- 通过指定一个范围，可以对整数进行循环，例如：`foreach(loop_var range total)`或`foreach(loop_var range start stop [step])`。
- 对列表值变量的循环，例如：`foreach(loop_var IN LISTS [list1[...]])` 。参数解释为列表，其内容就会自动展开。
- 对变量的循环，例如：`foreach(loop_var IN ITEMS [item1 [...]])`。参数的内容没有展开。
