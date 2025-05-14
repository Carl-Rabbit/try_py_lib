#include "gtest/gtest.h"

#include "animal/cat.h"
#include "animal/dog.h"

TEST(CatTest, BasicAssertions) {
  Cat cat;
  EXPECT_EQ(cat.make_sound(), "Meow!");
}

TEST(DagTest, BasicAssertions) {
  Dog dog;
  EXPECT_EQ(dog.make_sound(), "Woof!");
}


