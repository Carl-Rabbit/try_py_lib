add_executable(_test_animal
  test_animal.cpp
)

target_link_libraries(_test_animal PRIVATE _animal GTest::gtest_main)

# 第一个参数是测试的名称，第二个参数是要运行的命令
add_test(NAME TestAnimal COMMAND _test_animal)
