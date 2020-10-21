# Standard Template Library

## 六大部件：

容器Containers 

分配器Allocators

算法Algorithms

迭代器Iterators

适配器Adapters

防函式Functors

```cpp
#include<vector>
#include<algorithm>
#include<functional>
#include<iostream>

using namespace std;

int main(){
	int ia[6] = {27,210,12,47,109,83};
	vector<int, allocator<int>> vi(ia,ia+6);
	
	cout << count_if(vi.begin(), vi.end(),
				not1(bind2nd(less<int>(),40)));
	return 0;
}
```



```cpp
std::vector<double> vec;
for(auto elem : vec){
	std::cout << elem << std::endl;
}
for(auto & elem : vec){
	elem *= 3;
}
```



```cpp
list<string>::iterator ite;
ite = ::find(c.begin(),c.end(),target);
```



## 容器分类

Sequence Containers:

Array, Vector, Deque, List, Forward-List



Associative Containers:

Set/Multiset

Map/Multimap



Unordered Containers(Associative Containers):



gnu_C



```cpp
	list<string,allocator<string>> c1;
	list<string,__gnu_cxx::malloc_allocator<string>> c2;
	list<string,__gnu_cxx::new_allocator<string>> c3;
	list<string,__gnu_cxx::__pool_alloc<string>> c4;
	list<string,__gnu_cxx::__mt_alloc<string>> c5;
	list<string,__gnu_cxx::bitmap_allocator<string>> c6;
```



初版new malloc 每分配一次内存需要很多附加开销

G2.9

alloc

减少附加空间分配的次数

通过链表指向新的空间



G4.9

std::allocator

__allocator_base 

__gnu_cxx:new_allocator

::operator new()

__pool_alloc 是G2.9的alloc



## List

G2.9  --- 4 一个指针

双向循环链表 

有一个虚拟节点(end())

```cpp
typedef __list_node<T> list_node;

typedef list_node * link_type;

link_type node;(4)



__list_node{
	typedef void * void_pointer;
	void_pointer prev;//(设计不合理)
	void_pointer next;
	T data;
};


typedef __list_iterator<T,T&,T *>iterator;
template<class T,class Ref,class Ptr>
struct __list_iterator{
    typedef bidirectional_iterator_tag iteratir_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T> list_node;
    typedef ptrdiff_t difference_tyep;
    
    link_type node;
};

reference operator *() const { return (*node).data;}
self  operator++(int){ //(参数是为了区分i++,++i) 
    self tmp = *this; //不会调用operator*() 而是唤醒拷贝构造。以*this为初始值
    ++*this;
    return tmp;    
}
self & operator++(){
    node = (link_type) ((*node).next);
    return *this;
}
++(++i); 对
(i++)++ 错
所以后加加 self 
    前加加 self &

reference operator *() const { return (*node).data;}
pointer operator->() const { return & (operator * ()); }

```



G4.9  -- 8  两个指针

```cpp
_List_iterator<_Tp> iterator;
struct _List_iterator{
    typedef std::bidirectional_iterator_tag iteratir_category;
	typedef _Tp * pointer;
	typedef _Tp & reference;
    ...
        
    _List_node_base * _M_next;
    _List_node_base * _M_prev;
};
typedef<typename _Tp>
struct _List_node:public _List_node_base{
    _Tp _M_data;
};


```



## Iterator Traits

程序需要知道指针的类型

萃取

```cpp
template<typename _ForwardIterator>
inline void
rotate(_ForwardIterator __first, _ForwardIterator __middle, _ForwardIterator __last){
	std::__roate(__first, __middle, __last, std::__iteraotr_category(__first)); (1)
}
-->
    __iteraotr_category(const _Iter &)
	{return typename iterator_traits<_Iter>::iterator_category();}

__roate(.. random_access_iteraros_tag){
    typedef typename iterator_traits<_RandomAccessIterator>::difference_type _Distance; (2)
    typedef typename iterator_traits<_RandomAccessIterator>::value_type _Value; (3)
}
reference(4)
pointer(5)
    
G 2.9
struct __list_iterator{ //(迭代器回答)
    typedef bidirectional_iterator_tag iteratir_category;
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    typedef __list_node<T> list_node;
    typedef ptrdiff_t difference_tyep;
    
    link_type node;
};

template <typename I>
algorithm(I first, I last){
	I::iterator_category  //算法询问
     I::pointer
        ..
}



```

