#include "fmt/base.h"
#include "src/helpers.h"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>
#include <set>
#include <unordered_set>
#include <vector>

// https://leetcode.com/problems/zigzag-conversion

// data = std::vector<std::string>()
// row = n % K
// row == K - 1 ->
class Solution {
public:
  auto threeSum(std::vector<int>& nums) -> std::vector<std::vector<int>> {
      return {};
  }
};

TEST_CASE("unordered_multimap") {
  std::vector<int> vdata = {-1, -1, 0, 1, 2, -1};
  std::ranges::sort(vdata);
    fmt::print("vdata: {}\n", utilities::to_json(vdata));

    std::multiset<int> data(vdata.cbegin(), vdata.cend());
    fmt::print("data: {}\n", utilities::to_json(data));

    const auto left = data.lower_bound(-1);
    const auto right = data.upper_bound(-1);

    for (auto it = left; it != right; ++it) {
        fmt::print("{} ", *it);
    }
    fmt::print("\n");
}

TEST_CASE("Basic tests") {
  Solution sol;

  SECTION("Case 1") {
    std::vector<int> nums = {-1, 0, 1, 2, -1, -4};
    auto results = sol.threeSum(nums);
    std::vector<std::vector<int>> expected_results = {};
    CHECK(expected_results == sol.threeSum(nums));
  }
}
