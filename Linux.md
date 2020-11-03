ls 

第一个字母 目录(d) 、文件(-)、字符型文件(c)、块设备(b)



touch test_one

创建新的空文件,更改文件的修改时间（不需要改变内容）



链接文件

符号链接，是一个文件，指向存放在虚拟目录结构中某个地方的另一个文件。两个通过符号链接在一起的文件，彼此内容并不相同。

ln -s data_file sl_data_file

sl指向data

inode不同。

硬链接

创建独立的虚拟文件，其中包含了原始文件的信息和位置，本质上是同一个文件，引用硬链接文件等于引用了源文件。

inode相同。

只能对处于同一存储媒体的文件创建硬链接，否则只能用符号链接。



mv

移动或重命名



rm 

建议加-i

rm -i fall

-f强制删除



mkdir

创建目录

mkdir -p new_dir/sub_dir/under_dir

-p参数会自动创建缺失的目录。



rmdir

默认只接受空目录

或者 rm -ri My_Dir



tree

展示目录树



### 3.8查看文件内容

file My_file

查看文件类型，编码，符号链接，二进制文件需要何种库



cat test1

显示

-n 加上行号

-b 只给有文本的地方加行号

-T 不显示制表符(^I )替换所有制表符



more

显示一页之后就停下来



less

加强more （less is more）

可以上下键翻页等



tail

展示尾部文件，默认10行

tail -n 2 log_file

只展示最后两行



head

前十行

head -5 log_file



## 更多的bash shell命令

### 4.1监测程序

ps

默认显示运行在当前控制台下的属于当前用户的进程

Unix风格的参数，前面加单破折号。

BSD风格的参数，前面不加破折号。

GNU风格的长参数前面加双破折线。



ps -ef

查看系统运行的所有进程

-f

UID 启动进程的用户，PID进程的进程ID，PPID父进程的进程号，C进程生命周期中CPU利用率，STIME进程启动时系统时间，TTY进程启动时的中断设备，TIME运行进程需要的累计CPU时间，CMD启动的程序名称。

ps -l

F内个分配给进程的系统标记，S进程的转台,PRI进程的优先级（和数字大小成反比），NI谦让度值用来决定优先级，ADDR进程的内存地址，SZ加入进程被换出，所需交换空间的大致大小，WCHAN进程休眠的内核函数的地址。

ps --forest

显示进程的层级信息。



top

ps只能显示某个特定时间点的信息，动态使用top



Linux中进程之间通过信号来通信。

信号 名称 描述

1	HUP	挂起

2	INT	中断

3	QUIT	结束进程

9	KILL	无条件错误

11	SEGV	段错误	

15	TERM	 尽可能终止

17	STOP	无条件停止运行，但不终止

18	TSTP	停止或暂停，但继续在后台运行

19	CONT	在STOP或TSTP之后继续执行

kill

kill 3940

通过PID给进程发信号

kill -s HUP 3940

如果要强制终止，-s参数支持其他信号。

### 4.2 监测磁盘空间

Linux文件系统将所有的磁盘都并入一个虚拟目录下。在使用新的存储媒体之前需要把它放入虚拟目录下，这项工作成为挂载。



mount

输出当前系统上挂载的设备列表

四部分：

媒体的设备文件名	媒体挂载到虚拟目录下的挂载点	文件系统类型	已挂载媒体的访问状态

mount -t type device directory

type参数指定了磁盘被格式化的系统文件类型。



umount [directory| device]

卸载设备，正在使用时不允许卸载



df

查看所有已挂载磁盘的使用情况



du

显示某个特定目录（默认当前）的磁盘使用情况

左边占用的磁盘块数，列表从目录层级的最底部开始，按文件、子目录、目录逐级向上。

-c 显示所有已列出文件的总大小

-h 按用户易读的格式输出大小



### 4.3处理数据

sort

排序数据，默认被当做字符来排序

sort -n file2

排序数字

sort -M file3

按日期排序

sort 	-t 	':' 	-k	3 	-n /etc/passwd

-t参数指定字段分隔符，-k参数指定排序的字段。

du -sh | sort -nr

-r反向



grep [options] pattern [file]

grep在输入或指定的文件中查找包含匹配指定模式的字符的行

-v 

反向搜索，输出不匹配该模式的行

-n 显示行号

grep -e t -e f

-e指定多个匹配模式



压缩数据

工具				文件拓展名			描述

bzip2 			 .bz2			采用Burrows-Wheeler块排序文本压缩算法和霍夫曼编码

compress		.Z				最初的Unix文件压缩工具（几乎不使用）

gzip				.gz				GNU压缩工具，采用Lepel-Ziv编码

zip					,zip			windows上的PKZIP工具的Unix实现

gzip	压缩文件

gzcat	哟你查看压缩过的文件

gunzip	用来解压文件



归档数据

