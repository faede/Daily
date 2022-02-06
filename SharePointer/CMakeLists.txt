cmake_minimum_required(VERSION 3.14)
project(shared_pointer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(SharePointer Shared_Pointer.cpp)

add_executable(shared_main main.cpp)
target_link_libraries(shared_main SharePointer)


cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



add_executable(shared_ptr_test "")

target_sources(shared_ptr_test
  PRIVATE 
    test.cpp
)

target_link_libraries(shared_ptr_test
  PRIVATE 
    SharePointer
    gtest_main
)

enable_testing(
  #NAME google_test
  #COMMAND $<TARGET_FILE:shared_ptr_test>

)

include(GoogleTest)
# gtest_discover_tests(shared_ptr_test)




