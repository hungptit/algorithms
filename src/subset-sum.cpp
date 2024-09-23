#include "src/helpers.h"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdio>
#include <fmt/format.h>
#include <vector>

namespace algorithm {
// Note:
// 1. Take advantage of the fact that all number are positive.
// 2. We can bring the complexity down using the dynamic programming approach,
// O(target * n).

// The O(2^n) solution
bool subset_sum(const std::vector<int>& x, const size_t pos, const int target) {
  if (pos >= x.size() || target < 0)
    return false;

  if (x[pos] == target)
    return x[pos] == target;

  return subset_sum(x, pos + 1, target) ||
      subset_sum(x, pos + 1, target - x[pos]);
}

// The O(target * n) solution that requires O(n) memory.
bool subset_sum_dp(const std::vector<int>& x, const int N) {
  if (N < 0)
    return false;

  if (N == 0)
    return true;

  // Initial states
  std::vector<int> current(N + 1, 0);
  std::vector<int> next(N + 1, 0);
  current[0] = 1;

  // Main loop
  for (const auto val : x) {
    for (auto target = 0; target <= N; ++target) {
      if (target >= val) {
        next[target] = current[target] | current[target - val];
      } else {
        next[target] = current[target];
      }
    }
    std::swap(current, next);
  }

  return current.back();
}
}  // namespace algorithm

TEST_CASE("Basic tests") {
  SECTION("Case 1") {
    std::vector<int> x = {8, 6, 7, 5, 3, 10, 9};
    fmt::print("x: {}\n", utilities::to_json(x));
    const int target = 15;
    CHECK(algorithm::subset_sum(x, 0, 15));
    CHECK(algorithm::subset_sum_dp(x, 15));
    CHECK(algorithm::subset_sum_dp(x, 16));
    CHECK(algorithm::subset_sum_dp(x, 30));
  }

  SECTION("Case 2") {
    std::vector<int> x = {11, 6, 5, 1, 7, 13, 12};
    fmt::print("x: {}\n", utilities::to_json(x));

    CHECK_FALSE(algorithm::subset_sum(x, 0, 15));
    CHECK_FALSE(algorithm::subset_sum_dp(x, 15));

    CHECK(algorithm::subset_sum_dp(x, 23));
  }
}
