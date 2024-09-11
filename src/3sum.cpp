#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>
#include <vector>

// https://leetcode.com/problems/3sum/description/

// Given:
// 1. There may be duplicated elements in the array.

// 1. The naive solution is testing all possible combinations in O(n^3).
//
// Observations:
// a. We can bring the complexity down to the O(n^2) by using a lookup table (value -> positions)
// b. We can
class Solution {
public:
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {}
};

TEST_CASE("Basic tests") {
  Solution sol;

  SECTION("Case 1") {
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto results = sol.threeSum(nums);
    std::vector<std::vector<int>> expected_results = {};
    CHECK(expected_results == sol.threeSum(nums));
  }
}
