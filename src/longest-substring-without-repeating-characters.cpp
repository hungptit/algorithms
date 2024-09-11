#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <fmt/format.h>
#include <string>

namespace algorithm {

// 1. Naive solution: Find the longest substring length using the O(n^2)
// solution.
// Check that s(i,j) is a valid string. We need to explore all combinations of
// (i, j) therefore the runtime complexity is O(n^2).

// We can check that a string is valid or not using a lookup table. The fastest
// lookup table is std::array<char, 256> assuming we are using the 8 bit
// characters.

// Is there any efficient way to check that s(i, j+1) is a valid string if we
// have already know s(i, j) is valid. We can use a shared lookup table to reuse
// the previos step results.

// 2. Using the lookup table to find the longest substring length using O(n)
// algorithm.
// * If the current character is in the lookup table then increase the begin and
// restart the process.
// * Otherwise update the lookup table and move to the next character.
//

bool is_valid(const std::string& s) {
  std::array<int, 256> lookup_table = {};
  for (const auto ch : s) {
    if (lookup_table[ch]) {
      return false;
    }
    ++lookup_table[ch];
  }
  return true;
}

struct Solution {
  size_t compute(const std::string& s) {
    if (s.empty())
      return 0;

    // Setup the initial state
    size_t left = 0, end = s.length();
    lookup_table[s[left]] = 1;
    size_t right = left + 1;
    size_t maxlen = right - left;

    // Find the maximum substring lenght using the sliding window technique.
    while (right < end) {
      if (lookup_table[s[right]]) {
        maxlen = std::max(maxlen, right - left);
        --lookup_table[s[left]];
        ++left;  // Shift the window if there is a duplicated character.
      } else {
        ++lookup_table[s[right]];
        ++right;  // Expand the window if there is not any duplicated character.
      }
    }

    return std::max(maxlen, right - left);
  }

  std::array<int, 256> lookup_table = {};
};

}  // namespace algorithm

TEST_CASE("Tests") {
  CHECK_FALSE(algorithm::is_valid("aaaa"));
  CHECK(algorithm::is_valid("abcd"));
}

TEST_CASE("Basic tests") {
  algorithm::Solution sol;
  CHECK(sol.compute("") == 0);
  CHECK(sol.compute("a") == 1);
  CHECK(sol.compute("abcabcbb") == 3);
  CHECK(sol.compute("bbbbb") == 1);
  CHECK(sol.compute("pwwkew") == 3);
  CHECK(sol.compute("au") == 2);
}
