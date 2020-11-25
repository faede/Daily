### ls 

第一个字母 目录(d) 、文件(-)、字符型文件(c)、块设备(b)



touch test_one

创建新的空文件,更改文件的修改时间（不需要改变内容）

### 以root权限执行上一条命令

sudo !!

### sudo

```
sudo -V
sudo -h
sudo -l
sudo -v
sudo -k
sudo -s
sudo -H
sudo [ -b ] [ -p prompt ] [ -u username/#uid] -s
sudo command
```

\- -V 显示版本编号
\- -h 会显示版本编号及指令的使用方式说明
\- -l 显示出自己（执行 sudo 的使用者）的权限
\- -v 因为 sudo 在第一次执行时或是在 N 分钟内没有执行（N 预设为五）会问密码，这个参数是重新做一次确认，如果超过 N 分钟，也会问密码
\- -k 将会强迫使用者在下一次执行 sudo 时问密码（不论有没有超过 N 分钟）
\- -b 将要执行的指令放在背景执行
\- -p prompt 可以更改问密码的提示语，其中 %u 会代换为使用者的帐号名称， %h 会显示主机名称
\- -u username/#uid 不加此参数，代表要以 root 的身份执行指令，而加了此参数，可以以 username 的身份执行指令（#uid 为该 username 的使用者号码）
\- -s 执行环境变数中的 SHELL 所指定的 shell ，或是 /etc/passwd 里所指定的 shell
\- -H 将环境变数中的 HOME （家目录）指定为要变更身份的使用者家目录（如不加 -u 参数就是系统管理者 root ）
\- command 要以系统管理者身份（或以 -u 更改为其他人）执行的指令

```
指定用户执行命令 ： # sudo -u userb ls -l

显示sudo设置 ： # sudo -L

以root权限执行上一条命令 ： # sudo !!

以特定用户身份进行编辑文本 ： $ sudo -u uggc vi ~www/index.html

列出目前的权限 ：# sudo -l
列出 sudo 的版本资讯 ： # sudo -V
```



### 链接文件

符号链接，是一个文件，指向存放在虚拟目录结构中某个地方的另一个文件。两个通过符号链接在一起的文件，彼此内容并不相同。

ln -s data_file sl_data_file

sl指向data

inode不同。

硬链接

创建独立的虚拟文件，其中包含了原始文件的信息和位置，本质上是同一个文件，引用硬链接文件等于引用了源文件。

inode相同。

只能对处于同一存储媒体的文件创建硬链接，否则只能用符号链接。



### mv

移动或重命名



### rm 

建议加-i

rm -i fall

-f强制删除



mkdir

### 创建目录

mkdir -p new_dir/sub_dir/under_dir

-p参数会自动创建缺失的目录。



rmdir

默认只接受空目录

或者 rm -ri My_Dir



### tree

展示目录树



### 3.8查看文件内容

### file My_file

查看文件类型，编码，符号链接，二进制文件需要何种库



### cat test1

显示

-n 加上行号

-b 只给有文本的地方加行号

-T 不显示制表符(^I )替换所有制表符



### more

显示一页之后就停下来



### less

加强more （less is more）

可以上下键翻页等



### tail

展示尾部文件，默认10行

tail -n 2 log_file

只展示最后两行



### head

前十行

head -5 log_file



## 更多的bash shell命令

### 4.1监测程序

### ps

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



### grep [options] pattern [file]

`grep -rn str *`

**递归**查找当前文件夹下所有文件带"str"并**显示行号**

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



### 归档数据

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

## 15呈现数据

### 标准文件描述符

文件描述符是一个非负整数，可以唯一标识会话中打开

的文件。每个进程一次最多可以有九个文件描述符。出于特殊目的，bash shell保留了前三个文

件描述符（0、1和2）

```shell
文件描述符 缩 写 描 述
0 STDIN 标准输入
1 STDOUT 标准输出
2 STDERR 标准错误
```

1. STDIN

STDIN文件描述符代表shell的标准输入。对终端界面来说，标准输入是键盘。shell从STDIN文件描述符对应的键盘获得输入，在用户输入时处理每个字符。

在使用输入重定向符号（<）时，Linux会用重定向指定的文件来替换标准输入文件描述符。它会读取文件并提取数据，就如同它是键盘上键入的。

2. STDOUT

STDOUT文件描述符代表shell的标准输出

3. STDER

shell通过特殊的STDERR文件描述符来处理错误消息。STDERR文件描述符代表shell的标准错误输出。shell或shell中运行的程序和脚本出错时生成的错误消息都会发送到这个位置。

### 重定向错误

1. 只重定向错误

```shell
ls -al badfile 2> test4
```

该值必须紧紧地放在重定向符号前，否则不会工作。

2. 重定向错误和数据

```shell
ls -al test test2 test3 badtest 2> test6 1> test7
```

shell利用1>符号将ls命令的正常输出重定向到了test7文件，而这些输出本该是进入STDOUT的。所有本该输出到STDERR的错误消息通过2>符号被重定向到了test6文件。，如果愿意，也可以将STDERR和STDOUT的输出重定向到同一个输出文件。为此bash shell提供了特殊的重定向符号`&>`。

### 在脚本中重定向输出

### 临时重定向

如果有意在脚本中生成错误消息，可以将单独的一行输出重定向到STDERR。你所需要做的是使用输出重定向符来将输出信息重定向到STDERR文件描述符。在重定向到文件描述符时，你必须在文件描述符数字之前加一个&

```shell
#!/bin/bash
# testing STDERR messages
echo "This is an error" >&2
echo "This is normal output"
```



```shell
$ ./test8 2> test9
This is normal output
$ cat test9
This is an error
$
```

### 永久重定向

如果脚本中有大量数据需要重定向，那重定向每个echo语句就会很烦琐。取而代之，你可以用`exec`命令告诉shell在脚本执行期间重定向某个特定文件描述符。

```shell
#!/bin/bash
# redirecting all output to a file
exec 1>testout
echo "This is a test of redirecting all output"
echo "from a script to another file."
echo "without having to redirect every individual line"
```

exec命令会启动一个新shell并将STDOUT文件描述符重定向到文件。脚本中发给STDOUT的所有输出会被重定向到文件。



