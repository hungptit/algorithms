#include "UniqueCharacters.hpp"
#include "gtest/gtest.h"

TEST(BasicTests, Positive) {
  using namespace algorithms;
    EXPECT_TRUE(is_unique<bool>(""));
    EXPECT_TRUE(is_unique<bool>("abcd"));

    EXPECT_FALSE(is_unique<bool>("hello"));
    EXPECT_FALSE(is_unique_vector<bool>("hello"));
    
    EXPECT_FALSE( is_unique_map("hello") );
    EXPECT_TRUE( is_unique_map("") );
    EXPECT_TRUE( is_unique_map("abcd") );
}