如果distance超过定义的数据类型范围呢？

如果iterator 并不是一个class呢？
    例如native pointer (退化的iterator)

萃取机   要能力分清是否是class分出的

```cpp
template<class I>
struct iterator_traits{
	typedef typename I::value_type value_type;
};
template<class T>
struct iterator_traits<T*>{//偏特化
    typedef random_access_iteraros_tag iterator_category ;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};
template<class T>
struct iterator_traits<const T*>{
    typedef random_access_iteraros_tag iterator_category ;
    typedef T value_type;//注意是T而不是const T 因为声明一个const 变量并没有什么意义
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;
};



template <typename I>
algorithm(I first, I last){//通过traits间接询问
	typename iterator_traits<I>::value_type v1;
}
```



## vector



```cpp
template<class T,class Alloc = alloc>
class vector{
    public:
    	typedef T value_type;
    	typedef value_type * iterator; // T *
    	typedef value_type & reference;
    	typedef size_t size_type;
    protected:
    	iterator start;
  		iterator finish;
    	iterator end_of_storage;
    public:
    	iterator begin(){return start;}
    	iterator end(){return finish;}
    	size_type size()const { return size_type(end()-begin());}
    	size capacity()const { return size_type(end_of_storage-begin());}
    	bool empty() const{ return begin() == end();} 
    	reference operator[](size_type n){return *(begin()+n);}
    	reference front(){ return * begin();}
    	refernece back(){ return *end();}
    
    	void push_back(const & T x){
            if( finish != end_of_storage){
                construct(finish,x);
                ++finish;
            }
            else
                insert_aux(end(),x);
        }
    	
    	
};
template<class T, class Alloc>
void vector<T,Alloc>::insert_aux(iterator position, const T& x){
    if( finish != end_of_storage){
        construct(finish,*(finish - 1));
        ++finish;
        T x_copy = x;
        copy_backwaed(position, finish - 2, finish - 1);
        *position = x_copy;
     }
    else{
        const size_type old_size = size();
        const size_type len = old_size != 0 ? 2*old_size : 1;
        
        iterator new_start = data_allocator::allocate(len);
        iterator new_finish = new_start;
        try{
            new_finish = uninitialized_copy(start,position, new_start);
            construct(new_finish, x);
            ++new_finish;
            //拷贝安插点之后的内容 如insert的时候也会调用
            new_finish = uninitialized_copy(position,finish,new_finish);            
        }
        catch(){
            
        }
        destroy(begin(),end());
        deallocate();
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
         
}
```



## array

TR1

```cpp
template<typename _Tp, std::size_t _Nm>
struct array{ 
	typedef _Tp value_type;
	typedef _Tp* pointer;
	typedef value_type * iterator;
	
	value_type _M_instance[_Nm ? _Nm : 1];
	iterator begin()
	{return iterator(&_M_instance[0]);}
	iterator end()
	{return iterator(&_M_instance[_Nm]);}
    //没有ctor,没有dtor
}
```

## forward_list



## deque

分段连续

40

