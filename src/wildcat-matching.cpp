#include "src/helpers.h"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdio>
#include <fmt/format.h>
#include <vector>
namespace algorithm {
struct Solution {
  auto is_match(const int i, const int j) -> bool {
    if (j == p.length())
      return true;
    if (i == s.length()) {
      for (int idx = j; idx < p.length(); ++idx) {
          if (p[idx] != '*') return false;
      }
      return true;
    }
    if (p[j] == '*') {
      return is_match(i + 1, j) || is_match(i + 1, j + 1) || is_match(i, j + 1);
    }
    if (p[j] == '?') {
      return is_match(i + 1, j + 1);
    }
    return s[i] == p[j] && is_match(i + 1, j + 1);
  }
  std::string s;
  std::string p;
};
auto is_match(const std::string& s, const std::string& p) -> bool {
  Solution sol(s, p);
  return sol.is_match(0, 0);
}
}  // namespace algorithm

TEST_CASE("Basic tests") {
  CHECK(algorithm::is_match("aa", "a"));
  CHECK(algorithm::is_match("aa", "*"));
  CHECK(algorithm::is_match("aa", "aa*"));
  CHECK(algorithm::is_match("aa", "a*a"));
  CHECK(algorithm::is_match("adceb", "*a*b"));
  CHECK(algorithm::is_match("adceb", "*a*b*"));
  CHECK_FALSE(algorithm::is_match("cb", "?a"));
}
