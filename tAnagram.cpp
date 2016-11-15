#include "gtest/gtest.h"
#include <array>
#include <string>
#include <vector>

namespace algorithms {
    bool is_anagram_equal(const std::string &x, const std::string &y) {
        std::array<char, 256> mapx{}, mapy{};

        for (auto const ch : x) {
            mapx[ch]++;
        }

        for (auto const ch : y) {
            mapy[ch]++;
        }

        return (mapx == mapy);
    }
}

TEST(BasicTests, Positive) {
    EXPECT_TRUE(algorithms::is_anagram_equal("abd", "dab"));
    EXPECT_FALSE(algorithms::is_anagram_equal("abd", "da"));
    EXPECT_FALSE(algorithms::is_anagram_equal("abd", ""));
}