`exec 2>testerror`

### 在脚本中重定向输入

`exec 0< testfile`

### 创建自己的重定向

在脚本中重定向输入和输出时，并不局限于这3个默认的文件描述符。我曾提到过，在shell中最多可以有9个打开的文件描述符。其他6个从3~8的文件描述符均可用作输入或输出重定向。你可以将这些文件描述符中的任意一个分配给文件，然后在脚本中使用它们。

创建输出文件描述符

可以用exec命令来给输出分配文件描述符。和标准的文件描述符一样，一旦将另一个文件描述符分配给一个文件，这个重定向就会一直有效，直到你重新分配。

```shell
#!/bin/bash
# using an alternative file descriptor
exec 3>test13out
echo "This should display on the monitor"
echo "and this should be stored in the file" >&3
```

### 重定向文件描述符

现在介绍怎么恢复已重定向的文件描述符。你可以分配另外一个文件描述符给标准文件描述符，反之亦然。

```shell
#!/bin/bash
# storing STDOUT, then coming back to it
exec 3>&1
exec 1>test14out
echo "This should store in the output file"
echo "along with this line."
exec 1>&3
echo "Now things should be back to normal"


$
$ ./test14
Now things should be back to normal
$ cat test14out
This should store in the output file
along with this line.
$
```

这个例子有点叫人抓狂，来一段一段地看。首先，脚本将文件描述符3重定向到文件描述符1的当前位置，也就是STDOUT。这意味着任何发送给文件描述符3的输出都将出现在显示器上。

第二个exec命令将STDOUT重定向到文件，shell现在会将发送给STDOUT的输出直接重定向到输出文件中。但是，文件描述符3仍然指向STDOUT原来的位置，也就是显示器。如果此时将输出数据发送给文件描述符3，它仍然会出现在显示器上，尽管STDOUT已经被重定向了。

在向STDOUT（现在指向一个文件）发送一些输出之后，脚本将STDOUT重定向到文件描述符3的当前位置（现在仍然是显示器）。这意味着现在STDOUT又指向了它原来的位置：显示器。



###  创建输入文件描述符

可以用和重定向输出文件描述符同样的办法重定向输入文件描述符。在重定向到文件之前，先将STDIN文件描述符保存到另外一个文件描述符，然后在读取完文件之后再将STDIN恢复到它原来的位置。

```shell
#!/bin/bash
# redirecting input file descriptors
exec 6<&0
exec 0< testfile
count=1
while read line
do
echo "Line #$count: $line"
count=$[ $count + 1 ]
done
exec 0<&6
read -p "Are you done now? " answer
case $answer in
Y|y) echo "Goodbye";;
N|n) echo "Sorry, this is the end.";;
esac
```

### 创建读写文件描述符

也可以打开单个文件描述符来作为输入和输出,由于你是对同一个文件进行数据读写，shell会维护一个

内部指针，指明在文件中的当前位置。任何读或写都会从文件指针上次的位置开始

```shell
#!/bin/bash
# testing input/output file descriptor
exec 3<> testfile
read line <&3
echo "Read: $line"
echo "This is a test line" >&3
```



当脚本向文件中写入数据时，它会从文件指针所处的位置开始。read命令读取了第一行数据，所以它使得文件指针指向了第二行数据的第一个字符。在echo语句将数据输出到文件时，它会将数据放在文件指针的当前位置，覆盖了该位置的已有数据。

### 关闭文件描述符

`exec 3>&-`

一旦关闭了文件描述符，就不能在脚本中向它写入任何数据，否则shell会生成错误消息。在关闭文件描述符时还要注意另一件事。如果随后你在脚本中打开了同一个输出文件，shell会用一个新文件来替换已有文件。这意味着如果你输出数据，它就会覆盖已有文件。考虑下面这个问题的例子。

```shell
$ cat test17
#!/bin/bash
# testing closing file descriptors
exec 3> test17file
echo "This is a test line of data" >&3
exec 3>&-
cat test17file
exec 3> test17file
echo "This'll be bad" >&3
$ ./test17
This is a test line of data
$ cat test17file
This'll be bad
$
```

在向test17file文件发送一个数据字符串并关闭该文件描述符之后，脚本用了cat命令来显示文件的内容。到目前为止，一切都还好。下一步，脚本重新打开了该输出文件并向它发送了另一个数据字符串。当显示该输出文件的内容时，你所能看到的只有第二个数据字符串。shell覆盖了原来的输出文件。

### 列出打开的文件描述符

lsof命令会列出整个Linux系统打开的所有文件描述符。这是个有争议的功能，因为它会向非系统管理员用户提供Linux系统的信息。鉴于此，许多Linux系统隐藏了该命令，这样用户就不会一不小心就发现了。

在很多Linux系统中（如Fedora），lsof命令位于/usr/sbin目录。要想以普通用户账户来运行它，必须通过全路径名来引用：`$ /usr/sbin/lsof`

有大量的命令行选项和参数可以用来帮助过滤lsof的输出。最常用的有-p和-d，前者允许指定进程ID（PID），后者允许指定要显示的文件描述符编号。

要想知道进程的当前PID，可以用特殊环境变量$$（shell会将它设为当前PID）。-a选项用来对其他两个选项的结果执行布尔AND运算，这会产生如下输出。

```shell
$ /usr/sbin/lsof -a -p $$ -d 0,1,2
COMMAND PID USER FD TYPE DEVICE SIZE NODE NAME
bash 3344 rich 0u CHR 136,0 2 /dev/pts/0
bash 3344 rich 1u CHR 136,0 2 /dev/pts/0
bash 3344 rich 2u CHR 136,0 2 /dev/pts/0
$
```

```
列 描 述
COMMAND 正在运行的命令名的前9个字符
PID 进程的PID
USER 进程属主的登录名
FD 文件描述符号以及访问类型（r代表读，w代表写，u代表读写）
TYPE 文件的类型（CHR代表字符型，BLK代表块型，DIR代表目录，REG代表常规文件）
DEVICE 设备的设备号（主设备号和从设备号）
SIZE 如果有的话，表示文件的大小
NODE 本地文件的节点号
NAME 文件名
```

## 阻止命令输出