tar命令用来将文件写入到磁带设备上归档，也能把输出写出到文件里

tar function [options]   object1   object2

function

功能	长名称	描述

-A	 --concatenate	将一个已有tar归档文件追加到另一个已有tar归档文件

-c	--cteate	 创建一个新的tar归档文件

-d 	--diff	检查归档文件和文件系统的不同之处

​		--delete	 从已有tar归档文件中删除

-r	--apend	追加文件到已有tar归档文件末尾

-t	 --list	追出已有tar文档文件文件的内容

-u 	--update	将比tar归档文件中已有的同名文件新的文件追加到该tar归档文件中

-x --extract从已有tar归档文件中提取文件

options

选项				描述

-c dir			切换到指定目录

-f file			输出结果到文件或设备file

-j					将输出重定向给bzip2命令来压缩内容

-p				保留所用文件权限

-v				在处理文件时显示文件

-z				将输出重定向给gzip命令来压缩内容

tar -cvf test.tar	test/	test2/

创建一个归档文件test.tat包含test和test2目录内容

tar -tf test.tar

列出文件test.tar的内容（但并不提取）

tar -xvf	test.tar

提取test.tar的内容

.tgz是gzip压缩过的tar文件，可以用命令tar -zxvf filename.tgz 来解压



## 5理解shell

bash

 在当前bash下创建子bash

-c string 

从string 中读取命令并进行处理

-i

启动一个能够接收用户输入的交互bash

-l

以登陆shell的形式启动

-r

启动一个受限shell，用户会被限制在默认目录

-s

从标准输入中读取命令



一行依次运行多个命令，用; 分开

要想组成进程列表，需要在外边加上（），尽管加括号后看起来没什么不同，但是加括号，让命令列表变成了进程列表，生成了一个子shell来执行对应的命令。

另一种{ comand;},不创建子shell

echo  $BASH_SUBSHELL,如果返回1或者更大的数字，就说明有子shell





sleep 10

让进程等待（休眠），10秒，然后返回CLI提示符

sleep 10&

把sleep命令置于后台模式。输出后台作业号和后台作业的进程ID



jobs

显示出当前运行在后台模式中的所有用户进程（作业）



(sleep 10;echo 2;sleep 10)&; 

后台作业



协程

coproc sleep 10

在后台生成一个shell，并在这个shell中执行命令。

coproc My_Job  { sleep 10; }

通过拓展语法，重命名协程名字为 My_Job，但是{（}）前（后），要加空格，并且命令要以；结尾





### 5.3理解shell的内建命令

外部命令，也成为文件系统命令。是存在于bash shell 之外的程序。它们并不是shell程序的一部分。外部命令通常位于/bin、/usr/bin、/sbin或/usr/sbin中。

ps就是一个外部命令，可以用which，type命令找到。



当外部命令执行时，会创建一个子进程，这种操作称为衍生（forking）。

输入ps -f，父进程发出外部命令：ps -f，衍生子进程，子进程执行外部命令ps  -f



内建命令

不需要子进程来执行，效率更高，执行速度更快。

type -a echo

如果有两种实现方式，则显示每个命令的两种实现。注意which只显示出来外部命令文件，对于多种实现命令，如果需要使用外部命令，可以直接输入对应文件 比如/bin/pwd



history

内建命令，显示最近用过的命令列表。默认保存1000条，可以通过修改名为HISTSIZE的环境变量修改。



!!

输入!!唤起并重用历史列表中最近使用的命令，然后执行。

命令历史记录放在隐藏文件.bash_history中，它位于用户的主目录中，并且bash的历史记录先是存放在内存当中，当shell退出时才被写入到历史文件中。

history -a

强制写入历史文件。

history -n

使用history -a多个终端时在一个终端中强制写入其他不会更新，要想更新使用



命令别名

alias -p

查看系统中命令的别名





alias li='ls -li'

创建自己的别名，但是只在它所被定义的shell进程中才有效，要想都有效之后介绍。



## 6使用Linux环境变量

bash shell用一个叫做环境变量的特性来存储有关shell会话和工作环境的信息。

- 全局环境变量
- 局部环境变量



全局环境变量

对于shell会话和所有生成的子shell都可见，局部变量只对创建它们的shell可见。

printenv 或者env

查看全局变量



printenv    HOME

查看个别变量，env不可以使用，或者

echo $HOME

还能让变量作为命令行参数。



局部环境变量

set

显示全局变量，局部变量以及用户定义变量，还会按照字母顺序对结果排序，env和printenv不会排序，也不会输出局部变量和用户定义变量，但是env又一个printenv没有的功能，这使它要更有用一些。



设置局部用户定义变量

echo $my_variable

my_variable=Hello

echo $my_variable

赋值含有空格的字符串时，要加""

