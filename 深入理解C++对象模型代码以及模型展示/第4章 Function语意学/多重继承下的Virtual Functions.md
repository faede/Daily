### 多重继承下的Virtual Functions

```cpp
class Derived	size(20):
	+---
 0	| +--- (base class Base1)
 0	| | {vfptr}
 4	| | data_Base1
	| +---
 8	| +--- (base class Base2)
 8	| | {vfptr}
12	| | data_Base2
	| +---
16	| data_Derived
	+---

Derived::$vftable@Base1@:
	| &Derived_meta //informaion 表示class的类型 (为了支持多态)
	|  0
 0	| &Derived::{dtor} 
 1	| &Base1::speakClearly 
 2	| &Derived::clone 

Derived::$vftable@Base2@:
	| -8 // offset 同下
 0	| &thunk: this-=8; goto Derived::{dtor} //指向Base2首部的this指针需要调整位置(this -= sizeof(Base2))使其指向Derived的首部，之后再调用Derived的析构函数
 1	| &Base2::mumble 
 2	| &thunk: this-=8; goto Base2* Derived::clone 
 3	| &thunk: this-=8; goto Derived* Derived::clone 

Derived::{dtor} this adjustor: 0
Derived::clone this adjustor: 0
Derived::__delDtor this adjustor: 0
Derived::__vecDelDtor this adjustor: 0
```



```cpp
class Base1	size(8):
	+---
 0	| {vfptr}
 4	| data_Base1
	+---

Base1::$vftable@:
	| &Base1_meta
	|  0
 0	| &Base1::{dtor} 
 1	| &Base1::speakClearly 
 2	| &Base1::clone 

Base1::{dtor} this adjustor: 0
Base1::speakClearly this adjustor: 0
Base1::clone this adjustor: 0
Base1::__delDtor this adjustor: 0
Base1::__vecDelDtor this adjustor: 0
```



```cpp
class Base2	size(8):
	+---
 0	| {vfptr}
 4	| data_Base2
	+---

Base2::$vftable@:
	| &Base2_meta
	|  0
 0	| &Base2::{dtor} 
 1	| &Base2::mumble 
 2	| &Base2::clone 

Base2::{dtor} this adjustor: 0
Base2::mumble this adjustor: 0
Base2::clone this adjustor: 0
Base2::__delDtor this adjustor: 0
Base2::__vecDelDtor this adjustor: 0
```