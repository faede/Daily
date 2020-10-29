

## C++ memory primitives

```cpp
void * p1 = malloc(512);
free(p1);

complex<int> * p2 = new complex<int>;
delete p2;
void * p3 = ::operator new(512);
::operator delete(p3);

#ifdef _MSC_VER
	// 3 个整数
	int *p4 = allocator<int>().allocate(3,(int*)0); // (int*)0 暂时不用理解
	allocator<int>().deallocate(p4,3);
#endif
#ifdef __BORLANDC__
	// 5 个整数
	int *p4 = allocator<int>().allocate(5);//也有第二参数但是有默认值
	allocator<int>().deallocate(p4,5);//要记住当时分配了几个
#endif
#ifdef __GNUC__
	//gnu 2.9
	void* p4 = alloc::allocate(512);//512bytes 
	alloc::deallocate(p4,512);
#endif
#ifdef __GNUC__
	//gnu 4.9
	void* p4 = allocator<int>().allocate(7);
	allocator<int>().deallocate(p4,7);

	void* p5 = __gnu_cxx::__pool_alloc<int>().allocate(9);
	__gnu_cxx::__pool_alloc<int>().deallocate((int*)p5,9);
#endif
```

## new expression

```cpp
Complex * pc = new Complex(1,2);
     |
     |
    \ /
Complex * pc;
try{
    void * mem = operator new(sizeof(Complex));
    pc = static_cast<Complex*>(mem);
    pc->Complex::Complex(1,2);//编译器才可以(不一定)
    //可以
    ==>new(p) Complex(1,2) //placement new
}
catch(std::bad_alloc)
{
    
}

// vc
void*operator new(size_t size ,cosnt std::nothrow_t & _THROW0()) //保证不抛异常
{
    void * p;
    while((p = malloc(size)) == 0)
    {
        _TRY_BEGIN
            	if(_callnewh(szie) == 0) break;// new handles
        _CATCH(std::bad_alloc) return (0);
        _CATCH_END
    }
    return (p);
}
```

## delete expression

```cpp
Complex * pc = new Complex(1,2);

...
delte pc;

pc->~Complex();//可以
operator delete(pc);
void __cdecl operator delete(void * p)_THROW0()
{
    free(p);
}
```



```cpp
string * pstr = new string;

// !pstr->string::string("jjhou"); // 'class std::basic_string<char>' no member named

// ! pstr->~string();//carsh 可以使用
class A{
    public:
    int id;
    A(int i):id(i) {}
    ~A(){}
};
A * pA = new A(1);
// !pA->A::A(3)  //vc6 ok ; gcc error

//!A::A(5);  //vc ok ;gcc error


```

## array new,array delete

```cpp
Complex *pca = new Complex[3];
...
delete[] pca; //唤起3次dtor

```

cookie  | Complex object  | Complex object  | Complex object  |

(something about bookkeeping)

​		    /|\

​			pca



```cpp
int * p1 = new int[10];
delete p1;//对于整数加不加[]无所谓 因为析构函数没有意义

Demo *p = new Demo[3];
delete [] p;//有意义 cookie里会放上3 不加[]布局出错
```

## placement new

```cpp
#include<new>
//允许建造在已分配的内存中
char * buf = new char[sizeof(Comlex)*3];
Complex*pc = new (buf)Complex(1,2); // 1
delete [] buf;

//1 调用
try{
    void * mem = operator new(sizeof(Complex),buf);//  void * operator new(size_t,void * loc) return loc;
    pc = static_cast<Complex*>(mem);
    pc->Complex::Complex(1,2);
}
catch(std::bad_alloc)
{
}
```

## 重载::operator new /::operator delete

```cpp
void *myAlloc(size_t size)
{return malloc(size);}
void *myFree(void * ptr)
{return free(ptr);}
inline void *operator new(size_t size)
{return myAlloc(size);}
inline void *operator new[](size_t size)
{return myAlloc(size);}
inline void operator delete(void * ptr)
{myFree(ptr);}
inline void operator delete[](void * ptr)
{myFree(ptr);}


```

## 重载operator new/operator delete



```cpp
class Foo{
    public:
    void * opeator new(size_t);
    void opeator delete(void *, size_t); //size_t optional可以不加
    //其实应该是static 但是cpp内部有处理
    
    
    void * opeator new[](szie_t);
    void opeator delete[](void *, size_t);
};

```



```cpp
class Foo{
    public:
    int _id;
    long _data;
    string _str;
    ...
    Foo(){}
    Foo(int){throw bad();}
    static void * opeator new(size_t);
    static void opeator delete(void *, size_t);
    
    
    static void * opeator new[](szie_t);
    static void opeator delete[](void *, size_t);
};
//调用重载函数
Foo *p = new Foo(7);
delete p;

//调用全局
Foo *p = ::new Foo(7);
::delete p;
```

## 重载new()/delete()

```cpp
Foo* pf = new(300,'c') Foo; //第一个参数必须是size_t Foo的大小

void * opeator new(size_t);//一般重载
void * opeator new(size_t,void *start);//已提供的placement new
void * opeator new(size_t,long extra);//新的placement new
void * opeator new(size_t,long extra);//新的placement new
void * opeator new(long,long extra);//error


//可以写出多个operator delete但是不会被delete调用
static void opeator delete(void *, size_t);
static void opeator delete(void *, void *);
static void opeator delete(void *, long);
static void opeator delete(void *, long,char);
//抛出异常时，才会调用operator delete    
//gnu 2.9调用 4.9不调用
//new没有对应delete也无所谓，因为语义就是在处理异常
```

## basic_string 使用new(extra)扩充申请量



```cpp
template<>
class basic_string
{
private:
	struct Rep{};
	
	inline static Rep*create(size_t);
	
	==> create(size_t extra){
		extra = frob_size(extra + 1);
		Rep *p = new (extra) Rep;
		...
		return p;
	}
}
```



## per-class allocator,1  ref. C++ primer 3/e p.765



```cpp
#include<cstddef>
#inlcude<iostream>
using namespace std;
class Screen{
    public:
    Screen(int x):i(x) {};
    int get() { return i;}
    void * operator new(size_t);
    void operator delete(void *,size_t);
    
    private:
    Screen * next;
    //多消耗一个next  下版会更好
    static Screen * freeStore;
    static const int screenChunk;
    
   	private:
    int i;
};
Screen * Screen::freeStore = 0;
const int Screen::screenChunk = 24;
void *Screen::operator new(size_t size)
{
    Screen * p ;
    if(!freeStore){
        size_t chunk = screenChunk* size;
        freeStore = p =
            reinterpret_cast<Screen*>(new char[chunk]);
        //像list一样串接回去
        for(; p!= &freeStore[screenChunk-1];++p)
            p->next = p + 1;
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore ->next;
    return p;
}
void Screen:operator delete(void *p,size_t){
    (static_cast<Screen*>(p))->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}

cout<<sizeof(Screen)<<endl;
size_t const N = 100;
Screen *p [N];
for(int i = 0; i < N; ++i)
    p[i] = new Screen(i);
for(int i = 0; i < 10; ++i)
    cout << p[i] <<endl;
for(int i = 0; i < 10; ++i)
    delete p[i];
```