窍门：所有环境变量都使用大写字母，这是bash shell的标准惯例，如果是自己创建的局部变脸或者是shell脚本变量请使用小写字母，变量名区分大小写，涉及到哟哦难怪乎局部变量时坚持使用小写字母，这能够有效的避免重新定义系统环境变量可能带来的灾难。

my_variable = "Hello word"

错误，变量名、等号和值之间没有空格，如果加上bash shell会把值当作一个单独的命令





设置全局环境变量

在设定全局环境变量的进程所创建的子进程中，该变量都是可见的。创建全局环境变量的方法是：先创建一个局部环境变量，然后再把它导出到全局环境中。

my_variable="Hello word"

export my_variable

在定义并导出环境变量后，子shell能正确显示出变量my_variable的值。

**修改子shell中全局变量并不会影响到父shell中该变量的值。**



删除环境变量

unset my_variable

不加$



但是处理全局变量时，子进程中删除一个全局环境变量，只对子进程有效，该全局环境变量在父进程中依然可用，和修改变量一样，在子进程中删除全局变量后无法将效果映射到父shell中。



涉及到环境变量名时什么时候加$,什么时候不加，关键点：如果要用到变量，使用$, 如果要操作变量，不使用$,这条规则的一个例外就是使用printenv显示某个变量的值。



默认的shell环境变量

略



设置PATH环境变量

当在shell命令行界面输入一个外部命令时，shell必须搜索系统来找到对应的程序，PATH环境变量定义了用于进行命令和程序查找的目录 。



echo $PATH

冒号分开，如果命令或程序不在PATH变量中，那么如果不使用绝对路径，shell是没办法找到的。

PATH中各个目录是由冒号分隔。

添加环境变量

PATH=$PATH:/home/christine/Scripts

如果希望子shell也能找到程序的位置，一定要将修改后的PATH环境变量导出



程序员常见的办法是将单点符也加入PATH环境变量中。

PATH=$PATH:.



定位系统环境变量

当登入Linux启动一个bash shell时，默认情况下会在几个文件中查找命令，这些文件叫做启动文件或环境文件。bash检查的启动文件取决于你启动bash shell的方式。启动bash shell有三种方式

**登录时作为默认登录shell**

**作为非登录shell的交互式shell**

**作为运行脚本的非交互式shell**



当你登录Linux时，bash shell会作为登录shell启动，登录shell会从5个不同的启动文件读取命令。

/etc/profile

$HOME/.bash_profile

$HOME/.bashrc

$HOME/.bash_login

$HOME/.profile



在bash shell输入bash启动的是交互式shell，系统执行的是非交互式shell 



环境变量持久啊

对于系统所有用户都使用的变量可以放到/etc/profile中，但是一旦你升级了所用的发行版，那么这个文件也会更新，最好是在/etc/profile.d目录中创建一个以.sh为结尾的文件，把新的或修改过的文件放到这里。

对大多是发行版中，存储个人用户永久性bash shell 变量的地方是$HOME/.bash_src，这适用于所有类型的shell，但是如果设置了BASH_EV变量，那么除非它指向$HOME/.bashrc，否则你应该将非交互式shell 的用户变量放到其它位置。



数组变量

mytest = (one two three four five)

但是

$ echo $mytest

one

$ echo ${mytest[2]}

three

$ echo ${mytest[*]}

one two three four five

$mytest[2] = seven

$ echo ${mytest[*]}

one two seven four five

$ unset mytest[2]

$

$ echo ${mytest[*]}

one two  four five

$ echo ${mytest[2]}



$ echo ${mytest[3]}

four

## 7理解Linux文件权限

用户权限是通过创建用户时分配的UID来跟踪。



/etc/passwd

root是管理员，UID为0

字段包括：登录用户名、用户密码、用户账户的UID、用户账户组的ID、用户账户的文本描述、用户HOME目录的位置、用户默认shell，密码字段都为x是为了安全。

现在密码都放在了/etc/shadow 文件中，只有特定的程序（比如登录程序）才能访问。



/etc/shadow文件

9个字段：

与etc/passwd文件中的登录名字字段对应的登录名

加密后的密码

自上次修改密码过后的天数（自1970年1月1日开始计算）

多少天后才能更改密码

多少天后必须更改密码

密码过期前提前多少天提醒用户更改密码

密码过期后多少天禁用用户账户

用户账户被禁用的日期（自1970年1月1日到当天的天数表示）

预留字段给将来使用。



添加新用户

useradd

系统默认值被设置在/etc/default/useradd文件中，使用useradd的-D选项可以查看。

/usr/sbin/useradd -D



删除用户

### 构建基本脚本

有两种方法可以将**命令**输出赋给变量：

