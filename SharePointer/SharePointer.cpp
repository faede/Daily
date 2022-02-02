#include <iostream>
#include <utility>

template<typename T>
class Shared_Pointer;
// TODO : lock
class ControlBlock{
private:
    int _reference_count;
    int _weak_reference_count;
    // TODO:
public:
    ControlBlock() : _reference_count(0), _weak_reference_count(0) {}
    void increase_reference(){
        _reference_count++;
    }
    void decrease_reference(){
        _reference_count--;
    }
    int get_reference(){
        return _reference_count;
    }
    void print_reference(){
        std::cout << "ref_count is: " << _reference_count << std::endl;
    }
    void check_reference(){
        if(_reference_count == 0){
            std::cout <<"need to be delete"<<std::endl;
        }
    }
public:
    ~ControlBlock(){

    }
};


template<typename T>
Shared_Pointer<T> & make_Shared_Pointer(T && data){
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
    Shared_Pointer();
    // Copy constructor from new.
    Shared_Pointer(T * data){
        _data = data;
        _controlblock = new ControlBlock();
        _controlblock->increase_reference(); // set it to 1
        //this->
        std::cout << "do a copy  constructor form new" << std::endl;
        _controlblock->print_reference();
    }
    // Copy assignment operator from new.
    Shared_Pointer<T> & operator=(const T * data)
    {
        _data = data;
        _controlblock = new ControlBlock();
        _controlblock->increase_reference();

        std::cout << "do a copy  assignment operator form new" << std::endl;
        
        _controlblock->print_reference();
        return *this;
    }


    // Copy constructor.
    Shared_Pointer(const Shared_Pointer<T>& other)
        : _data(other._data), _controlblock(other._controlblock)
    {
        _controlblock->increase_reference();
        std::cout << "do a copy constructor" << std::endl;

        _controlblock->print_reference();
    }
    // Copy assignment operator.
    Shared_Pointer<T> & operator=(const Shared_Pointer<T>& other)
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
    Shared_Pointer(Shared_Pointer<T> && other) noexcept
        : _data(nullptr), _controlblock(nullptr)
    {
        _data = other._data;
        _controlblock = other._controlblock;
        other._data = nullptr;
        other._controlblock = nullptr;
        

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
    T & operator* (){
        return *(this->_data);
    }   

    ~Shared_Pointer(){
        if(_controlblock == nullptr){
            // to fix bug
            return ;
        }
        std::cout << "before delete :" << std::endl;
        _controlblock->print_reference();

        _controlblock->decrease_reference(); // by move shouldn't be decreased
        if(_controlblock->get_reference() == 0){
            delete _controlblock;
            std::cout << "shared pointer has been deleted" << std::endl;
        }
        else 
            _controlblock->print_reference();

        std::cout << std::endl;
    }
};

int main(){
    int a = 5;
    Shared_Pointer<int> sd_ptr = & a;
    auto p2(sd_ptr);
    auto p3 = sd_ptr;
    auto p4 = std::move(sd_ptr);
    std::cout << *p4 << std::endl;
    //new Shared_Pointer()
}