将STDERR重定向到一个叫作null文件的特殊文件。null文件跟它的名字很像，文件里什么都没有。shell输出到null文件的任何数据都不会保存，全部都被丢掉了。

```shell
ls -al > /dev/null
```

### 创建临时文件

mktemp命令可以在/tmp目录中创建一个唯一的临时文件。shell会创建这个文件，但不用默认的umask值（参见第7章）。它会将文件的读和写权限分配给文件的属主，并将你设成文件的属主。一旦创建了文件，你就在脚本中有了完整的读写权限，但其他人没法访问它（当然，root用户除外）。

### 创建本地临时文件

要用mktemp命令在本地目录中创建一个临时文件，你只要指定一个文件名模板就行了。模板可以包含任意文本文件名，在文件名末尾加上6个X就行了。`mktemp testing.XXXXXX`

mktemp命令会用6个字符码替换这6个X，从而保证文件名在目录中是唯一的。你可以创建多个临时文件，它可以保证每个文件都是唯一的。

在脚本中使用mktemp命令时，可能要将文件名保存到变量中，这样就能在后面的脚本中引用了。



```shell
#!/bin/bash
# creating and using a temp file
tempfile=$(mktemp test19.XXXXXX)
exec 3>$tempfile
echo "This script writes to temp file $tempfile"
echo "This is the first line" >&3
echo "This is the second line." >&3
echo "This is the last line." >&3
exec 3>&-
echo "Done creating temp file. The contents are:"
cat $tempfile
rm -f $tempfile 2> /dev/null
```

### 在tmp 目录创建临时文件

-t选项会强制mktemp命令来在系统的临时目录来创建该文件。在用这个特性时，mktemp命令会返回用来创建临时文件的全路径，而不是只有文件名。` mktemp -t test.XXXXXX`

由于mktemp命令返回了全路径名，你可以在Linux系统上的任何目录下引用该临时文件，不管临时目录在哪里。

### 创建临时目录

-d选项告诉mktemp命令来创建一个临时目录而不是临时文件。

```shell
#!/bin/bash
# using a temporary directory
tempdir=$(mktemp -d dir.XXXXXX)
cd $tempdir
tempfile1=$(mktemp temp.XXXXXX)
tempfile2=$(mktemp temp.XXXXXX)
exec 7> $tempfile1
exec 8> $tempfile2
echo "Sending data to directory $tempdir"
echo "This is a test line of data for $tempfile1" >&7
echo "This is a test line of data for $tempfile2" >&8
```

### 记录消息

将输出同时发送到显示器和日志文件，这种做法有时候能够派上用场。你不用将输出重定向两次，只要用特殊的tee命令就行。

tee命令相当于管道的一个T型接头。它将从STDIN过来的数据同时发往两处。一处是STDOUT，另一处是tee命令行所指定的文件名：

`tee filename`

由于tee会重定向来自STDIN的数据，你可以用它配合管道命令来重定向命令输出。

```shell
date | tee testfile
```

如果你想将数据追加到文件中，必须用-a选项。

```shell
date | tee -a testfile
```

### 实例

```shell
#!/bin/bash
# read file and create INSERT statements for MySQL
outfile='members.sql'
IFS=','
while read lname fname address city state zip
do
cat >> $outfile << EOF
INSERT INTO members (lname,fname,address,city,state,zip) VALUES
('$lname', '$fname', '$address', '$city', '$state', '$zip');
EOF
done < ${1}
```

done < ${1}

当运行程序test23时，$1代表第一个命令行参数。它指明了待读取数据的文件。read语句会使用IFS字符解析读入的文本，我们在这里将IFS指定为逗号。

cat >> $outfile << EOF

这条语句中包含一个输出追加重定向（双大于号）和一个输入追加重定向（双小于号）。输出重定向将cat命令的输出追加到由$outfile变量指定的文件中。

## 16控制脚本

### 处理信号

### 重温Linux 信号

常见信号：

```shell
信 号 值 描 述
1 SIGHUP 挂起进程
2 SIGINT 终止进程
3 SIGQUIT 停止进程
9 SIGKILL 无条件终止进程
15 SIGTERM 尽可能终止进程
17 SIGSTOP 无条件停止进程，但不是终止进程
18 SIGTSTP 停止或暂停进程，但不终止进程
19 SIGCONT 继续运行停止的进程
```

默认情况下，bash shell会忽略收到的任何SIGQUIT (3)和SIGTERM (5)信号（正因为这样，交互式shell才不会被意外终止）。但是bash shell会处理收到的SIGHUP (1)和SIGINT (2)信号。

shell会将这些信号传给shell脚本程序来处理。而shell脚本的默认行为是忽略这些信号。它们可能会不利于脚本的运行。要避免这种情况，你可以脚本中加入识别信号的代码，并执行命令来处理信号。

### 生成信号

bash shell允许用键盘上的组合键生成两种基本的Linux信号。这个特性在需要停止或暂停失控程序时非常方便。

1. 中断进程

Ctrl+C组合键会生成SIGINT信号，并将其发送给当前在shell中运行的所有进程。可以运行一条需要很长时间才能完成的命令，然后按下Ctrl+C组合键来测试它。

2. 暂停进程

尽管有时这可能会比较危险（比如，脚本打开了一个关键的系统文件的文件锁），但通常它可以在不终止进程的情况下使你能够深入脚本内部一窥究竟。

Ctrl+Z组合键会生成一个SIGTSTP信号，停止shell中运行的任何进程。停止（stopping）进程跟终止（terminating）进程不同：停止进程会让程序继续保留在内存中，并能从上次停止的位置继续运行。

方括号中的数字是shell分配的作业号（job number）。shell将shell中运行的每个进程称为作业，并为每个作业分配唯一的作业号。它会给第一个作业分配作业号1，第二个作业号2，以此类推。

`ps -l`

在S列中（进程状态），ps命令将已停止作业的状态为显示为T。这说明命令要么被跟踪，要么被停止了。

如果在有已停止作业存在的情况下，你仍旧想退出shell，只要再输入一遍exit命令就行了。shell会退出，终止已停止作业。或者，既然你已经知道了已停止作业的PID，就可以用kill命令来发送一个SIGKILL信号来终止它。