```cpp
template<class T,class Alloc = alloc, size_t BufSiz = 0>
class deque{
    public:
		typedef T value_type;
		typedef __deque_iterator<T,T&,T8,BufSiz> iterator;
	protected:
   		typedef pointer* map_pointer; // T**
		iterator start;
		iterator finish;
		map_pointer map;
		size_type map_size;
    public:
    	
};
struct __deque_iterator{
    typedef random_access_iteraros_tag iterator_category ;
    typedef T value_type;    
    typedef T* pointer;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;    
    typedef T** map_pointer;
    typedef __deque_iterator self;
    
    ..
    T * cur;
    T * first;
    T * last;
    map_pointer node;
}

iterator insert(iterator position, const value_type & x){
    if(posisition.cur == start.cur){
        push_front(x);
        return start;
    }else if(position.cur == finish.cur){
        push_back(x);
        iterator tmp = finish;
        --tmp;  
        return tmp;
    }else{
        return insert_aux(position,x);
    }
}
refernce front(){
    return *start;
}
reference back(){
	iterator tmp = finish;
	--tmp;  
	return tmp;
}
size_type size() const
{return finish - start;}
bool empty() const{
    return finish == start;
}
reference operator *()const{
    return *cur;
}
pointer operator->() const{
    return &(operator*());
}
operator - const(const self & x)const{
    return difference_typed(buffer_size())*(node - x.node - 1) + (cur - first) + (x.last - x.cur);
    //  							map                                末尾            起始
}
self& operator++(){
    ++cur;
    if(cur == last){
        set_node(node+1);
        cur = first;
    }
    return *this;
}
self operator++(int){
    self tmp = *this;
    ++*this;
    return tmp;
}
self operator--(){
    if(cur == first){
        set_node(node-1);
        cur = last;
    }
    --cur;
    return *this;
}
self & operator += (difference_type n){
    difference_type offset = n + (cur - first)；
    //在一个缓冲区
    //不在
}
self operstor +(difference_type n) const{
    self tmp = *this;
    return tmp += n ;
} 
self operator -=(difference_type n){
    return *this += -n;
}
reference operator[](difference_type n) const{
    return *(*this +n);
}
```



## queue

(adaptor)

```cpp
template<class T,class Sequence = deque<T>>
class deque{
	..
	protected:
		Sequence c;
	
	..
}
```



## stack

```cpp
template<class T,class Sequence = deque<T>>
class deque{
	..
	protected:
		Sequence c;
	
	..
}
```

stack 和 queue 都不允许便利，也不提供iterator

stack 和 queue 可以选择list或deque作为底层结构。(现实中采用deque)

stack可以用vector

queue不可以选择vector

stack和queue不可以选择set或map



## rb_tree

++ite 中序遍历

不应该用迭代器改变数值，但可以改



```cpp
template <class Key, class Value, class KeyOfValue,class Compare,class Alloc = alloc>
    // Value => key | data
class rb_tree{
	protected:
    	typedef __rb_tree_node<Value> rb_tree_node;
    	...
    public:
    	typedef rb_tree_node * link_type;
    	...
    protected:
    	size_type node_count;
    	link_type header;
    	Compare key_compare;//函数0，函数对象对象占1字节   4 + 4 + 1 = 9  =>  12
    	...
};
rb_tree<int,int,identity<int>,less<int>,alloc> myTree; //Gnu c
template<class Arg,class Result>
struct nuary_function{
  	typedef Arg argument_type;
    typedef Result result_type;
};
template <class T>
struct identity:public nuary_function<T,T>{
    const T & operator()(const T& x)const {return x;}
};
```



## hindle_body

遵循的设计理念 imp -> base

## set

```cpp
template <class Key, class Compare = less<Key>, class Alloc = alloc>
    // Value => key | data
class set{	
    public:
    	typedef Key key_type;
    	typedef Key value_type;
    	typedef Compare key_compare;
    	typedef Compare value_compare;
    	...
    private:
    	typedef rb_tree<key_type,value_type,
    						identity<value_type>,key_compare,Alloc> rep_type;
    	//                        key = value
    	rep_type t;
    public:
    	typedef typename rep_type::const_iterator iterator;// const  所以不可修改
    	...
};
```

底层操作调用t ， containter adapter





## map



