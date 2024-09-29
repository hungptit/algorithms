#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <cstdio>
#include <fmt/format.h>
#include <vector>

namespace algorithm {
struct ForwardSolution {
  ForwardSolution(const std::vector<int>& x) : x(x) {}
  auto longest_increasing_subsequence(const int i) -> int {
    int max_len = 0;
    for (auto j = i + 1; j < x.size(); ++j) {
      if (x[j] > x[i]) {
        max_len = std::max(max_len, longest_increasing_subsequence(j));
      }
    }
    return 1 + max_len;
  }

  std::vector<int> x;
};

struct DPSolution {
  DPSolution(const std::vector<int>& x) : x(x), solutions(x.size(), 1) {}
  auto longest_increasing_subsequence() -> int {
    for (int i = 0; i < x.size() - 1; ++i) {
      for (auto j = i + 1; j < x.size(); ++j) {
        if (x[j] > x[i]) {  // Only update the solution if x[j] > x[i]
          solutions[j] = std::max(solutions[j], 1 + solutions[i]);
        }
      }
    }
    auto it = std::ranges::max_element(solutions);
    return *it;
  }

  std::vector<int> x;
  std::vector<int> solutions;
};

}  // namespace algorithm

TEST_CASE("Basic tests") {
    SECTION("Recursive solution") {
        using Solution = algorithm::ForwardSolution;
        CHECK(
              Solution({3, 1, 4, 1, 5, 9, 2, 6, 5, 3})
              .longest_increasing_subsequence(0) == 4);
        CHECK(Solution({3, 1}).longest_increasing_subsequence(0) == 1);
        CHECK(Solution({1, 2}).longest_increasing_subsequence(0) == 2);
    }

    SECTION("DP solution") {
    using Solution = algorithm::DPSolution;
    CHECK(
        Solution({3, 1, 4, 1, 5, 9, 2, 6, 5, 3})
            .longest_increasing_subsequence() == 4);
    CHECK(Solution({3, 1}).longest_increasing_subsequence() == 1);
    CHECK(Solution({1, 2}).longest_increasing_subsequence() == 2);
  }
}