### 捕获信号

也可以不忽略信号，在信号出现时捕获它们并执行其他命令。trap命令允许你来指定shell脚本要监看并从shell中拦截的Linux信号。如果脚本收到了trap命令中列出的信号，该信号不再由shell处理，而是交由本地处理。

```shell
trap commands signals
```

```shell
#!/bin/bash
# Testing signal trapping
#
trap "echo ' Sorry! I have trapped Ctrl-C'" SIGINT
#
echo This is a test script
#
count=1
while [ $count -le 10 ]
do
echo "Loop #$count"
sleep 1
count=$[ $count + 1 ]
done
#
echo "This is the end of the test script"
#
```

### 捕获脚本退出

要捕获shell脚本的退出，只要在trap命令后加上EXIT信号就行。

```shell
#!/bin/bash
# Trapping the script exit
#
trap "echo Goodbye..." EXIT
#
count=1
while [ $count -le 5 ]
do
echo "Loop #$count"
sleep 1
count=$[ $count + 1 ]
done
#
```

当脚本运行到正常的退出位置时，捕获就被触发了，shell会执行在trap命令行指定的命令。如果提前退出脚本，同样能够捕获到EXIT。

### 修改或移除捕获

```shell
#!/bin/bash
# Modifying a set trap
#
trap "echo ' Sorry... Ctrl-C is trapped.'" SIGINT
#
count=1
while [ $count -le 5 ]
do
echo "Loop #$count"
sleep 1
count=$[ $count + 1 ]
done
#
trap "echo ' I modified the trap!'" SIGINT
#
count=1
while [ $count -le 5 ]
do
echo "Second Loop #$count"
sleep 1
count=$[ $count + 1 ]
done
#
```



也可以删除已设置好的捕获。只需要在trap命令与希望恢复默认行为的信号列表之间加上两个破折号就行了。

```shell
trap -- SIGINT
```

也可以在trap命令后使用单破折号来恢复信号的默认行为。单破折号和双破折号都可以正常发挥作用。

### 后台运行脚本

以后台模式运行shell脚本非常简单。只要在命令后加个&符就行了。

当&符放到命令后时，它会将命令和bash shell分离开来，将命令作为系统中的一个独立的后台进程运行。

方括号中的数字是shell分配给后台进程的作业号。下一个数是Linux系统分配给进程的进程ID（PID）。Linux系统上运行的每个进程都必须有一个唯一的PID。

最好是将后台运行的脚本的STDOUT和STDERR进行重定向，避免杂乱的输出。

### 运行多个后台作业

都加&

在终端会话中使用后台进程时一定要小心。注意，在ps命令的输出中，每一个后台进程都和终端会话（pts/0）终端联系在一起。如果终端会话退出，那么后台进程也会随之退出。

### 在非控制台下运行脚本

nohup命令运行了另外一个命令来阻断所有发送给该进程的SIGHUP信号。这会在退出终端会话时阻止进程退出。

`nohup ./test1.sh &`

由于nohup命令会解除终端与进程的关联，进程也就不再同STDOUT和STDERR联系在一起。为了保存该命令产生的输出，nohup命令会自动将STDOUT和STDERR的消息重定向到一个名为nohup.out的文件中。

如果使用nohup运行了另一个命令，该命令的输出会被追加到已有的nohup.out文件中。当运行位于同一个目录中的多个命令时一定要当心，因为所有的输出都会被发送到同一个nohup.out文件中，结果会让人摸不清头脑。

### 作业控制

启动、停止、终止以及恢复作业的这些功能统称为作业控制。通过作业控制，就能完全控制shell环境中所有进程的运行方式了。

### 查看作业

作业控制中的关键命令是jobs命令。jobs命令允许查看shell当前正在处理的作业。

```shell
#!/bin/bash
# Test job control
#
echo "Script Process ID: $$"   #$$变量来显示Linux系统分配给该脚本的PID
#
count=1
while [ $count -le 10 ]
do
echo "Loop #$count"   
sleep 10
count=$[ $count + 1 ]
done
#
echo "End of script..."
#
```

jobs命令可以查看分配给shell的作业。jobs命令会显示已停止/运行中的作业，以及它们的作业号和作业中使用的命令。要想查看作业的PID，可以在jobs命令中加入-l选项（小写的L）。

```shell
参 数 描 述
-l 列出进程的PID以及作业号
-n 只列出上次shell发出的通知后改变了状态的作业
-p 只列出作业的PID
-r 只列出运行中的作业
-s 只列出已停止的作业
```

你可能注意到了jobs命令输出中的加号和减号。带加号的作业会被当做默认作业。在使用作业控制命令时，如果未在命令行指定任何作业号，该作业会被当成作业控制命令的操作对象。当前的默认作业完成处理后，带减号的作业成为下一个默认作业。任何时候都只有一个带加号的作业和一个带减号的作业，不管shell中有多少个正在运行的作业。

### 重启停止的作业

要以后台模式重启一个作业，可用bg命令加上作业号。

作业是默认作业（从加号可以看出），只需要使用bg命令就可以将其以后台模式重启。注意，当作业被转入后台模式时，并不会列出其PID。

要以前台模式重启作业，可用带有作业号的fg命令。

### 调整谦让度

在多任务操作系统中（Linux就是），内核负责将CPU时间分配给系统上运行的每个进程。调度优先级（scheduling priority）是内核分配给进程的CPU时间（相对于其他进程）。在Linux系统中，由shell启动的所有进程的调度优先级默认都是相同的。

调度优先级是个整数值，从-20（最高优先级）到+19（最低优先级）。默认情况下，bash shell以优先级0来启动所有进程。

### nice 命令

nice命令允许你设置命令启动时的调度优先级。要让命令以更低的优先级运行，只要用nice的-n命令行来指定新的优先级级别。

nice命令允许你设置命令启动时的调度优先级。要让命令以更低的优先级运行，只要用nice的-n命令行来指定新的优先级级别。

nice命令阻止普通系统用户来提高命令的优先级。注意，指定的作业的确运行了，但是试图使用nice命令提高其优先级的操作却失败了。nice命令的-n选项并不是必须的，只需要在破折号后面跟上优先级就行了。