````cpp
template<class Key, class T, class Compare = less<Key>, class Alloc = alloc>
class map{
	public:
		typedef Key key_type;
		typedef T data_type;
		typedef T mapped_type;
		typedef pair<const Key, T> value_type; // const Key
		typedef Compare key_compare;
	private:
		typedef rb_tree<key_type, value_type, 
							select1st<value_type>,key_compare, Alloc> rep_type;
		rep_type t;
    public:
    	typedef typename rep_type::iterator iterator;
}

//没找到就插入一个默认值pair<key,default>
//所以[]比inert慢 （因为要先做lower_dound
mapped_type & operator[](const key_type &__k){
    __glibcxx_function_requires(_DefalutConstructibleCon
    
    iterator __i = lower_bound(__k);
    if(__i == end() || key_compt()(__k,(*__i).first))
##if __cplusplus >= 201103L
                                _i = M_t._M

#else
     __i = insert(__i,value_type(__k,mapped_type()));
#endif                                
}
````



## hashtable

rehashing

```cpp
static const unsigned long
__stl_prime_list[__stl_num_primes] =
{
53,97,193,389,769,
1543,3079,6151,1289,24593,..
};

template<class Value,class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc = alloc>
class hashtable{
	public:
		typedef HashFcn hasher;
		typedef EqualKey key_equal;
		typedef size_t size_type;
	private:
		hasher hashl
		key_equal equals;
		ExtractKey get_key;
		
		typedef __hashtable_node<Value> node;
		
		vector<node *, Alloc> buckets;
		size_type num_elements;
	public:
		size_type bucket_count() const{ return buckts.size();}
		...
};
template <class Value>
struct __hashtable_node{
    __hashtable_node * next; //gnu c单向链表 vc双向链表
    Value val;
};
template<class Value,class Key,class HashFcn, class ExtractKey, class EqualKey, class Alloc = alloc>
struct __hashtable_iterator{
    ...
    node *cur;
    hashtable *ht;
};


hashtable<const char*,const char*,hash<const char *>,identity<const char *>, eqstr, alloc> 
    	hs(50,hash<const char *>(),eqstr());
struct eqstr{
    bool operator()(const char *s1,const char *s2) const{
        return strcmp(s1,s2) == 0;
    }
}

inline size_t __Stl_hash_string(const char * s)
{
    unsigned long h = 0;
    for( ; *s; ++s)
        h = 5*h + *s;
    return size_t(h);
}
```

## unordered

since C++11

unordered_set, unordered_multiset, unordered_map, unordered_multimap

## 算法

function template

```cpp
template<typename Iterator>
Algorithn(Iterator iter1,Iterator2)
{
	
}
template<typename Iterator,typename Cmp>
Algorithn(Iterator iter1,Iterator2,Cmp comp)
{
	
}
```

算法需要的一切信息必须从Iterator取得。

## 迭代器分类

```cpp
//五种 iterator category
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag: public input_iterator_tag{};
struct bidirectional_iterator_tag: public forward_iterator_tag{};
struct random_access_iterator_tag: public bidirectional_iterator_tag{};

template<typename I>
void display_category(I itr)
{
    typename iterator_traits<I>::iterator_category cagy;
    _display_category(cagy);
}


//test
#include<typeinfo>
#include<list>
cout<<typeid(list<int>::iterator::iterator_category()).name();//output depends on library
cout<<typeid(istreambuf_iterator<input_iterator_tag>()).name();
```



input_iterator ,   output_iterator

## iterator_category对算法的影响

1. ```cpp
   template<class InputIterator>
   inline iterator_traits<InputIterator>::difference_type  
   __distance(InputIterator first,InputIterator last)
   {
       iterator_traits<InputIterator>::difference_type n = 0;
       while(first != last){
           ++first;
           ++n;
       }
       return n;
   }
   
   template<class RandomAccessIterator>
   inline iterator_traits<RandomAccessIterator>::difference_type  
   __distance(RandomAccessIterator first,RandomAccessIterator last)
   {
       return last - first;
   }
   
   //----------------------------------------------
   template<class InputIterator>
   inline iterator_traits<InputIterator>::difference_type
   distance(InputIterator first, InputIterator last)
   {
   	typedef typename iterator_traits<InputIterator>::iterator_category category;
   	return __distance(first,last,category());
   }
   
   
   
   
   
   
   
   __advance()
   {
       
   }
   __advance()
   {
       
   }
   //------------------------------------------
   template <class InputIterator,class Distance>
   inline void advance(InputIterator &i,Distance n)
   {
       __advance(i,n,iterator_category(i));//包装成了小函数，和上方一致
   }
   
   ```

如果是farward_iterator 由于是继承关系，会匹配到input_iterator,所以一定会匹配到某一个版本。

## iterator_category和type traits对算法的影响

```cpp
template<class InputIterator,class OutputIterator>
OutputIterator
copy(InputIterator first,InputIterator last,OutputIterator result)
{
	while(first != last){
        *result = *first;
        ++result;++first;
    }
    return result;
}
```

​                                                                                                  ===>for(;first!=last;..)

​											  -----泛化---->__ copy()---->        强化<RandomAccessIteraot >===>__ copy_d()

copy  ---泛化--> __ copy_dispatch()--特化--->  __copy_t()        强化has trival op = ()   ===>memmove()

​											 ----特化------> __ copy_t()       强化has not-trival op = ()   => __ copy_d()

​		--->特化                    ===>memmove()

​		--->特化                    ===>memmove()

```cpp
reverse_iterator
rbegin()
{
	return reverse_iterator(end());//adapter
}
reverse_iterator
rend()
{
	return reverse_iterator(begin());//adapter
}
```

## 仿函数functor

```cpp
template<class T>
struct plus:public binary_function<T,T,T>{
    T operator()(const T &x, const T&y)const{
        return x + y;
    }
};

template<class T>
struct greater:public binary_function<T, T, bool>{
    bool operator()(const T&x, const T &y)const
    {
        return x > y;
    }
};

template<class T>
struct less:public binary_function<T, T, bool>{
    bool operator()(const T&x, const T &y)const
    {
        return x < y;
    }
};

template<class Arg,class Result>
struct unary_function{
    typedef Arg argument_type;
    typedef Result result_type;
};

template<class Arg1,class Arg2,class Result>
struct binary_function{
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};
```

## Adapter

### bind2nd

```cpp
template<class Operation, class T>
inline binder2nd<Operation> bind2nd(const Operation &op, const T &x){
    //保证编译通过
    typedef typename Operation::second_argument_type arg2_type;
    return binder2nd<Operation>(op,arg2_type(x));
}
template<class Operation>
class binder2nd :public unary_function<typename Operation::first_argument_type,
				typename Operation::result_type>
{
	protected:
    	Operation op;
        typename Operation::second_argument_type &y;
     public:
         binder2nd(const Operation &x, const typename Operation::second_argument_type & y):op(x),value{y}{}
                    
                    
         typename Operation::result_type operator()(const typename Operation::first_argument_type) const{
             return op(x,value);
         }
                    
};
```

### not1

```cpp
template<class Predicate>
inline unary_negate<Predicate> not1(const Predicate &pred){
    return unary_negate<unary_negate>(pred);
}
template<class Predicate>
class unary_negate:public unary_function<typename Predicate::argument_type, bool>
{
    protected:
    	Predicate pred;
    public:
    	explicit unary_negate(const Predicate &x):pred(x){}
    	bool operator()(const typename Predicate::argument_type &x)const{
            return !pred(x);
        }
};
```

### bind

std::bind

1.functions

2.function objects

3.member functions , _1必须是某个object地址   ( _1 是占位符)

4.data members , _1必须是某个object地址

```cpp
double my_divide (double x,double y)
{
    return x/y;
}
struct MyPair{
    double a,b;
    double multiply()
    {
        return a*b;
    }
};
using namespace std::placeholders; //add visibility of _1, _2, _3,...
auto fn_five = bind(my_divide,10,2);
cout<< fn_five() <<'\n';  //5
auto fn_half = bind(my_divide,_1,2);
cout<< fn_half(10) <<'\n';  //5
auto fn_invert = bind(my_divide,_2,_1);
cout<< fn_invert(10,2) <<'\n';  //0.2
auto fn_rounding = bind<int>(my_divide,_1,_2);//retrun int(x/y)
cout<< fn_rounding(10,3) <<'\n';  //3
   
//binding members
MyPair ten_two{10,2};
	//member function 有个argument: this
auto bound_memfn = bind(&MyPair::multiply,_1); //return x.multiply()
cout<< bound_memfn(ten_two) <<'\n'; //20
auto bound_memdata = bind(&MyPair::a,ten_two);
cout<<bound_memdata() <<'\n';//10
auto bound_memdata2 = bind(&MyPair::b,_1);
cout<<bound_memdata2(ten_two) <<'\n'; //2

cout<< count_if(v.cbegin(),v.end(),not1(bind2nd(less<int>(), 50))) <<endl;
auto fn_ = bind(less<int>(), _1, 50);
cout<< count_if(v.cbegin(),v.end(),fn_) <<endl;
cout<< count_if(v.cbegin(),v.end(),bind(less<int>(), _1, 50)) <<endl;
```

## 迭代器适配器
### reverse_iterator

```cpp
reverse_iterator
rbegin()
{
	return reverse_iterator(end());//adapter
}
reverse_iterator
rend()
{
	return reverse_iterator(begin());//adapter
}

template<class Iterator>
class reverse_iterator
{
    protected:
    	Iterator current;
    public:
    	typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    	typedef typename iterator_traits<Iterator>::value value_type;
    	typedef Iterator iterator_type;	//代表正迭代器
    	typedef reverse_iterator<Iterator> self; //代表逆迭代器
    	...
    public:
    	explicit reverse_iterator(iterator_type x):current(x){}
    			reverse_iterator(const self& x):current(x.current){}
    	iterator_type base()const { return current;}//取出对应的正向迭代器
    	reference operator *() const{
            Iterator tmp = current;
            return *--tmp;
        }
    	//逆向迭代器就是对应正向迭代器退一位取值
        pointer operator->()const{
            return &(operator*());
        }
    	self& operator ++(){ --current; return *this;}
    	self& operator --(){ ++current; return *this;}
	    self operator+(difference_type n) const{ return self(current - n);}
    	self operator-(difference_type n) const{ return self(current + n);}
}
```

### inserter

```cpp
template<class Container,class Iterator>
inline insert_iterator<Container>
inserter(Container &x, Iterator i){
    typedef typename Container::iterator iter
    return insert_iterator<Container>(x,i);
}

template<class Container>
class insert_iterator{
    Container *container;
    typename Container::iterator iter;
    public:
    	typedef out_put_iterator_tag iteraetor_category;
    	insert_iterator(Container &x, typename Constainer::iterator i)
            :container(& x),iter(i){}
    	insert_iterator<Container> &
            operator=(const typename Container::value_type &value){
            iter = container->insert(iter,value);
            ++iter;
            return *this;
        }
};
```

## X适配器

### ostream_iterator

```cpp
#include<iteator>myvector;
for(int i =1; i< 10; ++i) myvector.push_back(i*10);
std::vector<int> 
std::ostream_iterator<int> out_it(std::out,",");
std::copy(myvector.begin(),myvector.end(),out_it);
template<class T,class charT= char,class traits =char_traits<charT>>
class ostream_iterator:public iterator<output_iterator_tag,void,void,void,void>{
    basic_ostream<charT,traits> * out_stream;
    const char T *delim;
    public:
    	typedef charT char_type;
    	ostream_iterator(ostream_type & s, const charT *delimiter):out_stream(&s),delime(delimiter){}
    	ostream_iterator(const ostream_iterator<<T,charT,traits>& x):out_stream(x.out_stream),delim(x.delim){}
    ~ostream_iterator(){}
    
    ostream_iterator<T,charT,traits>& operator =(const T& value){
        *out_stream << value;
        if(delime!=0) *out_stream << delim;
        return *this
    }
    ostream_iteraor<T,charT,traits>& operator*()(return *this;)
    ostream_iteraor<T,charT,traits>& operator++()(return *this;)
    ostream_iteraor<T,charT,traits>& operator++(int)(return *this;)
}
```

### istream_iterator

```cpp
#include<iterator>

double value1,value2;
std::istream_iterator<double> eos; //end-of-stream iterator
std::istream_iterator<double> iit(std::cin); // stdin iterator
if(iit != eos){
    value1 =*iit;
}
++iit;
if(iit != eos){
    value2 =*iit;
}
cout<<value1<<" "<<value2;

std::istream_iterator<double> iit(std::cin),eos;//创建对象时已经在读第一个数据
copy(iit,eos,inserter(c,c.begin()));

template<class T,class charT = char,class traits = char_traits<charT>,class Distance = ptrdiff_t>
class istream_iterator:public itaerator<input_iterator_tag,T,Distance, const T*,const T&>
{
    basic_istream<charT,traits> *in_stream;
    T value;
    public:
    ...
    istream_iterator(istream_type &s):in_stream(&s){++*this;}//创建对象时已经在读第一个数据
    
    const T&operator*() const{return value;}
    const T*operator->() const{return &value;}
    istream_iterator<> & operator++(){
        if(in_stream && !(*in_stream >>value))
            in_stream = 0;
        return *this;
    }
}
```



## 一个万用的hash function

```cpp
#include<functional>
class Customer{

};
class CustomerHash{
	std::size_t operator()(const Customer &c)const{
		return hash_val(c.fname,c.lname,c.no);
	}
};

unordered_set<Customer,CustomerHash>custset;

//variadic templates
template<typename T, typename ... Types>
inline void hash_val(size_t& seed,const T & val,const Types &...args){
    hash_combine(seed,val); //2 递归调用,一次次取出元素
    hash_val(seed,args...);
}

template<typename ... Types>
inline size_T hash_Val(const Types &... args){
    size_t seed = 0; // 1 
    hash_val(seed,args...);
    return seed;
}
template<typename T>
inline void hash_Val(size_t& seed,const T & val){
    hash_combine(seed,val); //3
}
template<typename T>
inline void hash_combine(size_t& seed,const T & val){
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    //                             黄金比例
}


class MyString{
    private:
    	char *_data;
    	size_t _len;
    ...
};
namespace std//必须放在std下
{
    template<> struct hash<MyString &s>const noexcept
    {return hash<string>()(string(s.get()));}
    
};
```

## tuple

```cpp

tuple<string,int,int,complex<double>> t; //size 32    why not 28?  
tuple<int,float,string>t1(41,6.3,"nico");// size 12
cout<<"t1:">>get<0>(t1)<<" "<<get<1(t1)<<" "<<get<2>(t1);
auto t2 = make_tuple(22,44,"stacy");

tuple<in,float,string> t3(77,1.1,"more light");
int i1;
float f1;
string s1;
tie(i1,f1,s1) = t3;

template<typename... Values>class tuple;
template<>class tuple<>{};

//tuple<int,float,stirng>  --继承--> tuple<float,stirng>  --继承-->   tuple<stirng> -继承->t uple<>
template<typename Head, typename ... Tail>
class tuple<Head, Tail...>:
		private tuple<Tail...>//递归继承
{
    typedef tuple<Tail...> inherited;
    public:
    	tuple(){}
    	tuple(Head v,Tail... vatil):m_head(v),inherited(vatil...){}
    	typename Head::type head(){return m_head;}
    	inherited & tail(){return *this;} //inherited 是尾部 所以进行了转换
    protected:
    	Head m_head;
}
```

## type traits

G2.9

```cpp
template<class type>
struct __type_traits{
    typedef __true_type this_dummy_member_must_be_first;
    typedef __false_type has_trival_default_constructor;
    typedef __false_type is_POD_type; //Plain Old Data => c struct (not function)
    ....
};
template<>struct __type_traits<int>{
    typedef __true_type has_trival_default_constructor;
    typedef __true_type has_trival_copy_constructor;
    typedef __true_type is_POD_type;
    ...
};

//问
__type_traits<Foo>::has_trival_default_destructor
```

c++11

is_arrat,is_void, is_abstract  ...



### is_void

```cpp
template<typename >
	struct __is_void_helper:public false_type{};
template<typename >
	struct __is_void_helper<void>:public true_type{};
template<typename _Tp>
struct is_void : public __is_void_helper<typename remove_cv<_Tp>::type>::type
{ };

template<typename _Tp>
struct remove_const{
    typedef _Tp type;
};
template<typename _Tp>
struct remove_const<_Tp const>{
    typedef _Tp type;
};
template<typename _Tp>
struct remove_volatile{
    typedef _Tp type;
};
template<typename _Tp>
struct remove_volatile<_Tp volatile>{
    typedef _Tp type;
};
template<typename _Tp>
struct remove_cv
{
    typedef typename
        remove_const<typename remove_volatile<_TP>::type>::type type;
};

```

### is_integral 

```cpp
template<typename _Tp>
	struct is_integral :public __is_integral_helper<typename remove_cv<_Tp>::type>::type {};
template<typename> :struct __is_integral_helper:public false_type{};
template<typename> :struct __is_integral_helper<bool>:public true_type{};
template<typename> :struct __is_integral_helper<char>:public true_type{};
template<typename> :struct __is_integral_helper<signed char>:public true_type{};
template<typename> :struct __is_integral_helper<unsigned char>:public true_type{};
...
```

### is_class,is_union,_is_enum,is_pod

```cpp
template<typename _Tp>
	struct is_enum:public integral_constant<bool,__is_enum(_Tp)> { };
template<typename _Tp>
	struct is_union:public integral_constant<bool,__is_union(_Tp)> { };
template<typename _Tp>
	struct is_class:public integral_constant<bool,__is_class(_Tp)> { };

//__is_enum  __is_union __is_class
//在标准库中没有出现,或许是编译器做的
```

### is_move_assignable

```cpp
template<typename _Tp>
	struct is_move_assignable: public __is_move_assignable_impl<_Tp>{};
//.. 最终也找不到
```



## cout

```cpp
class ostream:virtual public ios
{
    public:
    ostream & operator<<(char c);
    ...
}
class _IO_ostream_withassign:public ostream{
    public :
    	_IO_ostream_withassign & operator = (ostream &);
    	_IO_ostream_withassign & operator = (_IO_ostream_withassign &rhs){
            return operator = (static_cast<ostream&>(rhs));
        };
}
extern _IO_ostream_withassign cout;
```

## moveable元素对速度效能的影响

对于放元素

vector 要倍增差距很大，list、deque差距不大

```cpp
class MyString{
    public:
    	static size_t DCtor ;
    ...
        //move ctor
        MyString (MyString && str) noexcept :_data(str._data),_len(str.len){
        ++MCtor;
        str._len = 0;
        str._data = NULL;
    }
    virtual ~MyString(){
        ++Dtor;
        if(_data){
            delete _data; //浅拷贝会置为NULL 要检查
        }
    }
    MyString & operator = (MyString && str)noexcept{
        ++MAsgn;
        if(this != &str){
            if(_data) delete _data;
            _len = str._len;
            _data = str._data;
            str._len = 0;
        	str._data = NULL;//置为NULL
        }
        return *this;
    }
    
}
size_t MyString::DCtor;
...
```



vector move  =>  swap

string 可以move