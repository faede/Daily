#include <iostream>
#include <utility>
#include <thread>
#include <mutex>
#include <functional>
#include <typeinfo>

template<typename T>
class Shared_Pointer;
// TODO : lock


class ControlBlock{
private:
    int _reference_count;
    int _weak_reference_count;
    std::mutex _r_mutex;
    std::function<void()> _deleter;
    // TODO:
public:
    
    static void de(){
        std::cout << "this is a deleter" << std::endl;
    }

    template<typename Arg = void>
    ControlBlock(std::function<void()> deleter = de) noexcept
        : _reference_count(0), _weak_reference_count(0), _deleter(deleter)
    {
       // _deleter();
    }

    // static fun -> function arg -> init list ->  func define
    void increase_reference() noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        _reference_count++;
    }
    void decrease_reference() noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        _reference_count--;
    }
    int get_reference() noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        return _reference_count;
    }
    void print_reference() noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        std::cout << "ref_count is: " << _reference_count << std::endl;
    }

    void set_deleter(std::function<void()> deleter)noexcept
    {
        _deleter = deleter;
    }

    template<typename T>
    int check_reference(T __data) noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        if(_reference_count == 0){
            std::cout <<"need to be delete"<<std::endl;
            delete __data;
            return 0; // 0 to deleted
        }
        
        return 1; // 1 to exist 
    }
public:
    ~ControlBlock(){
        std::cout << "deleter:" << std::endl;
        _deleter();
    }
};


template<typename T>
Shared_Pointer<T> & make_Shared_Pointer(T && data) noexcept
{
    // error
    auto res = Shared_Pointer<T>(data);
    return res;
}

template<typename T>
class Shared_Pointer
{
private:
    T * _data;
    ControlBlock * _controlblock;
public:
    Shared_Pointer() noexcept
    {
        _data = nullptr;
        _controlblock = nullptr;
    }
    
    // Copy constructor from new.
    Shared_Pointer(T * data, std::function<void()> deleter = NULL) noexcept
    {
        _data = data;
        _controlblock = new ControlBlock();
        _controlblock->increase_reference(); // set it to 1
        std::cout << "do a copy  constructor form new" << std::endl;
        _controlblock->print_reference();
    }

    // Copy constructor from new with special deleter.
    template<typename F>
    Shared_Pointer(T * data, F && f) noexcept
    {   
        std::cout << "This is a shared_ptr with special deleter" << std::endl;
        // Create a function f with bounded parameters 
        std::function<decltype(f(data))()> func = std::bind(std::forward<F>(f),
                                                         std::forward<T *>(data));
        // Wrap function func into void function
        std::function<void()> wrapper_func = [func]() {
            (func)(); 
        };        
        _data = data;
        _controlblock = new ControlBlock(wrapper_func);
        _controlblock->increase_reference(); // set it to 1
        std::cout << "do a copy  constructor form new" << std::endl;
        _controlblock->print_reference();
    }
    
    // Copy assignment operator from new.
    Shared_Pointer<T> & operator=(const T * data) noexcept
    {
        _data = data;
        _controlblock = new ControlBlock();
        _controlblock->increase_reference();

        std::cout << "do a copy  assignment operator form new" << std::endl;
        
        _controlblock->print_reference();
        return *this;
    }


    // Copy constructor.
    Shared_Pointer(const Shared_Pointer<T>& other, std::function<void()> deleter = NULL) noexcept
        : _data(other._data), _controlblock(other._controlblock)
    {
        _controlblock->increase_reference();
        std::cout << "do a copy constructor" << std::endl;

        _controlblock->print_reference();
    }
    
    // Copy assignment operator.
    Shared_Pointer<T> & operator=(const Shared_Pointer<T>& other) noexcept
    {
        if(this != other){
            _data = other._data;
            _controlblock = other._controlblock;
            _controlblock->increase_reference();
            std::cout << "do a copy  assignment operator" << std::endl;
        }
        _controlblock->print_reference();
        return *this;
    }

    // Move constructor.
    Shared_Pointer(Shared_Pointer<T> && other, std::function<void()> deleter = NULL) noexcept
        : _data(other._data), _controlblock(other._controlblock)
    {
        other._data = nullptr;
        other._controlblock = nullptr;
        

        std::cout << "do a Move constructor" << std::endl;
        _controlblock->print_reference();
    }

    // TODO:
    // This is wrong
    template<typename F>
    Shared_Pointer(Shared_Pointer<T> && other, F && f) noexcept
        : _data(other._data), _controlblock(other._controlblock)
    {   
        other._data = nullptr;
        other._controlblock = nullptr;
        std::cout << "This is a shared_ptr with special deleter" << std::endl;
        // Create a function f with bounded parameters 
        std::function<decltype(f(_data))()> func = std::bind(std::forward<F>(f),
                                                         std::forward<T *>(_data));
        // Wrap function func into void function
        std::function<void()> wrapper_func = [func]() {
            (func)(); 
        };        
        _controlblock->set_deleter(wrapper_func);
        
        std::cout << "do a Move constructor" << std::endl;
        _controlblock->print_reference();
    }
    // Move assignment operator.
    Shared_Pointer<T> & operator=(Shared_Pointer<T>&& other) noexcept
    {
        if(this != other){
            _data = other._data;
            _controlblock = other._controlblock;
            other->_data = nullptr;
            other->_controlblock = nullptr;
        }
        std::cout << "do a Move assignment operator" << std::endl;
        _controlblock->print_reference();
        return *this;
    }

    // Operator overload * .
    T & operator* () noexcept
    {
        return *(this->_data);
    }   

    ~Shared_Pointer() noexcept
    {
        if(_controlblock == nullptr){
            // TODO: fix bug
            return ;
        }
        std::cout << "before delete :" << std::endl;
        _controlblock->print_reference();

        _controlblock->decrease_reference(); // by move shouldn't be decreased

        
        if(_controlblock == nullptr){
            // TODO: fix bug
            return ;
        }
        _controlblock->print_reference();
        
        
        // _controlblock->check_reference(_data);
        // TODO:
        // lock
        if(_controlblock->get_reference() == 0){
            delete _controlblock;
        }
        
        std::cout << std::endl;
    }
};

class test{
    int a;
public:
    test() : a(0) {}
    test(int a) : a(a) {}
    void p(){
        std::cout << a << std::endl;
    }
    ~test(){
        std::cout << "test has been freed " << std::endl;
    }
};

int df(test *){
    std::cout << "my deleter" << std::endl;
}   
int main(){
    //int a = 5;
    test* t = new test(5);



    std::cout << "-------------------------------" << std::endl;
    Shared_Pointer<test> sd_ptr (t,df);
    std::cout << "-------------------------------" << std::endl;
    auto p2(sd_ptr);
    std::cout << "-------------------------------" << std::endl;
    auto p3 = sd_ptr;
    std::cout << "-------------------------------" << std::endl;
    auto p4 = std::move(sd_ptr);

    // TODO: 
    // std::cout << "-------------------------------" << std::endl;
    // auto p5(std::move(sd_ptr),df); 

    std::cout << "-------------------------------" << std::endl;
    (*p4).p();
    std::cout << "-------------------------------" << std::endl;
    //new Shared_Pointer()
}