### renice 命令

有时你想改变系统上已运行命令的优先级。这正是renice命令可以做到的。它允许你指定运行进程的PID来改变它的优先级。

```shell
  只能对属于你的进程执行renice；
  只能通过renice降低进程的优先级；
  root用户可以通过renice来任意调整进程的优先级。
如果想完全控制运行进程，必须以root账户身份登录或使用sudo命令。
```

### 定时运行作业

当你开始使用脚本时，可能会想要在某个预设时间运行脚本，这通常是在你不在场的时候。Linux系统提供了多个在预选时间运行脚本的方法：at命令和cron表。每个方法都使用不同的技术来安排脚本的运行时间和频率。接下来会依次介绍这些方法。

### 用at 命令来计划执行作业

at命令允许指定Linux系统何时运行脚本。at命令会将作业提交到队列中，指定shell何时运行该作业。at的守护进程atd会以后台模式运行，检查作业队列来运行作业。大多数Linux发行版会在启动时运行此守护进程。

atd守护进程会检查系统上的一个特殊目录（通常位于/var/spool/at）来获取用at命令提交的作业。默认情况下，atd守护进程会每60秒检查一下这个目录。有作业时，atd守护进程会检查作业设置运行的时间。如果时间跟当前时间匹配，atd守护进程就会运行此作业。

1. at命令的格式

`at [-f filename] time`

time参数指定了Linux系统何时运行该作业。如果你指定的时间已经错过，at命令会在第二天的那个时间运行指定的作业。

```
的那个时间运行指定的作业。
在如何指定时间这个问题上，你可以非常灵活。at命令能识别多种不同的时间格式。
  标准的小时和分钟格式，比如10:15。
  AM/PM指示符，比如10:15 PM。
  特定可命名时间，比如now、noon、midnight或者teatime（4 PM）。
除了指定运行作业的时间，也可以通过不同的日期格式指定特定的日期。
  标准日期格式，比如MMDDYY、MM/DD/YY或DD.MM.YY。
  文本日期，比如Jul 4或Dec 25，加不加年份均可。
  你也可以指定时间增量。
  当前时间+25 min
  明天10:15 PM
  10:15+7天
```

在你使用at命令时，该作业会被提交到作业队列（job queue）。作业队列会保存通过at命令提交的待处理的作业。针对不同优先级，存在26种不同的作业队列。作业队列通常用小写字母a~z和大写字母A~Z来指代。

作业队列的字母排序越高，作业运行的优先级就越低（更高的nice值）。默认情况下，at的作业会被提交到a作业队列。如果想以更高优先级运行作业，可以用-q参数指定不同的队列字母。

2. 获取作业的输出

当作业在Linux系统上运行时，显示器并不会关联到该作业。取而代之的是，Linux系统会将

提交该作业的用户的电子邮件地址作为STDOUT和STDERR。任何发到STDOUT或STDERR的输出都

会通过邮件系统发送给该用户。

3. 列出等待的作业

atq命令可以查看系统中有哪些作业在等待。

4. 删除作业

一旦知道了哪些作业在作业队列中等待，就能用atrm命令来删除等待中的作业。只要指定想要删除的作业号就行了。只能删除你提交的作业，不能删除其他人的。

### 安排需要定期执行的脚本

用at命令在预设时间安排脚本执行非常好用，但如果你需要脚本在每天的同一时间运行或是每周一次、每月一次呢？用不着再使用at不断提交作业了，你可以利用Linux系统的另一个功能。

Linux系统使用cron程序来安排要定期执行的作业。cron程序会在后台运行并检查一个特殊的表（被称作cron时间表），以获知已安排执行的作业。

1. cron时间表

cron时间表采用一种特别的格式来指定作业何时运行。其格式如下：

```shell
min hour dayofmonth month dayofweek command
```

cron时间表允许你用特定值、取值范围（比如1~5）或者是通配符（星号）来指定条目。例

如，如果想在每天的10:15运行一个命令，可以用cron时间表条目：

`15 10 * * * command`

2. 构建cron时间表

每个系统用户（包括root用户）都可以用自己的cron时间表来运行安排好的任务。Linux提供了crontab命令来处理cron时间表。要列出已有的cron时间表，可以用-l选项。

默认情况下，用户的cron时间表文件并不存在。要为cron时间表添加条目，可以用-e选项。在添加条目时，crontab命令会启用一个文本编辑器（参见第10章），使用已有的cron时间表作为文件内容（或者是一个空文件，如果时间表不存在的话）。

3. 浏览cron目录

如果你创建的脚本对精确的执行时间要求不高，用预配置的cron脚本目录会更方便。有4个基本目录：hourly、daily、monthly和weekly。

`ls /etc/cron.*ly`

因此，如果脚本需要每天运行一次，只要将脚本复制到daily目录，cron就会每天执行它。

4. anacron程序

cron程序的唯一问题是它假定Linux系统是7×24小时运行的。除非将Linux当成服务器环境来运行，否则此假设未必成立。

如果某个作业在cron时间表中安排运行的时间已到，但这时候Linux系统处于关机状态，那么这个作业就不会被运行。当系统开机时，cron程序不会再去运行那些错过的作业。要解决这个问题，许多Linux发行版还包含了anacron程序。

如果anacron知道某个作业错过了执行时间，它会尽快运行该作业。这意味着如果Linux系统关机了几天，当它再次开机时，原定在关机期间运行的作业会自动运行。这个功能常用于进行常规日志维护的脚本。如果系统在脚本应该运行的时间刚好关机，日志文件就不会被整理，可能会变很大。通过anacron，至少可以保证系统每次启动时整理日志文件。

anacron程序只会处理位于cron目录的程序，比如/etc/cron.monthly。它用时间戳来决定作业是否在正确的计划间隔内运行了。每个cron目录都有个时间戳文件，该文件位于/var/spool/anacron。

anacron时间表的基本格式和cron时间表略有不同：

`period delay identifier command`

period条目定义了作业多久运行一次，以天为单位。anacron程序用此条目来检查作业的时间戳文件。delay条目会指定系统启动后anacron程序需要等待多少分钟再开始运行错过的脚本。command条目包含了run-parts程序和一个cron脚本目录名。run-parts程序负责运行目录中传给它的任何脚本。

