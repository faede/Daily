#pragma once

#include <iostream>
#include <utility>
#include <thread>
#include <mutex>
#include <functional>
#include <typeinfo>
#include <cassert> 
#include <memory>
#include <random>

// #define DEBUG_MODE


template<typename T>
class Shared_Pointer;
// TODO : lock
template<typename T>
class Weak_Ponter;

class ControlBlock{
private:
    long _reference_count;
    long _weak_reference_count; // TODO: 
    std::mutex _r_mutex;
    std::function<void()> _deleter;
    // TODO:
public:
    
    static void de(){
        #if defined( DEBUG_MODE ) 
            std::cout << "this is a deleter" << std::endl;
        #endif
    }

    template<typename Arg = void>
    ControlBlock(std::function<void()> deleter = de) noexcept
        : _reference_count(1), _weak_reference_count(0), _deleter(deleter)
    {
       // _deleter();
    }

    // static fun -> function arg -> init list ->  func define
    void increase_reference() noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        _reference_count++;
    }
    void increase_weak_reference() noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        _weak_reference_count++;
    }
    long get_reference() noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        return _reference_count;
    }
    void print_reference() noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        #if defined( DEBUG_MODE ) 
            std::cout << "ref_count is: " << _reference_count << std::endl;
        #endif        
    }

    void set_deleter(std::function<void()> deleter)noexcept
    {
        _deleter = deleter;
    }

    template<typename T>
    void check_reference(T __data) noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        _reference_count--;
        if(_reference_count == 0 && _weak_reference_count == 0){
            #if defined( DEBUG_MODE ) 
            std::cout <<"need to be delete"<<std::endl;
            #endif              
            // delete __data;
            // _deleter();
            this->~ControlBlock();
        }
    }

    template<typename T>
    void check_weak_reference(T __data) noexcept
    {
        std::lock_guard<std::mutex> lock(_r_mutex);
        _weak_reference_count--;
        if(_reference_count == 0 && _weak_reference_count == 0){
            #if defined( DEBUG_MODE ) 
            std::cout <<"weak : need to be delete"<<std::endl;
            #endif             
            delete __data;
            this->~ControlBlock();
        }
    }
protected:
    ~ControlBlock(){
        #if defined( DEBUG_MODE ) 
            std::cout << "control block free, deleter:" << std::endl;
        #endif        
        _deleter();
    }
};

template<typename T>
class Weak_Ponter{
    T * _wk_data;
    ControlBlock * _wk_controlblock;
    //Shared_Pointer<T> * bind_pointer;

    Weak_Ponter(Shared_Pointer<T> sd_ptr){
        _wk_data = sd_ptr._data;
        _wk_controlblock = sd_ptr._controlblock;
        _wk_controlblock->increase_reference();
        //bind_pointer = sd_ptr;
    }

    bool expired(){
        if(_wk_controlblock == nullptr){
            return 1;
        }
        return _wk_controlblock->get_reference() == 0;
    }

    void lock(){
        Shared_Pointer<T> rt();
        rt._data = _wk_data;
        rt._controlblock = _wk_controlblock;
        _wk_controlblock->increase_reference();
        //return Shared_Pointer<T>
        // TODO
        return ;
    }
    ~Weak_Ponter(){
        if(_wk_controlblock != nullptr){
            _wk_controlblock->check_weak_reference(_wk_data);
        }
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
friend  class Weak_Pointer;
private:
    T * _data;
    ControlBlock * _controlblock;
    int id ;
/*protected:
    Shared_Pointer<T> & get_shared_ptr(){
        auto rt = Shared_Pointer();
        rt._data = _data;
        rt._controlblock = _controlblock;
        _controlblock->increase_reference();
        return rt;
    }*/


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
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " construct " << std::endl;
        #endif 
        _data = data;
        _controlblock = new ControlBlock();
        #if defined( DEBUG_MODE ) 
            std::cout << "do a copy  constructor form new" << std::endl;
        #endif
        _controlblock->print_reference();
    }

    // Copy constructor from new with special deleter.
    template<typename F>
    Shared_Pointer(T * data, F && f) noexcept
    { 
        id = std::rand();
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " construct " << std::endl;
            std::cout << "This is a shared_ptr with special deleter" << std::endl;
        #endif     
        // Create a function f with bounded parameters 
        std::function<decltype(f(data))()> func = std::bind(std::forward<F>(f),
                                                         std::forward<T *>(data));
        // Wrap function func into void function
        std::function<void()> wrapper_func = [func]() {
            (func)(); 
        };        
        _data = data;
        _controlblock = new ControlBlock(wrapper_func);
        #if defined( DEBUG_MODE ) 
            std::cout << "do a copy  constructor form new" << std::endl;
        #endif
        _controlblock->print_reference();
    }
    