1.反引号字符 (\`）`testing='date'`

2.$()格式 `testing=$(date)`



### 输出重定向

用大于号（>）

将命令的输出追加到已有文件中用双大于号（>>）



### 输入重定向

符号是小于号（<）

内联输入重定向（<<）你必须指定一个文本标记来划分输入数据的开始和结尾,在命令行上使用内联输入重定向时，shell会用PS2环境变量中定义的次提示符来提示输入数据。次提示符会持续提示，以获取更多的输入数据，直到你输入了作为文本标记的那个字符串。

### 管道

command1 | command2

不要以为由管道串起的两个命令会依次执行。Linux系统实际上会同时运行这两个命令，在系统内部将它们连接起来。在第一个命令产生输出的同时，输出会被立即送给第二个命令。数据传输不会用到任何中间文件或缓冲区。

到目前为止，管道最流行的用法之一是将命令产生的大量输出通过管道传送给more命令。这对ls命令来说尤为常见.



### 执行数学运算



### expr 命令(Bourne shell)

expr命令能够识别少数的数学和字符串操作符

防止解释错误

`expr 5*2  `=>`expr 5\*2`

### 使用方括号

在将一个数学运算结果赋给某个变量时$[ operation ]

，不用担心shell会误解乘号或其他符号。shell知道它不是通配符，因为它在方括号内。

100/45 = 2

bash shell数学运算符只支持整数运算。若要进行任何实际的数学计算，这是一个巨大的限制。

### 浮点解决方案 bc

`bc`进入quit退出

浮点运算是由内建变量scale控制的。必须将这个值设置为你希望在计算结果中保留的小数

位数，否则无法得到期望的结果。

除了普通数字，bash计算器还能支持变量。

variable=$(echo "options; expression" | bc)

### 在脚本中使用bc

variable=$(echo "options; expression" | bc)

var1=$(echo "scale=4; 3.44 / 5" | bc)

bc命令能识别输入重定向

最好的办法是使用内联输入重定向，它允许你直接在命令行中重定向数据。在shell脚本中，你可以将输出赋给一个变量。

在bash

**计算器中创建的变量只在bash计算器中有效，不能在shell脚本中使用**

### 查看退出状态码

Linux提供了一个专门的变量$?来保存上个已执行命令的退出状态码。

```
0 命令成功结束
1 一般性未知错误
2 不适合的shell命令
126 命令不可执行
127 没找到命令
128 无效的退出参数
128+x 与Linux信号x相关的严重错误
130 通过Ctrl+C终止的命令
255 正常范围之外的退出状态码
```



### exit 命令

exit命令允许你在脚本结束时指定一个退出状态码。`exit 5`

退出状态码最大只能是255。shell通过模,状态码被缩减到了0～255的区间

## 12使用结构化命令

### 使用if-then 语句

```shell
if command
then
	commands
fi
```

bash shell的if语句会运行if后面的那个命令。如果该命令的退出状态码（参见第11章）是0（该命令成功运行），位于then部分的命令就会被执行。如果该命令的退出状态码是其他值， then部分的命令就不会被执行，bash shell会继续执行脚本中的下一个命令。fi语句用来表示if-then语句到此结束。

```shell
if command; then
	commands
fi
```

### if-then-else 语句

```shell
if command
then
	commands
else
	commands
fi
```

### 嵌套if/elif

```shell
if command1
then
	commands
elif command2
then
	more commands
fi
```



### test 命令

到目前为止，在if语句中看到的都是普通shell命令。你可能想问，if-then语句是否能测试

命令退出状态码之外的条件。

答案是不能

test命令提供了在if-then语句中测试不同条件的途径。如果test命令中列出的条件成立，test命令就会退出并返回退出状态码0。这样if-then语句就与其他编程语言中的if-then语句以类似的方式工作了。如果条件不成立，test命令就会退出并返回非零的退出状态码，这使得if-then语句不会再被执行。

`test condition`

如果不写test命令的condition部分，它会以非零的退出状态码退出，并执行else语句块。



可以使用test命令确定变量中是否有内容 `test $my_variable`



bash shell提供了另一种条件测试方法，无需在if-then语句中声明test命令。

### [ ]

```shell
if [ condition ]
then
	commands
fi
```

test命令可以判断三类条件：

```
1. 数值比较
2. 字符串比较
3. 文件比较
```



### 数值比较

```
n1 -eq n2 检查n1是否与n2相等
n1 -ge n2 检查n1是否大于或等于n2
n1 -gt n2 检查n1是否大于n2
n1 -le n2 检查n1是否小于或等于n2
n1 -lt n2 检查n1是否小于n2
n1 -ne n2 检查n1是否不等于n2
```

但是涉及浮点值时，数值条件测试会有一个限制

记住，bash shell只能处理整数。如果你只是要通过echo语句来显示这个结果，那没问题。但是，在基于数字的函数中就不行了，例如我们的数值测试条件。最后一行就说明我们不能在test命令中使用浮点值。

### 字符串比较

```
str1 = str2 检查str1是否和str2相同
str1 != str2 检查str1是否和str2不同
str1 < str2 检查str1是否比str2小
str1 > str2 检查str1是否比str2大
-n str1 检查str1的长度是否非0
-z str1 检查str1的长度是否为0
```

字符串顺序

1.大于号和小于号必须转义，否则shell会把它们当作重定向符号，把字符串值当作文件

名；

2.大于和小于顺序和sort命令所采用的不同。

if [ $val1 \> $val2 ]

在比较测试中，大写字母被认为是小于小写字母的。但sort命令恰好相反。当你将同样的

字符串放进文件中并用sort命令排序时，小写字母会先出现。这是由各个命令使用的排序技术

不同造成的。



比较测试中使用的是标准的ASCII顺序，根据每个字符的ASCII数值来决定排序结果。sort命令使用的是系统的本地化语言设置中定义的排序顺序。对于英语，本地化设置指定了在排序顺序中小写字母出现在大写字母前。

### 文件比较

```
-d file 检查file是否存在并是一个目录
-e file 检查file是否存在
-f file 检查file是否存在并是一个文件
-r file 检查file是否存在并可读
-s file 检查file是否存在并非空
-w file 检查file是否存在并可写
-x file 检查file是否存在并可执行
-O file 检查file是否存在并属当前用户所有
-G file 检查file是否存在并且默认组与当前用户相同
file1 -nt file2 检查file1是否比file2新
file1 -ot file2 检查file1是否比file2旧
```

### 复合条件测试

if-then语句允许你使用布尔逻辑来组合测试。有两种布尔运算符可用：

```shell
[ condition1 ] && [ condition2 ]

[ condition1 ] || [ condition2 ]
```

### if-then 的高级特性

### 使用双括号

双括号命令允许你在比较过程中使用高级数学表达式。test命令只能在比较中使用简单的算术操作。双括号命令提供了更多的数学符号，这些符号对于用过其他编程语言的程序员而言并不陌生。双括号命令的格式如下：

`(( expression ))`

expression可以是任意的数学赋值或比较表达式.

```
符 号 描 述
val++ 后增
val-- 后减
++val 先增
--val 先减
! 逻辑求反
~ 位求反
** 幂运算
<< 左位移
>> 右位移
& 位布尔和
| 位布尔或
&& 逻辑和
|| 逻辑或
```

### 使用双方括号

双方括号命令提供了针对字符串比较的高级特性。

`[[ expression ]]`

**双方括号在bash shell中工作良好。不过要小心，不是所有的shell都支持双方括号。**

### case 命令

```shell
case variable in
pattern1 | pattern2) commands1;;
pattern3) commands2;;
*) default commands;;
esac
```

## 使用更多的结构化命令

### for命令

```shell
for var in list
do
commands
done
```

只要你愿意，也可以将do语句和for语句放在同一行，但必须用分号将其同列表中的值分

开：`for var in list; do`

### 读取列表中的复杂值

`for test in I don't know if this'll work`

```shell
1.使用转义字符（反斜线）来将单引号转义；
2.使用双引号来定义用到单引号的值。
```

如果有包含空格的数据值

`for test in Nevada "New Hampshire" "New Mexico" "New York"`

### 从变量读取列表

`for state in $list`

### 从命令读取值

```shell
for state in $(cat $file)
```

如果你列出了一个名字中有空格的单词，for命令仍然会将每个单词当作单独的值。

### 更改字段分隔符

默认情况下，bash shell会将下列字符当作字段分隔符：

```
空格
制表符
换行符
```

要解决这个问题，可以在shell脚本中临时更改IFS环境变量的值来限制被bash shell当作字段分隔符的字符

`IFS=$'\n'`

将这个语句加入到脚本中，告诉bash shell在数据值中忽略空格和制表符

```
在处理代码量较大的脚本时，可能在一个地方需要修改IFS的值，然后忽略这次修改，在
脚本的其他地方继续沿用IFS的默认值。一个可参考的安全实践是在改变IFS之前保存原
来的IFS值，之后再恢复它。
这种技术可以这样实现：
IFS.OLD=$IFS
IFS=$'\n'
<在代码中使用新的IFS值>
IFS=$IFS.OLD
这就保证了在脚本的后续操作中使用的是IFS的默认值。
```

要遍历一个文件中用冒号分隔的值 `IFS=:`

如果要指定多个IFS字符，只要将它们在赋值行串起来就行。

`IFS=$'\n':;"`

