#include "gtest/gtest.h"
#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace algorithms {
    template <typename Iterator> void reverse_string(Iterator begin, Iterator end) {
        if (begin == end) {
            return;
        }
        auto left = begin, right = --end;

        while (left != right) {
            std::cout << std::distance(left, right) << "\n";
            auto tmpValue = *left;
            *left = *right;
            *right = tmpValue;
            --right;
            if (left == right) {
                break;
            };
            ++left;
        }
    }
}

TEST(BasicTests, Positive) {
    using namespace algorithms;
    {
        std::string s("Hello");
        reverse_string(s.begin(), s.end());
        EXPECT_TRUE(s == "olleH");
        // std::cout << s << "\n";
    }

    {
        std::string s("");
        reverse_string(s.begin(), s.end());
        EXPECT_TRUE(s == "");
    }

    {
        std::string s("a");
        reverse_string(s.begin(), s.end());
        EXPECT_TRUE(s == "a");
    }
}