    // Copy assignment operator from new.
    Shared_Pointer<T> & operator=(const T * data) noexcept
    {
        id = std::rand();
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " construct " << std::endl;
        #endif     
        _data = data;
        _controlblock = new ControlBlock();
        _controlblock->increase_reference();        
        #if defined( DEBUG_MODE ) 
            std::cout << "do a copy  assignment operator form new" << std::endl;
        #endif
        _controlblock->print_reference();
        return *this;
    }


    // Copy constructor.
    Shared_Pointer(const Shared_Pointer<T>& other, std::function<void()> deleter = NULL) noexcept
        : _data(other._data), _controlblock(other._controlblock)
    {
        id = std::rand();
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " construct " << std::endl;
        #endif
        _controlblock->increase_reference();
        #if defined( DEBUG_MODE ) 
            std::cout << "do a copy constructor" << std::endl;
        #endif
        _controlblock->print_reference();
    }
    
    // Copy assignment operator.
    // we need to redefine
    // we can't change bind, we onlu create
    Shared_Pointer<T> & operator=(const Shared_Pointer<T>& other) noexcept
    {
        assert(_data == nullptr && "error, can't change bind");
        id = std::rand();
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " construct " << std::endl;
        #endif
        if(this != &other){
            other._controlblock->increase_reference();

            _data = other._data;
            _controlblock = other._controlblock;
            #if defined( DEBUG_MODE ) 
            std::cout << "do a copy  assignment operator" << std::endl;
            #endif            
        }
        _controlblock->print_reference();
        return *this;
    }

    // Move constructor.
    Shared_Pointer(Shared_Pointer<T> && other, std::function<void()> deleter = NULL) noexcept
        : _data(other._data), _controlblock(other._controlblock)
    {
        id = std::rand();        
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " construct " << std::endl;
        #endif 
        other._data = nullptr;
        other._controlblock = nullptr;
        #if defined( DEBUG_MODE ) 
            std::cout << "do a Move constructor" << std::endl;
        #endif       
        _controlblock->print_reference();
    }

    // TODO:
    // This is wrong
    template<typename F>
    Shared_Pointer(Shared_Pointer<T> && other, F && f) noexcept
        : _data(other._data), _controlblock(other._controlblock)
    {   
        id = std::rand();
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " construct " << std::endl;
        #endif
        other._data = nullptr;
        other._controlblock = nullptr;
        #if defined( DEBUG_MODE ) 
            std::cout << "This is a shared_ptr with special deleter" << std::endl;
        #endif        
        // Create a function f with bounded parameters 
        std::function<decltype(f(_data))()> func = std::bind(std::forward<F>(f),
                                                         std::forward<T *>(_data));
        // Wrap function func into void function
        std::function<void()> wrapper_func = [func]() {
            (func)(); 
        };        
        _controlblock->set_deleter(wrapper_func);        
        #if defined( DEBUG_MODE ) 
            std::cout << "do a Move constructor" << std::endl;
        #endif        
        _controlblock->print_reference();
    }
    // Move assignment operator.
    Shared_Pointer<T> & operator=(Shared_Pointer<T>&& other) noexcept
    {
        id = std::rand();
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " construct " << std::endl;
        #endif
        if(this != other){
            _data = other._data;
            _controlblock = other._controlblock;
            other->_data = nullptr;
            other->_controlblock = nullptr;
        }
        #if defined( DEBUG_MODE ) 
            std::cout << "do a Move assignment operator" << std::endl;
        #endif        
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
        #if defined( DEBUG_MODE ) 
            std::cout << "id -----> " << id << " destruct " << std::endl;
        #endif
        
        if(_controlblock != nullptr){
            _controlblock->check_reference(_data);
        }
    }
};

class testclass{
public:
    int a;
    int id;

    testclass() : a(0) {
        id = rand();
        #if defined( DEBUG_MODE ) 
            std::cout << "testclass : id -------> "<< id <<" testclass has been cons " << std::endl;
        #endif        
    }
    testclass(int a) : a(a) {
        id = rand();
        #if defined( DEBUG_MODE ) 
           std::cout << "testclass : id -------> "<< id <<" testclass has been cons " << std::endl;
        #endif
    }
    void p(){
        std::cout << a << std::endl;
    }
    ~testclass(){
        #if defined( DEBUG_MODE ) 
           std::cout << "testclass : id -------> "<< id <<" testclass has been freed " << std::endl;
        #endif        
    }
};
static int i =0;
int df(testclass * t){    
    i++;
    #if defined( DEBUG_MODE ) 
        std::cout << "free testclass : "<< t->id << " my deleter: " << i<< std::endl;
    #endif
        delete t;
    return 0;
}  