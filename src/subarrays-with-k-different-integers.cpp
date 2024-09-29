#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>
#include <unordered_map>
#include <vector>
// https://leetcode.com/problems/subarrays-with-k-different-integers/description/
//
// 1. We can cout all possible solution by testing all combinations with the
// O(n^3) algorithm (naive).

// Observations:
// a. We should reuse the nums(i, j) results when checking nums(i, j+1).
// b. We can do this by using the sliding windows technique.
// c. We can store the num(i, j) results to bring the runtime complexity down to
// O(n^2)

// 2. The sliding windows solution O(n)
// a. Use the hash table to keep track of the count.
// b. Shift the windows if we have more than k distinct integers.
// c. Expand the windows if we have no more than k distinct integers.

namespace algorithm {
struct ForwardSolution {
public:
  auto subarraysWithKDistinct(const std::vector<int>& nums, int k) -> int { return 1; }

  std::unordered_map<int, int> lookup;
};
}  // namespace algorithm
TEST_CASE("Basic tests") {
  algorithm::ForwardSolution sol;
  CHECK(sol.subarraysWithKDistinct({1, 2, 1, 2, 3}, 2) == 7);
  CHECK(sol.subarraysWithKDistinct({1, 2, 1, 3, 4}, 3) == 3);
}
