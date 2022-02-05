add_test( HelloTest.BasicAssertions /home/zyy/files/GitHub/Daily/SharePointer/build/hello_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( HelloTest.BasicAssertions PROPERTIES WORKING_DIRECTORY /home/zyy/files/GitHub/Daily/SharePointer/build)
set( hello_test_TESTS HelloTest.BasicAssertions)
