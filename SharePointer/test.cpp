#include <memory>

#include <gtest/gtest.h>
#include "SharePointer.cpp"
// Demonstrate some basic assertions.

int main(int argc, char ** argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(shared_ptr, copy_constructer) {

  testclass* t = new testclass(5);
  // shared_ptr use
  testclass* lib_t = new testclass(5);
  Shared_Pointer<testclass> sd_ptr (t); 
  std::shared_ptr<testclass> lib_sd_ptr(lib_t);
  
  ASSERT_EQ(lib_sd_ptr.use_count() , sd_ptr.use_count());
}

TEST(shared_ptr, copy_constructer_deleter) {

  testclass* t = new testclass(5);
  // shared_ptr use
  testclass* lib_t = new testclass(5);
  Shared_Pointer<testclass> sd_ptr (t, df); 
  std::shared_ptr<testclass> lib_sd_ptr(lib_t, df); 
  
  ASSERT_EQ(lib_sd_ptr.use_count() , sd_ptr.use_count());
}

TEST(shared_ptr, copy_assign){
  testclass* t = new testclass(5);
  // shared_ptr use
  testclass* lib_t = new testclass(5);
  Shared_Pointer<testclass> sd_ptr (t); 
  std::shared_ptr<testclass> lib_sd_ptr(lib_t); 

  auto p = sd_ptr; 
  auto lib_p(lib_sd_ptr); 
  
  ASSERT_EQ(lib_p.use_count() ,p.use_count() );
}

TEST(shared_ptr, copy_assign_with_deleter){
  testclass* t = new testclass(5);
  // shared_ptr use
  testclass* lib_t = new testclass(5);
  Shared_Pointer<testclass> sd_ptr (t, df); 
  std::shared_ptr<testclass> lib_sd_ptr(lib_t, df); 

  auto p = sd_ptr; 
  auto lib_p(lib_sd_ptr); 
  
  ASSERT_EQ(lib_p.use_count() ,p.use_count() );
}

TEST(shared_ptr, move){
    testclass* t = new testclass(5);
    // shared_ptr use
    testclass* lib_t = new testclass(5);
    Shared_Pointer<testclass> p_2;
    std::shared_ptr<testclass> lib_p_2;
    Shared_Pointer<testclass> sd_ptr (t); 
    std::shared_ptr<testclass> lib_sd_ptr(lib_t); 
    {

    auto p = std::move(sd_ptr); 
    auto lib_p = std::move(lib_sd_ptr); 
    
    ASSERT_EQ(lib_p.use_count(), p.use_count());
    
    p_2 = p;
    lib_p_2 = lib_p;
    }
    
    ASSERT_EQ(lib_p_2.use_count(),p_2.use_count());
}

TEST(shared_ptr, move_with_deleter){
    testclass* t = new testclass(5);
    // shared_ptr use
    testclass* lib_t = new testclass(5);

    Shared_Pointer<testclass> p_2;
    std::shared_ptr<testclass> lib_p_2;

    Shared_Pointer<testclass> sd_ptr (t,df);
    std::shared_ptr<testclass> lib_sd_ptr(lib_t,df); 

    {

    auto p = std::move(sd_ptr); 
    auto lib_p = std::move(lib_sd_ptr); 
    
    ASSERT_EQ(lib_p.use_count(), p.use_count());
    
    p_2 = p;
    lib_p_2 = lib_p;
    }
    
    ASSERT_EQ(lib_p_2.use_count(),p_2.use_count());
}