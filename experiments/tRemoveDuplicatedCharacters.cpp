#include "gtest/gtest.h"
#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace algorithms {
  /** 
   * This is O(n^2) algorithm since we cannot use extra memory.
   *
   * @param s 
   */
    void remove_duplicate(std::string &s) {
        size_t N = s.size();
        if (s.size() > 1) {
            for (size_t firstIdx = 0; firstIdx < (N - 1); ++firstIdx) {
                char firstChar = s[firstIdx];
                for (size_t secondIdx = firstIdx + 1; secondIdx < N; ) {
                    if (firstChar == s[secondIdx]) {
                        // Shift the rest of the string by 1. We can reduce the number of shift operations
                        // later
                        size_t len = N - 1;
                        for (size_t idx = secondIdx; idx < len; ++idx) {
                            s[idx] = s[idx + 1];
                        }

                        // Update the size of the string
                        N--;
                    } else {
                      ++secondIdx;
                    }
                }
            }
            s.resize(N);
        }
    }
}

TEST(BasicTests, Positive) {
    using namespace algorithms;
    {
        std::string s("Hello");
        remove_duplicate(s);
        EXPECT_EQ(s, "Helo");
        // std::cout << s << "\n";
    }

    {
        std::string s("aaaaaaaaaa");
        remove_duplicate(s);
        EXPECT_EQ(s, "a");
    }

    {
        std::string s("");
        remove_duplicate(s);
        EXPECT_TRUE(s == "");
    }
}
