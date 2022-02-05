#include <iostream>
#include <utility>
#include <thread>
#include <mutex>
#include <functional>
#include <typeinfo>
#include <cassert> 
#include <memory>
#include <random>

template<typename T>
class Shared_Pointer;
// TODO : lock


class ControlBlock{
private:
    long _reference_count;
    long _weak_reference_count;
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
    long get_reference() noexcept
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
    long check_reference(T __data) noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        _reference_count--;
        if(_reference_count == 0){
            std::cout <<"need to be delete"<<std::endl;
            delete __data;
            this->~ControlBlock();
            return 1; // 1 to deleted
        }
        
        return 0; // 0 to exist 
    }
public:
    ~ControlBlock(){
        std::cout << "control block free, deleter:" << std::endl;
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
    int id ;
public:
    Shared_Pointer() noexcept
    {
        id = std::rand();
        
        _data = nullptr;
        _controlblock = nullptr;
    }
    
    // Copy constructor from new.
    Shared_Pointer(T * data, std::function<void()> deleter = NULL) noexcept
    {
        id = std::rand();
        std::cout << "id -----> " << id << " construct " << std::endl;
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
        id = std::rand();
        std::cout << "id -----> " << id << " construct " << std::endl;

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
        id = std::rand();
        std::cout << "id -----> " << id << " construct " << std::endl;

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
        id = std::rand();
        std::cout << "id -----> " << id << " construct " << std::endl;

        _controlblock->increase_reference();
        std::cout << "do a copy constructor" << std::endl;

        _controlblock->print_reference();
    }
    
    // Copy assignment operator.
    // we need to redefine
    // we can't change bind, we onlu create
    Shared_Pointer<T> & operator=(const Shared_Pointer<T>& other) noexcept
    {
        assert(_data == nullptr && "error, can't change bind");
        id = std::rand();
        std::cout << "id -----> " << id << " construct " << std::endl;

        if(this != &other){
            // _controlblock->decrease_reference();
            other._controlblock->increase_reference();

            _data = other._data;
            _controlblock = other._controlblock;

            //_controlblock->increase_reference();
            std::cout << "do a copy  assignment operator" << std::endl;
        }
        _controlblock->print_reference();
        return *this;
    }

    // Move constructor.
    Shared_Pointer(Shared_Pointer<T> && other, std::function<void()> deleter = NULL) noexcept
        : _data(other._data), _controlblock(other._controlblock)
    {
        id = std::rand();
        std::cout << "id -----> " << id << " construct " << std::endl;

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
        id = std::rand();
        std::cout << "id -----> " << id << " construct " << std::endl;

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
        id = std::rand();
        std::cout << "id -----> " << id << " construct " << std::endl;

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

    long use_count() noexcept
    {
        return _controlblock->get_reference();
    }

    ~Shared_Pointer() noexcept
    {
        std::cout << "id -----> " << id << " destruct " << std::endl;
        if(_controlblock != nullptr){
            _controlblock->check_reference(_data);
        }
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
    // TODO: trans to test
    test* t = new test(5);
    test* t2 = new test(4);

    // shared_ptr use
    test* lib_t = new test(5);
    test* lib_t2 = new test(4);


    std::cout << "--------------------------1-------------------------------" << std::endl;
    Shared_Pointer<test> sd_ptr (t, df); // error de
    std::shared_ptr<test> lib_sd_ptr(lib_t, df); // ok de
    assert(lib_sd_ptr.use_count() == sd_ptr.use_count() && "compare error");

    std::cout << "--------------------------2-------------------------------" << std::endl;
    auto p2(sd_ptr); // ok de
    auto lib_p2(lib_sd_ptr); // ok de
    assert(lib_p2.use_count() == p2.use_count() && "compare error");

    std::cout << "--------------------------3-------------------------------" << std::endl;
    auto p3 = sd_ptr; // ok de
    auto lib_p3(lib_sd_ptr); //  ok de
    assert(lib_p3.use_count() == p3.use_count() && "compare error");

    std::cout << "--------------------------4-------------------------------" << std::endl;



    std::cout <<"lib: " << lib_sd_ptr.use_count() << "      my: " << sd_ptr.use_count() << std::endl;
    

    Shared_Pointer<test> p4_2;
    std::shared_ptr<test> lib_p4_2;
    {

    auto p4 = std::move(sd_ptr); //  ok de
    auto lib_p4 = std::move(lib_sd_ptr); // ok de

    std::cout <<"lib: " << lib_p4.use_count() << "      my: " << p4.use_count() << std::endl;
    assert(lib_p4.use_count() == p4.use_count() && "compare error");
    
    p4_2 = p4;
    lib_p4_2 = lib_p4;
    }
     std::cout << "--------------------------4 - mid -------------------------------" << std::endl;
    assert(lib_p4_2.use_count() == p4_2.use_count() && "compare error");
    std::cout <<"lib: " << lib_p4_2.use_count() << "      my: " << p4_2.use_count() << std::endl;




    std::cout << "--------------------------5-------------------------------" << std::endl;
    std::cout <<"lib: " << lib_p4_2.use_count() << "      my: " << p4_2.use_count() << std::endl;
    

    Shared_Pointer<test> p5_2;
    std::shared_ptr<test> lib_p5_2;
    {

    auto p5 (std::move(p4_2)) ; //  ok de
    auto lib_p5 (std::move(lib_p4_2)); // ok de

    std::cout <<"lib: " << lib_p5.use_count() << "      my: " << p5.use_count() << std::endl;
    assert(lib_p5.use_count() == p5.use_count() && "compare error");
    
    p5_2 = p5;
    lib_p5_2 = lib_p5;
    }
    std::cout << "-------------------------- 5 - mid -------------------------------" << std::endl;
    assert(lib_p5_2.use_count() == p5_2.use_count() && "compare error");
    std::cout <<"lib: " << lib_p5_2.use_count() << "      my: " << p5_2.use_count() << std::endl;



    // don't need
    // Shared_Pointer<test> p5 = t2; // ok de 
    // std::shared_ptr<test> lib_p5 = lib_t2;
    // assert(lib_p5.use_count() == p5.use_count() && "compare error");

    std::cout << "--------------------------6-------------------------------" << std::endl;
    //p5 = p4;

    // TODO: 
    //std::cout << "---------------------------------------------------------" << std::endl;
    //auto p6(std::move(sd_ptr), df); 

    std::cout << "--------------------------7-------------------------------" << std::endl;
    //(*p4).p();
    std::cout << "--------------------------9-------------------------------" << std::endl;

}