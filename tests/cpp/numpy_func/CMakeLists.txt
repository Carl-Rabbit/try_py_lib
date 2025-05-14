add_executable(_test_numpy_func
  test_numpy_func.cpp
)

target_link_libraries(_test_numpy_func PRIVATE _numpy_func GTest::gtest_main pybind11::embed)

# 第一个参数是测试的名称，第二个参数是要运行的命令
add_test(NAME TestNumpyFunc COMMAND _test_numpy_func)
