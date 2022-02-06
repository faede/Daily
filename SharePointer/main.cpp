#include <iostream>
#include <utility>
#include <thread>
#include <mutex>
#include <functional>
#include <typeinfo>
#include <cassert> 
#include <memory>
#include <random>

#include "SharePointer.cpp"

int main(){


    // TODO: trans to testclass
    testclass* t = new testclass(5);
    testclass* t2 = new testclass(4);

    // shared_ptr use
    testclass* lib_t = new testclass(5);
    testclass* lib_t2 = new testclass(4);


    #if defined( DEBUG_MODE ) 
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif
    
    Shared_Pointer<testclass> sd_ptr (t, df); // ok de de my deleter 
    std::shared_ptr<testclass> lib_sd_ptr(lib_t, df); // ok de, fail to pass 
    assert(lib_sd_ptr.use_count() == sd_ptr.use_count() && "compare error");

    #if defined( DEBUG_MODE ) 
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif
    auto p2(sd_ptr); // ok de my deleter 
    auto lib_p2(lib_sd_ptr); // ok de
    assert(lib_p2.use_count() == p2.use_count() && "compare error");

    #if defined( DEBUG_MODE ) 
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif
    auto p3 = sd_ptr; // ok de
    auto lib_p3(lib_sd_ptr); //  ok de
    assert(lib_p3.use_count() == p3.use_count() && "compare error");

    
    #if defined( DEBUG_MODE ) 
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif

    #if defined( DEBUG_MODE ) 
       std::cout <<"lib: " << lib_sd_ptr.use_count() << "      my: " << sd_ptr.use_count() << std::endl;
    #endif
    

    Shared_Pointer<testclass> p4_2;
    std::shared_ptr<testclass> lib_p4_2;
    {

    auto p4 = std::move(sd_ptr); //  ok de
    auto lib_p4 = std::move(lib_sd_ptr); // ok de
    #if defined( DEBUG_MODE ) 
       std::cout <<"lib: " << lib_p4.use_count() << "      my: " << p4.use_count() << std::endl;
    #endif
    
    assert(lib_p4.use_count() == p4.use_count() && "compare error");
    
    p4_2 = p4;
    lib_p4_2 = lib_p4;
    }
    
    #if defined( DEBUG_MODE ) 
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif
    assert(lib_p4_2.use_count() == p4_2.use_count() && "compare error");
    
    #if defined( DEBUG_MODE ) 
       std::cout <<"lib: " << lib_p4_2.use_count() << "      my: " << p4_2.use_count() << std::endl;
    #endif



    
    #if defined( DEBUG_MODE ) 
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif

    
    #if defined( DEBUG_MODE ) 
       std::cout <<"lib: " << lib_p4_2.use_count() << "      my: " << p4_2.use_count() << std::endl;
    #endif

    Shared_Pointer<testclass> p5_2;
    std::shared_ptr<testclass> lib_p5_2;
    {

    auto p5 (std::move(p4_2)) ; //  ok de
    auto lib_p5 (std::move(lib_p4_2)); // ok de
    #if defined( DEBUG_MODE ) 
        std::cout <<"lib: " << lib_p5.use_count() << "      my: " << p5.use_count() << std::endl;
    #endif
    
    
    assert(lib_p5.use_count() == p5.use_count() && "compare error");
    
    p5_2 = p5;
    lib_p5_2 = lib_p5;
    }
    #if defined( DEBUG_MODE ) 
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif
    
    #if defined( DEBUG_MODE ) 
        std::cout <<"lib: " << lib_p5_2.use_count() << "      my: " << p5_2.use_count() << std::endl;
    #endif
    assert(lib_p5_2.use_count() == p5_2.use_count() && "compare error");
    



    // don't need
    // Shared_Pointer<testclass> p5 = t2; // ok de 
    // std::shared_ptr<testclass> lib_p5 = lib_t2;
    // assert(lib_p5.use_count() == p5.use_count() && "compare error");

    #if defined( DEBUG_MODE ) 
        std::cout << "------------------------------------------------------------" << std::endl;
    #endif
    //p5 = p4;

    // TODO: 
    //std::cout << "---------------------------------------------------------" << std::endl;
    //auto p6(std::move(sd_ptr), df); 

    // std::cout << "--------------------------7-------------------------------" << std::endl;
    //(*p4).p();
    //std::cout << "--------------------------9-------------------------------" << std::endl;

}