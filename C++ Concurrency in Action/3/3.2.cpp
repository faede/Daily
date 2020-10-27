#include<list>
#include<mutex>
#include<algorithm>

class some_data
{
	int a;
	std::string b;
public:
	void do_something();
};
class data_wrapper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func) {
		std::lock_guard<std::mutex> l(m);
		func(data);
	}
};
some_data * unprotected;
void malicious_function(some_data & protected_data) {
	unprotected = &protected_data;
}
data_wrapper x;
void foo() {
	x.process_data(malicious_function);//恶意函数
	unprotected->do_something();
}
//不要将受保护数据的指针和引用传递到锁的范围之外，无论是通过函数中返回它们、将其放在外部可见的内存中，还是作为参数传递给用户提供的函数。