### 用通配符读取目录

可以用for命令来自动遍历目录中的文件。进行此操作时，必须在文件名或路径名中使用通配符。它会强制shell使用文件扩展匹配。文件扩展匹配是生成匹配指定通配符的文件名或路径名的过程。

`if [ -d "$file" ]`

在Linux中，**目录名和文件名中包含空格当然是合法的**。要适应这种情况，应该将$file变

量用双引号圈起来。如果不这么做，遇到含有空格的目录名或文件名时就会有错误产生。

### C 语言的for 命令

```shell
for (( variable assignment ; condition ; iteration process ))
```

```
注意，有些部分并没有遵循bash shell标准的for命令：
1.变量赋值可以有空格；
2.条件中的变量不以美元符开头；
3.迭代过程的算式未用expr命令格式。
```

```shell
#!/bin/bash
# testing the C-style for loop
for (( i=1; i <= 10; i++ ))
do
	echo "The next number is $i"
done
```

### 使用多个变量

C语言风格的for命令也允许为迭代使用多个变量。循环会单独处理每个变量，你可以为每个变量定义不同的迭代过程。尽管可以使用多个变量，但你只能在for循环中定义一种条件。

### while 命令

```shell
while test command
do
	other commands
done
```

### 使用多个测试命令

while命令允许你在while语句行定义多个测试命令。**只有最后一个测试命令**的退出状态码

