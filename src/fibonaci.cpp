#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdio>
#include <fmt/format.h>
#include <vector>

namespace algorithm {
size_t fibonaci(const size_t n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  return fibonaci(n - 1) + fibonaci(n - 2);
}

size_t fibonaci_dp(const int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;

  size_t current = 1;
  size_t prev = 0;
  for (auto i = 2; i <= n; ++i) {
    const auto next = current + prev;
    prev = current;
    current = next;
  }
  return current;
}
}  // namespace algorithm

TEST_CASE("Basic tests") {
  SECTION("Recursive algorithm") {
      CHECK(algorithm::fibonaci(2) == 1);
      CHECK(algorithm::fibonaci(3) == 2);
      CHECK(algorithm::fibonaci(4) == 3);
      CHECK(algorithm::fibonaci(5) == 5);
      CHECK(algorithm::fibonaci(10) == 55);
  }

  SECTION("Dynamic programming") {
      CHECK(algorithm::fibonaci_dp(10) == 55);
  }
}