注意，anacron不会运行位于/etc/cron.hourly的脚本。这是因为anacron程序不会处理执行时间需求小于一天的脚本。

identifier条目是一种特别的非空字符串，如cron-weekly。它用于唯一标识日志消息和错误邮件中的作业。



### 使用新shell 启动脚本

回想一下当用户登入bash shell时需要运行的启动文件（参见第6章）。另外别忘了，不是所有的发行版中都包含这些启动文件。基本上，依照下列顺序所找到的第一个文件会被运行，其余的文件会被忽略：

```
  $HOME/.bash_profile
  $HOME/.bash_login
  $HOME/.profile
```

# 高级shell 脚本编程

## 17创建函数

### 创建函数

有两种格式可以用来在bash shell脚本中创建函数。第一种格式采用关键字function，后跟分配给该代码块的函数名。

函数名唯一、先定义后使用

`# after function add a " " or "()"`

```shell
function name {
commands
}
```

```shell
name() {
commands
}
```

### 使用函数

```shell
#!/bin/bash
# using a function in a script
function func1 {
echo "This is an example of a function"
}
count=1
while [ $count -le 5 ]
do
func1
count=$[ $count + 1 ]
done
echo "This is the end of the loop"
func1
echo "Now this is the end of the script"
```

### 返回值

bash shell会把函数当作一个小型脚本，运行结束时会返回一个退出状态码。有3种不同的方法来为函数生成退出状态码。

### 默认退出状态码

默认情况下，函数的退出状态码是函数中最后一条命令返回的退出状态码。在函数执行结束后，可以用标准变量$?来确定函数的退出状态码。

```shell
#!/bin/bash
# testing the exit status of a function
func1() {
echo "trying to display a non-existent file"
ls -l badfile
}
echo "testing the function: "
func1
echo "The exit status is: $?"
```

### 使用return 命令

bash shell使用return命令来退出函数并返回特定的退出状态码。return命令允许指定一个整数值来定义函数的退出状态码，从而提供了一种简单的途径来编程设定函数退出状态码。

```shell
#!/bin/bash
# using the return command in a function
function dbl {
read -p "Enter a value: " value
echo "doubling the value"
return $[ $value * 2 ]
}
dbl
echo "The new value is $?"
```

但当用这种方法从函数中返回值时，要小心了。记住下面两条技巧来避免问题：

 记住，函数一结束就取返回值；

 记住，退出状态码必须是0~255。

### 使用函数输出

正如可以将命令的输出保存到shell变量中一样，你也可以对函数的输出采用同样的处理办法。可以用这种技术来获得任何类型的函数输出，并将其保存到变量中：

`result='dbl'`

这个命令会将dbl函数的输出赋给$result变量。下面是在脚本中使用这种方法的例子。

```shell
#!/bin/bash
# using the echo to return a value
function dbl {
read -p "Enter a value: " value
echo $[ $value * 2 ]
}
result=$(dbl)
echo "The new value is $result"
```

read命令输出了一条简短的消息来向用户询问输入值。bash shell脚本非常聪明，并不将其作为STDOUT输出的一部分，并且忽略掉它。如果你用echo语句生成这条消息来向用户查询，那么它会与输出值一起被读进shell变量中。

通过这种技术，你还可以返回浮点值和字符串值。这使它成为一种获取函数返回值的强大方法。

### 在函数中使用变量

### 向函数传递参数

函数可以使用标准的参数环境变量来表示命令行上传给函数的参数。例如，函数名会在\$0变量中定义，函数命令行上的任何参数都会通过\$1、\$2等定义。也可以用特殊变量\$#来判断传给函数的参数数目。

```shell
#!/bin/bash
# passing parameters to a function
function addem {
if [ $# -eq 0 ] || [ $# -gt 2 ]
then
echo -1
elif [ $# -eq 1 ]
then
echo $[ $1 + $1 ]
else
echo $[ $1 + $2 ]
fi
}
echo -n "Adding 10 and 15: "
value=$(addem 10 15)
echo $value
echo -n "Let's try adding just one number: "
value=$(addem 10)
echo $value
echo -n "Now trying adding no numbers: "
value=$(addem)
echo $value
echo -n "Finally, try adding three numbers: "
value=$(addem 10 15 20)
echo $value
```

由于函数使用特殊参数环境变量作为自己的参数值，因此它无法直接获取脚本在命令行中的参数值。

尽管函数也使用了$1和$2变量，但它们和脚本主体中的$1和$2变量并不相同。要在函数中使用这些值，必须在调用函数时手动将它们传过去。

### 在函数中处理变量

### 全局变量

默认情况下，你在脚本中定义的任何变量都是全局变量。在函数外定义的变量可在函数内正常访问。

### 局部变量

无需在函数中使用全局变量，函数内部使用的任何变量都可以被声明成局部变量。要实现这一点，只要在变量声明的前面加上local关键字就可以了。

`local temp`

也可以在变量赋值语句中使用local关键字：

`local temp=$[ $value + 5 ]`

### 数组变量和函数

如果你试图将该数组变量作为函数参数，函数只会取数组变量的第一个值。

要解决这个问题，你必须将该数组变量的值分解成单个的值，然后将这些值作为函数参数使用。

```shell
#!/bin/bash
# array variable to function test
function testit {
local newarray
newarray=(;'echo "$@"')
echo "The new array value is: ${newarray[*]}"
}
myarray=(1 2 3 4 5)
echo "The original array is ${myarray[*]}"
testit ${myarray[*]}
```

### 从函数返回数组

从函数里向shell脚本传回数组变量也用类似的方法。函数用echo语句来按正确顺序输出单个数组值，然后脚本再将它们重新放进一个新的数组变量中。

```shell
#!/bin/bash
# returning an array value
function arraydblr {
	local origarray
	local newarray
	local elements
	local i
	origarray=($(echo "$@"))
	newarray=($(echo "$@"))
	elements=$[ $# - 1 ]
	for (( i = 0; i <= $elements; i++ ))
	{
		newarray[$i]=$[ ${origarray[$i]} * 2 ]
	}
	echo ${newarray[*]}
}
myarray=(1 2 3 4 5)
echo "The original array is: ${myarray[*]}"
arg1=$(echo ${myarray[*]})
result=($(arraydblr $arg1))
echo "The new array is: ${result[*]}"
```

