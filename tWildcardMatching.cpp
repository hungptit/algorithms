#include "gtest/gtest.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

template <typename FirstIterator, typename SecondIterator>
bool is_matched(FirstIterator sbegin, FirstIterator send, SecondIterator pbegin,
                SecondIterator pend) {
    if (pbegin == pend) {
        if (sbegin == send) {
            return true;
        } else {
            return false;
        }
    }

    if (std::all_of(pbegin, pend, [](const char value) { return value == '*'; })) {
        return true;
    }

    // If input is empty then we need to handle these cases differently.
    if (sbegin == send) {
        return false;
    }

    auto sit = sbegin;
    auto pit = pbegin;

    while (true) {
        const char pch = *pit;
        if (pch == '*') {
            if (std::distance(pit, pend) == 1) {
                return true;
            } else {
                // Now call this function recursively to check that two ranges are matched.
                ++pit;
                for (auto currentIt = sit; currentIt != send; ++currentIt) {
                    if (is_matched(currentIt, send, pit, pend)) {
                        return true;
                    }
                }
                return false;
            }
        } else if (pch != '?') {
            if ((*sit) != (*pit)) {
                return false;
            }
        }

        // Move next
        ++sit;
        ++pit;

        // Check the stopping conditions.
        if (sit == send) {
            return is_matched(sit, send, pit, pend);
        }

        if (pit == pend) {
            return is_matched(sit, send, pit, pend);
        }
    }
}

bool test(const std::string &s, const std::string &pattern) {
    return is_matched(s.cbegin(), s.cend(), pattern.cbegin(), pattern.cend());
}

TEST(BasicTests, Positive) {
    EXPECT_TRUE(test("", "******"));
    EXPECT_TRUE(test("", ""));
    EXPECT_FALSE(test("", "a"));

    EXPECT_FALSE(test("a", ""));
    EXPECT_TRUE(test("a", "?"));
    EXPECT_TRUE(test("abcd", "a?cd"));
    EXPECT_TRUE(test("aa", "a*"));
    EXPECT_TRUE(test("afdsgsdgsa", "*"));

    EXPECT_TRUE(test("baa", "?aa"));
    EXPECT_TRUE(test("aac", "aa?"));
    EXPECT_TRUE(test("aac", "*?"));
    EXPECT_TRUE(test("aac", "*?c"));
    EXPECT_TRUE(test("abc", "a*b*c"));

    EXPECT_FALSE(test("aa", "a"));
    EXPECT_FALSE(test("aaa", "aa"));
    EXPECT_FALSE(test("aaa", "a*b"));
    EXPECT_FALSE(test("aadsdga", "a*b**b"));
}
