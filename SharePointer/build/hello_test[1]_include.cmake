if(EXISTS "/home/zyy/files/GitHub/Daily/SharePointer/build/hello_test[1]_tests.cmake")
  include("/home/zyy/files/GitHub/Daily/SharePointer/build/hello_test[1]_tests.cmake")
else()
  add_test(hello_test_NOT_BUILT hello_test_NOT_BUILT)
endif()
