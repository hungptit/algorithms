#include "helpers.h"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <fmt/format.h>
#include <utility>
#include <vector>

namespace algorithm {
void merge_sort(std::vector<int>& data, const size_t start, const size_t stop) {

  if (start == stop)
    return;
  if ((start + 1) == stop) {
      if (data[start] > data[stop]) std::swap(data[start], data[stop]);
  }

}
}  // namespace algorithm

TEST_CASE("Basic tests") {
  SECTION("Emprty array") {
    std::vector<int> data = {};
    const std::vector<int> expected_results = {};
    REQUIRE(data == expected_results);

  }
  SECTION("One elements") {
  }
}
