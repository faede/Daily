#### [Training: Regex](http://www.wechall.net/challenge/training/regex/index.php) ([Training](http://www.wechall.net/challs/Training), [Regex](http://www.wechall.net/challs/Regex))

正则表达式匹配空字符串，并且仅匹配空字符串

```
/^$/
```

^用于匹配字符串头，$匹配字符串尾。

^$用于匹配一行开始/结束的字符串



用于精确匹配



```
[\s\S]
```

匹配所有。\s 是匹配所有空白符，包括换行，\S 非空白符，不包括换行。



```
\w
```

匹配字母、数字、下划线。等价于 [A-Za-z0-9_]



```
\d 匹配数字
\D 匹配任意非数字的字符
```



```
[\w\W] 也可以达到 [\s\S]
```



```
\b	匹配一个单词边界，即字与空格间的位置。
\B	非单词边界匹配。
```

\b 位于要匹配的字符串的开始，它在单词的开始处查找匹配项。如果它位于字符串的结尾，它在单词的结尾处查找匹配项。

```
/ter\b/ 匹配Chapter结尾的ter
/\bCha/ 匹配Chapter开头的Cha
```







```
{n} 匹配n次
{n,} 匹配大于等于n次
{n,m} 匹配大于等于n小于等于m次
```





```
\d{3}
```

匹配三个数字



```
(pattern)：匹配pattern并捕获该匹配的子表达式，可以使用$0…$9属性从结果”匹配”集合中检索捕获的匹配；
```



Regex Group: 

()表示捕获分组，() 会把每个分组里的匹配的值保存起来， 多个匹配值可以通过数字 n 来查看(n是一个数字，表示第 n 个捕获组的内容)



non-capturing group

```
(?:) 匹配pattern但不捕获该匹配的子表达式
```



```
exp1(?=exp2)：查找 exp2 前面的 exp1
/ra(?=1)/ 匹配1前的ra
```

```
(<=exp2)exp1：查找 exp2 后的 exp1
```

```
exp1(?!exp2)：查找后面不是 exp2 的 exp1
```

```
(?<!exp2)exp1：查找前面不是 exp2 的 exp1
```

#### [Training: Programming 1](http://www.wechall.net/challenge/training/programming1/index.php) ([Training](http://www.wechall.net/challs/Training), [Coding](http://www.wechall.net/challs/Coding))



```python
import requests
url = 'http://www.wechall.net/challenge/training/programming1/index.php?action=request'
headers = {
    'WC' :  '13703310-59474-gTryTu3QC2EXBdiS'
}
r = requests.get(url, cookies = headers)
key = r.text
print(re.text)
url2 = 'http://www.wechall.net/challenge/training/programming1/index.php?answer='
requests.get(url2 + key, cookies = headers)
```



#### [Training: PHP LFI](http://www.wechall.net/challenge/training/php/lfi/up/index.php) ([Exploit](http://www.wechall.net/challs/Exploit), [PHP](http://www.wechall.net/challs/PHP), [Training](http://www.wechall.net/challs/Training))

字符串截断(用法已经被抛弃)

http://www.wechall.net/challenge/training/php/lfi/up/index.php?file=../../solution.php%00



#### [PHP 0817](http://www.wechall.net/challenge/php0817/index.php) ([PHP](http://www.wechall.net/challs/PHP), [Exploit](http://www.wechall.net/challs/Exploit))

http://www.wechall.net/challenge/php0817/index.php?which=solution

php中switch 执行的是松散比较 ==

两边变量为string或者null， 执行数字或者数值 ，"42" == 42 true

同时对 "php" == 0 true



#### [Training: Crypto - Transposition I](http://www.wechall.net/challenge/training/crypto/transposition1/index.php) **([Crypto](http://www.wechall.net/challs/Crypto), [Training](http://www.wechall.net/challs/Training))**

ihipfcngaicd

临位互换



#### [Training: Crypto - Substitution I](http://www.wechall.net/challenge/training/crypto/simplesub1/index.php) ([Crypto](http://www.wechall.net/challs/Crypto), [Training](http://www.wechall.net/challs/Training))

https://quipqiup.com/