该脚本用$arg1变量将数组值传给arraydblr函数。arraydblr函数将该数组重组到新的数组变量中，生成该输出数组变量的一个副本。然后对数据元素进行遍历，将每个元素值翻倍，并将结果存入函数中该数组变量的副本。

arraydblr函数使用echo语句来输出每个数组元素的值。脚本用arraydblr函数的输出来重新生成一个新的数组变量。

### 函数递归

```shell
#!/bin/bash
# using recursion
function factorial {
if [ $1 -eq 1 ]
then
echo 1
else
local temp=$[ $1 - 1 ]
local result=$(factorial $temp)
echo $[ $result * $1 ]
fi
}
read -p "Enter value: " value
result=$(factorial $value)
echo "The factorial of $value is: $result"
```

### 创建库

```shell
my script functions
function addem {
echo $[ $1 + $2 ]
}
function multem {
echo $[ $1 * $2 ]
}
function divem {
if [ $2 -ne 0 ]
then
echo $[ $1 / $2 ]
else
echo -1
fi
}
```

问题出在shell函数的作用域上。和环境变量一样，shell函数仅在定义它的shell会话内有效。如果你在shell命令行界面的提示符下运行myfuncs shell脚本，shell会创建一个新的shell并在其中运行这个脚本。它会为那个新shell定义这三个函数，但当你运行另外一个要用到这些函数的脚本时，它们是无法使用的。

使用函数库的关键在于source命令。source命令会在当前shell上下文中执行命令，而不是创建一个新shell。可以用source命令来在shell脚本中运行库文件脚本。这样脚本就可以使用库中的函数了。

source命令有个快捷的别名，称作点操作符（dot operator）。要在shell脚本中运行myfuncs库文件，只需添加下面这行：

`. ./myfuncs`

```shell
#!/bin/bash
# using functions defined in a library file
. ./myfuncs
value1=10
value2=5
result1=$(addem $value1 $value2)
result2=$(multem $value1 $value2)
result3=$(divem $value1 $value2)
echo "The result of adding them is: $result1"
echo "The result of multiplying them is: $result2"
echo "The result of dividing them is: $result3"
```

### 在命令行上使用函数

### 在命令行上创建函数

因为shell会解释用户输入的命令，所以可以在命令行上直接定义一个函数。有两种方法。

一种方法是采用单行方式定义函数。

`function divem { echo $[ $1 / $2 ]; }`

另一种方法是采用多行方式来定义函数。在定义时，bash shell会使用次提示符来提示输入更多命令。用这种方法，你不用在每条命令的末尾放一个分号，只要按下回车键就行。

在命令行上创建函数时要特别小心。如果你给函数起了个跟内建命令或另一个命令相同的名字，函数将会覆盖原来的命令。

### 在.bashrc 文件中定义函数

1. 直接定义函数

可以直接在主目录下的.bashrc文件中定义函数。许多Linux发行版已经在.bashrc文件中定义了一些东西，所以注意不要误删了。把你写的函数放在文件末尾就行了。这里有个例子。

2. 读取函数文件

只要是在shell脚本中，都可以用source命令（或者它的别名点操作符）将库文件中的函数添加到你的.bashrc脚本中。

更好的是，shell还会将定义好的函数传给子shell进程，这样一来，这些函数就自动能够用于该shell会话中的任何shell脚本了。你可以写个脚本，试试在不定义或使用source的情况下，直接使用这些函数。

## 18图形化桌面环境中的脚本编程

### 创建文本菜单

### 创建菜单布局

## 19 初识sed和gawk

到目前为止， shell脚本最常见的一个用途就是处理文本文件。检查日志文件、读取配置文件、处理数据元素，shell脚本可以帮助我们将文本文件中各种数据的日常处理任务自动化。但仅靠shell脚本命令来处理文本文件的内容有点勉为其难。如果想在shell脚本中处理任何类型的数据，你得熟悉Linux中的sed和gawk工具。这两个工具能够极大简化需要进行的数据处理任务。

### 文本处理

### sed 编辑器

sed编辑器被称作流编辑器（stream editor），和普通的交互式文本编辑器恰好相反。在交互式文本编辑器中（比如vim），你可以用键盘命令来交互式地插入、删除或替换数据中的文本。流编辑器则会在编辑器处理数据之前基于预先提供的一组规则来编辑数据流。

sed编辑器可以根据命令来处理数据流中的数据，这些命令要么从命令行中输入，要么存储在一个命令文本文件中。sed编辑器会执行下列操作。

```
(1) 一次从输入中读取一行数据。
(2) 根据所提供的编辑器命令匹配数据。
(3) 按照命令修改流中的数据。
(4) 将新的数据输出到STDOUT。
```

在流编辑器将所有命令与一行数据匹配完毕后，它会读取下一行数据并重复这个过程。在流编辑器处理完流中的所有数据行后，它就会终止。

`sed options script file`

```shell
选 项 描 述
-e script 在处理输入时，将script中指定的命令添加到已有的命令中
-f file 在处理输入时，将file中指定的命令添加到已有的命令中
-n 不产生命令输出，使用print命令来完成输出
```

script参数指定了应用于流数据上的单个命令。如果需要用多个命令，要么使用-e选项在命令行中指定，要么使用-f选项在单独的文件中指定。

1. 在命令行定义编辑器命令

默认情况下，sed编辑器会将指定的命令应用到STDIN输入流上。这样你可以直接将数据通过管道输入sed编辑器处理。

`echo "This is a test" | sed 's/test/big test/'`

这个例子在sed编辑器中使用了s命令。s命令会用斜线间指定的第二个文本字符串来替换第一个文本字符串模式。在本例中是big test替换了test。

`sed 's/dog/cat/' data1.txt`

