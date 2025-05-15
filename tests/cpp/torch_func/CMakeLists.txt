add_executable(_test_torch_func
  test_torch_func.cpp
)

target_link_libraries(_test_torch_func PRIVATE _torch_func gtest_main pybind11::embed)

# 第一个参数是测试的名称，第二个参数是要运行的命令
add_test(NAME TestTorchFunc COMMAND _test_torch_func)