会被用来决定什么时候结束循环。

### until 命令

until命令要求你指定一个通常返回非零退出状态码的测试命令。

```shel
until test commands
do
	other commands
done
```

和while命令类似，你可以在until命令语句中放入多个测试命令。只有最后一个命令的退

出状态码决定了bash shell是否执行已定义的other commands

### 嵌套循环

循环语句可以在循环内使用任意类型的命令，包括其他循环命令。

### 循环处理文件数据

```shell
#!/bin/bash
# changing the IFS value
IFS.OLD=$IFS
IFS=$'\n'
for entry in $(cat /etc/passwd)
do
	echo "Values in $entry –"
	IFS=:
	for value in $entry
	do
		echo " $value"
	done
done
$
```

### 控制循环

```
break命令
continue命令
```

### break 命令

1. 跳出单个循环

在shell执行break命令时，它会尝试跳出当前正在执行的循环。

2. 跳出内部循环

在处理多个循环时，break命令会自动终止你所在的最内层的循环。

3. 跳出外部循环

`break n`

其中n指定了要跳出的循环层级。默认情况下，n为1，表明跳出的是当前的循环。如果你将n设为2，break命令就会停止下一级的外部循环。

### continue 命令

`continue n`

### 处理循环的输出

```shell
for file in /home/rich/*
do
if [ -d "$file" ]
then
	echo "$file is a directory"
elif
	echo "$file is a file"
fi
done > output.txt
```

### 查找可执行文件

```shell
#!/bin/bash
# finding files in the PATH
IFS=:
for folder in $PATH
do
	echo "$folder:"
	for file in $folder/*
	do
		if [ -x $file ]
		then
		echo " $file"
		fi
	done
done
```



### 创建多个用户账户

`while IFS=’,’ read –r userid name`

read命令会自动读取.csv文本文件的下一行内容，所以不需要专门再写一个循环来处理。当read命令返回FALSE时（也就是读取完整个文件时），while命令就会退出。妙极了！

```shell
$ cat test26
#!/bin/bash
# process new user accounts
input="users.csv"
while IFS=',' read -r userid name
do
	echo "adding $userid"
	useradd -c "$name" -m $userid
done < "$input"
```

## 14处理用户输入

```shell
#!/bin/bash
# using one command line parameter
#
factorial=1
for (( number = 1; number <= $1 ; number++ ))
do
factorial=$[ $factorial * $number ]
done
echo The factorial of $1 is $factorial
```

$ >= 10 ${10}

basename命令会返回不包含路径的脚本名

```shell
#!/bin/bash
# Using basename with the $0 parameter
#
name=$(basename $0)
echo
echo The script name is: $name
#
```

### 测试参数

当脚本认为参数变量中会有数据而实际上并没有时，脚本很有可能会产生错误消息。这种写

脚本的方法并不可取。在使用参数前一定要检查其中是否存在数据。

```shell
#!/bin/bash
# testing parameters before use
#
if [ -n "$1" ]
then
echo Hello $1, glad to meet you.
else
echo "Sorry, you did not identify yourself. "
fi
```



### 特殊参数变量

### 参数统计

特殊变量`$#`含有脚本运行时携带的命令行参数的个数

或许`$#`变量含有参数的总数，那么变量`${$#}`代表最后一个参数，但是并不能在画括号中使用美元符号

`params=$#`

`${!#}`

### 抓取所有的数据

`$*`和`$@`变量可以用来轻松访问所有的参数。

`$*`变量会将命令行上提供的所有参数当作一个单词保存。这个单词包含了命令行中出现每一个参数值。基本上`$*`变量会将这些参数视为一个整体，而不是多个个体。

$@变量会将命令行上提供的所有参数当作同一字符串中的多个独立的单词。这样你就能够遍历所有的参数值，得到每个参数。这通常通过for命令完成。



### 移动变量

在使用shift命令时，默认情况下它会将每个参数变量向左移动一个位置。所以，变量$3的值会移到$2中，变量$2的值会移到$1中，而变量$1的值则会被删除（注意，变量$0的值，也就是程序名，不会改变）。

