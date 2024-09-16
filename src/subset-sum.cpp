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

// The O(target * n) solution
bool subset_sum_dp(const std::vector<int>& x, const int target) {
  if (target < 0)
    return false;

  if (target == 0)
    return true;

  // Initial states
  std::vector<int> solutions(target + 1, 0);
  std::vector<int> stack;
  stack.reserve(target);
  solutions[0] = 1;

  // Main loop
  for (const auto val : x) {
    for (auto idx = 0; idx < target; ++idx) {
      if (solutions[idx]) {
        const auto next_idx = idx + val;
        if (next_idx > target) {
          continue;
        }

        if (next_idx == target) {
          return true;
        }

        if (!solutions[next_idx]) {
          stack.push_back(next_idx);
        }
      }
    }

    for (const auto val : stack) {
      solutions[val] = 1;
    }

    stack.clear();
  }

  return false;
}
}  // namespace algorithm

TEST_CASE("Basic tests") {
  SECTION("Case 1") {
    std::vector<int> x = {8, 6, 7, 5, 3, 10, 9};
    const int target = 15;
    CHECK(algorithm::subset_sum(x, 0, target));
    CHECK(algorithm::subset_sum_dp(x, target));
  }

  SECTION("Case 1") {
    std::vector<int> x = {11, 6, 5, 1, 7, 13, 12};
    const int target = 15;
    CHECK_FALSE(algorithm::subset_sum(x, 0, target));
    CHECK_FALSE(algorithm::subset_sum_dp(x, target));
  }
}
