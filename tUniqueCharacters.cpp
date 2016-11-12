#include "gtest/gtest.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct FirstSolution {
    bool operator()(const std::string &s) {
        std::array<unsigned int, 256>
            map{}; // Will set all value to 0 -> Guarantee by C++ standard.
        for (unsigned char ch : s) {
            map[ch]++;
        }

        for (auto const val : map) {
            if (val > 1) {
                return false;
            }
        }
        return true;
    }
};

struct SecondSolution {
    bool operator()(const std::string &s) {
        std::unordered_map<char, unsigned int> map;
        map.reserve(256);
        for (unsigned char ch : s) {
            map[ch]++;
        }

        for (auto const &item : map) {
          if (item.second > 1) {
                return false;
            }
        }
        return true;
    }
};

template <typename F> bool is_unique(const std::string &s) {
    F f;
    return f(s);
}

template <typename Solution> void test() {
    EXPECT_TRUE(is_unique<Solution>("abcde"));
    EXPECT_TRUE(is_unique<Solution>(""));
    EXPECT_FALSE(is_unique<Solution>("aaaaaa"));
}

TEST(BasicTests, Positive) {
    test<FirstSolution>();
    test<SecondSolution>();
}