```shell
#!/bin/bash
# demonstrating the shift command
echo
count=1
while [ -n "$1" ]
do
echo "Parameter #$count = $1"
count=$[ $count + 1 ]
shift
done
```

`shift n  ` 一次移动n个位置

### 处理选项

### 查找选项

1. 处理简单选项

```shell
#!/bin/bash
# extracting command line options as parameters
#
echo
while [ -n "$1" ]
do
case "$1" in
-a) echo "Found the -a option" ;;
-b) echo "Found the -b option" ;;
-c) echo "Found the -c option" ;;
*) echo "$1 is not an option" ;;
esac
shift
done
```

2. 分离参数和选项

你会经常遇到想在shell脚本中同时使用选项和参数的情况。Linux中处理这个问题的标准方式是用特殊字符来将二者分开，该字符会告诉脚本何时选项结束以及普通参数何时开始。

对Linux来说，这个特殊字符是双破折线（--）。shell会用双破折线来表明选项列表结束。在双破折线之后，脚本就可以放心地将剩下的命令行参数当作参数，而不是选项来处理了。

```shell
#!/bin/bash
# extracting options and parameters
echo
while [ -n "$1" ]
do
case "$1" in
-a) echo "Found the -a option" ;;
-b) echo "Found the -b option";;
-c) echo "Found the -c option" ;;
--) shift
break ;;
*) echo "$1 is not an option";;
esac
shift
done
#
count=1
for param in $@
do
echo "Parameter #$count: $param"
count=$[ $count + 1 ]
done
```

3. 处理带值的选项

```shell
#!/bin/bash
# extracting command line options and values
echo
while [ -n "$1" ]
do
case "$1" in
-a) echo "Found the -a option";;
-b) param="$2"
echo "Found the -b option, with parameter value $param"
shift ;;
-c) echo "Found the -c option";;
--) shift
break ;;
*) echo "$1 is not an option";;
esac
shift
done
#
count=1
for param in "$@"
do
echo "Parameter #$count: $param"
count=$[ $count + 1 ]
done
```

### 使用getopt 命令

1. 命令的格式

```  shell
getopt optstring parameters
```

在optstring中列出你要在脚本中用到的每个命令行选项字母。然后，在每个需要参数值的选项字母后加一个冒号。getopt命令会基于你定义的optstring解析提供的参数。

`getopt ab:cd -a -b test1 -cd test2 test3`

optstring定义了四个有效选项字母：a、b、c和d。冒号（:）被放在了字母b后面，因为选项需要一个参数值。当getopt命令运行时，它会检查提供的参数列表（-a -b test1 -cd

test2 test3），并基于提供的optstring进行解析。注意，它会自动将-cd选项分成两个单独

的选项，并插入双破折线来分隔行中的额外参数。如果指定了一个不在optstring中的选项，默认情况下，getopt命令会产生一条错误消息。如果想忽略这条错误消息，可以在命令后加-q选项。

`getopt -q ab:cd -a -b test1 -cde test2 test3`

### set

The `set` command (when not setting options) sets the positional parameters eg

```bsh
$ set a b c
$ echo $1
a
$ echo $2
b
$ echo $3
c
```

The `--` is the standard "don't treat anything following this as an option"

The `"$@"` are all the existing position paramters.

So the sequence

```bsh
set -- haproxy "$@"
```

Will put the word `haproxy` in front of `$1` `$2` etc.

### 在脚本中使用getopt

```shell
set -- $(getopt -q ab:cd "$@")
```



getopt命令并不擅长处理带空格和引号的参数值。它会将空格当作参数分隔符，而不是根

据双引号将二者当作一个参数。幸而还有另外一个办法能解决这个问题。

### 使用更高级的getopts

与getopt不同，前者将命令行上选项和参数处理后只生成一个输出，而getopts命令能够

和已有的shell参数变量配合默契。

`getopts optstring variable`

optstring值类似于getopt命令中的那个。有效的选项字母都会列在optstring中，如果选项字母要求有个参数值，就加一个冒号。要去掉错误消息的话，可以在optstring之前加一个冒号。getopts命令将当前参数保存在命令行中定义的variable中。

getopts命令会用到两个环境变量。如果选项需要跟一个参数值，OPTARG环境变量就会保存这个值。OPTIND环境变量保存了参数列表中getopts正在处理的参数位置。这样你就能在处理完选项之后继续处理其他命令行参数了。

```shell
#!/bin/bash
# simple demonstration of the getopts command
#
echo
while getopts :ab:c opt
do
case "$opt" in
a) echo "Found the -a option" ;;
b) echo "Found the -b option, with value $OPTARG";;
c) echo "Found the -c option" ;;
*) echo "Unknown option: $opt";;
esac
done
```

