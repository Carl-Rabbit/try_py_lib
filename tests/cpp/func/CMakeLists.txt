add_executable(_test_add
  test_add.cpp
)

target_link_libraries(_test_add PRIVATE _core GTest::gtest_main)

# 第一个参数是测试的名称，第二个参数是要运行的命令
add_test(NAME TestAdd COMMAND _test_add)
