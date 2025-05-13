#include "gtest/gtest.h"

#include "func/func.hpp"

// 一个简单的示例测试套件和测试用例
TEST(AddTest, BasicAssertions) {
  EXPECT_EQ(cpp_add_numbers(20, 22), 42);
}

TEST(HelloTest, AnotherAssertion) {
  EXPECT_NE(5, 4); // 期望两个值不相等
}

// 如果你没有链接 GTest::gtest_main，你需要自己提供 main 函数：
// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
