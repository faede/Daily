#include<list>
#include<mutex>
#include<algorithm>
#include<deque>
template<typename T,typename Container = std::deque<T> >
class stack
{
public:
	explicit stack(const Container &);
	explicit stack(Container && = Container());
	template <class Alloc> explicit stack(cosnt Alloc &);
	template <class Alloc> explicit stack(cosnt Container&&,cosnt Alloc &);
	template <class Alloc> explicit stack(stack&&, cosnt Alloc &);
	bool empty(); //不可靠
	size_t size() const; //不可靠
	T& top();
	T const & top() const;
	void push(T const &);
	void push(T &&);
	void pop();
	void swap(stack&&);
};



void do_something(int);
void test()
{
	stack<int> s;
	if (!s.empty()) {
		int const value = s.top();//可能此时已经空了
		s.pop();
		do_something(value);
	}
}