while语句定义了getopts命令，指明了要查找哪些命令行选项，以及每次迭代中存储它们的变量名（opt）。

你会注意到在本例中case语句的用法有些不同。getopts命令解析命令行选项时会移除开头的单破折线，所以在case定义中不用单破折线。

getopts命令有几个好用的功能。对新手来说，可以在参数值中包含空格。

另一个好用的功能是将选项字母和参数值放在一起使用，而不用加空格。

`./test19.sh -abtest1`

getopts命令知道何时停止处理选项，并将参数留给你处理。在getopts处理每个选项时，它会将OPTIND环境变量值增一。在getopts完成处理时，你可以使用shift命令和OPTIND值来移动参数。

```shell
#!/bin/bash
# Processing options & parameters with getopts
#
echo
while getopts :ab:cd opt
do
case "$opt" in
a) echo "Found the -a option" ;;
b) echo "Found the -b option, with value $OPTARG" ;;
c) echo "Found the -c option" ;;
d) echo "Found the -d option" ;;
*) echo "Unknown option: $opt" ;;
esac
done
#
shift $[ $OPTIND - 1 ]
#
echo
count=1
for param in "$@"
do
echo "Parameter $count: $param"
count=$[ $count + 1 ]
done
#
```

`$[ $OPTIND - 1 ]`是`$OPTIND - 1`的值。

### 将选项标准化

```shell
选 项 描 述
-a 显示所有对象
-c 生成一个计数
-d 指定一个目录
-e 扩展一个对象
-f 指定读入数据的文件
-h 显示命令的帮助信息
-i 忽略文本大小写
-l 产生输出的长格式版本
-n 使用非交互模式（批处理）
-o 将所有输出重定向到的指定的输出文件
-q 以安静模式运行
-r 递归地处理目录和文件
-s 以安静模式运行
-v 生成详细输出
-x 排除某个对象
-y 对所有问题回答yes
```

### 获得用户输入

尽管命令行选项和参数是从脚本用户处获得输入的一种重要方式，但有时脚本的交互性还需要更强一些。比如你想要在脚本运行时问个问题，并等待运行脚本的人来回答。bash shell为此提供了read命令。

### 基本的读取

read命令从标准输入（键盘）或另一个文件描述符中接受输入。在收到输入后，read命令

会将数据放进一个变量。下面是read命令的最简单用法。

```shell
#!/bin/bash
# testing the read command
#
echo -n "Enter your name: "
read name
echo "Hello $name, welcome to my program. "
```

相当简单。注意，生成提示的echo命令使用了-n选项。该选项不会在字符串末尾输出换行符，允许脚本用户紧跟其后输入数据，而不是下一行。这让脚本看起来更像表单。实际上，read命令包含了-p选项，允许你直接在read命令行指定提示符。

```shell
#!/bin/bash
# testing the read -p option
#
read -p "Please enter your age: " age
days=$[ $age * 365 ]
echo "That makes you over $days days old! "
#
```

指定多个变量,输入的每个数据值都会分配给变量列表中的下一个变量。如果变量数量不够，剩下的数据就全部分配给最后一个变量。

也可以在read命令行中不指定变量。如果是这样，read命令会将它收到的任何数据都放进特殊环境变量`REPLY`中。

### 超时

使用read命令时要当心。脚本很可能会一直苦等着脚本用户的输入。如果不管是否有数据输入，脚本都必须继续执行，你可以用-t选项来指定一个计时器。-t选项指定了read命令等待输入的秒数。当计时器过期后，read命令会返回一个非零退出状态码。可以使用如if-then语句或while循环这种标准的结构化语句来理清所发生的具体情况。

也可以不对输入过程计时，而是让read命令来统计输入的字符数。当输入的字符达到预设的字符数时，就自动退出，将输入的数据赋给变量。

```shell
#!/bin/bash
# getting just one character of input
#
read -n1 -p "Do you want to continue [Y/N]? " answer
case $answer in
Y | y) echo
echo "fine, continue on…";;
N | n) echo
echo OK, goodbye
exit;;
esac
echo "This is the end of the script"
```

本例中将-n选项和值1一起使用，告诉read命令在接受单个字符后退出。只要按下单个字符回答后，read命令就会接受输入并将它传给变量，无需按回车键。

### 隐藏方式读取

-s选项可以避免在read命令中输入的数据出现在显示器上（实际上，数据会被显示，只是read命令会将文本颜色设成跟背景色一样）。这里有个在脚本中使用-s选项的例子。

```shell
#!/bin/bash
# hiding input data from the monitor
#
read -s -p "Enter your password: " pass
echo
echo "Is your password really $pass? "
```

### 从文件中读取

```shell
#!/bin/bash
# reading data from a file
#
count=1
cat test | while read line
do
echo "Line $count: $line"
count=$[ $count + 1]
done
echo "Finished processing the file"
```