这时sed不会改变data1.txt`文件

2. 在命令行使用多个编辑器命令

要在sed命令行上执行多个命令时，只要用-e选项就可以了

`sed -e 's/brown/green/; s/dog/cat/' data1.txt`

两个命令都作用到文件中的每行数据上。命令之间必须用分号隔开，并且在命令末尾和分号之间不能有空格。

如果不想用分号，也可以用bash shell中的次提示符来分隔命令。只要输入第一个单引号标示出sed程序脚本的起始（sed编辑器命令列表），bash会继续提示你输入更多命令，直到输入了标示结束的单引号。

3. 从文件中读取编辑器命令

如果有大量要处理的sed命令，那么将它们放进一个单独的文件中通常会更方便一些。可以在sed命令中用-f选项来指定文件。

`sed -f script1.sed data1.txt`

我们很容易就会把sed编辑器脚本文件与bash shell脚本文件搞混。为了避免这种情况，可以使用.sed作为sed脚本文件的扩展名。

### gawk 程序

虽然sed编辑器是非常方便自动修改文本文件的工具，但其也有自身的限制。通常你需要一个用来处理文件中的数据的更高级工具，它能提供一个类编程环境来修改和重新组织文件中的数据。这正是gawk能够做到的。

gawk程序是Unix中的原始awk程序的GNU版本。gawk程序让流编辑迈上了一个新的台阶，它提供了一种编程语言而不只是编辑器命令。在gawk编程语言中，你可以做下面的事情：

```
  定义变量来保存数据；
  使用算术和字符串操作符来处理数据；
  使用结构化编程概念（比如if-then语句和循环）来为数据处理增加处理逻辑；
  通过提取数据文件中的数据元素，将其重新排列或格式化，生成格式化报告。
```

gawk程序的报告生成能力通常用来从大文本文件中提取数据元素，并将它们格式化成可读的报告。其中最完美的例子是格式化日志文件。在日志文件中找出错误行会很难，gawk程序可以让你从日志文件中过滤出需要的数据元素，然后你可以将其格式化，使得重要的数据更易于阅读。

1. gawk命令格式

`gawk options program file`

```shell
选 项 描 述
-F fs 指定行中划分数据字段的字段分隔符
-f file 从指定的文件中读取程序
-v var=value 定义gawk程序中的一个变量及其默认值
-mf N 指定要处理的数据文件中的最大字段数
-mr N 指定数据文件中的最大数据行数
-W keyword 指定gawk的兼容模式或警告等级
```

gawk的强大之处在于程序脚本。可以写脚本来读取文本行的数据，然后处理并显示数据，创建任何类型的输出报告。

2. 从命令行读取程序脚本

awk程序脚本用一对花括号来定义。你必须将脚本命令放到两个花括号（{}）中。

```shell
gawk '{print "Hello World!"}'
```

在运行这个程序时，它会一直等待从STDIN输入的文本。

要终止这个gawk程序，你必须表明数据流已经结束了。bash shell提供了一个组合键来生成EOF（End-of-File）字符。Ctrl+D组合键会在bash中产生一个EOF字符。这个组合键能够终止该gawk程序并返回到命令行界面提示符下。

3. 使用数据字段变量

gawk的主要特性之一是其处理文本文件中数据的能力。它会自动给一行中的每个数据元素分配一个变量。默认情况下，gawk会将如下变量分配给它在文本行中发现的数据字段：

```
  $0代表整个文本行；
  $1代表文本行中的第1个数据字段；
  $2代表文本行中的第2个数据字段；
  $n代表文本行中的第n个数据字段。
```

```shell
$ cat data2.txt
One line of test text.
Two lines of test text.
Three lines of test text.
$
$ gawk '{print $1}' data2.txt
One
Two
Three
$
```

如果你要读取采用了其他字段分隔符的文件，可以用-F选项指定。

`gawk -F: '{print $1}' /etc/passwd`

4. 在程序脚本中使用多个命令

`echo "My name is Rich" | gawk '{$4="Christine"; print $0}'`

也可以用次提示符一次一行地输入程序脚本命令。

5. 从文件中读取程序

```shell
$ cat script2.gawk
{print $1 "'s home directory is " $6}
$
$ gawk -F: -f script2.gawk /etc/passwd
```

可以在程序文件中指定多条命令。要这么做的话，只要一条命令放一行即可，不需要用分号。

```shell
{
text = "'s home directory is "
print $1 text $6
}
```

6.  在处理数据前运行脚本

gawk还允许指定程序脚本何时运行。默认情况下，gawk会从输入中读取一行文本，然后针对该行的数据执行程序脚本。有时可能需要在处理数据前运行脚本，比如为报告创建标题。`BEGIN`关键字就是用来做这个的。它会强制gawk在读取数据前执行BEGIN关键字后指定的程序脚本。

`gawk 'BEGIN {print "Hello World!"}'`

这次print命令会在读取数据前显示文本。但在它显示了文本后，它会快速退出，不等待任何数据。如果想使用正常的程序脚本中处理数据，必须用另一个脚本区域来定义程序。

7. 在处理数据后运行脚本

与BEGIN关键字类似，END关键字允许你指定一个程序脚本，gawk会在读完数据后执行它。

````shell
BEGIN {
print "The latest list of users and shells"
print " UserID \t Shell"
print "-------- \t -------"
FS=":"
}
{
print $1 " \t " $7
}
END {
print "This concludes the listing"
}
````

### sed 编辑器基础

### 更多的替换选项

1. 替换标记

替换命令在替换多行中的文本时能正常工作，但默认情况下它只替换每行中出现的第一处。要让替换命令能够替换一行中不同地方出现的文本必须使用替换标记（substitution flag）。替换标记会在替换命令字符串之后设置。

```
  数字，表明新文本将替换第几处模式匹配的地方；
  g，表明新文本将会替换所有匹配的文本；
  p，表明原先行的内容要打印出来；
  w file，将替换的结果写到文件中。
```

`sed -n 's/test/trial/p' data5.txt`

-n选项将禁止sed编辑器输出。但p替换标记会输出修改过的行。将二者配合使用的效果就是只输出被替换命令修改过的行。

w替换标记会产生同样的输出，不过会将输出保存到指定文件中。

2. 替换字符

`sed 's/\/bin\/bash/\/bin\/csh/' /etc/passwd`

在这个例子中，感叹号被用作字符串分隔符，这样路径名就更容易阅读和理解了。

### 使用地址



