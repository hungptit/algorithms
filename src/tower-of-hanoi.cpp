#include "helpers.h"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <fmt/format.h>
#include <vector>

namespace algorithm {
void tower_of_hanoi(
    std::vector<int>& src,
    std::vector<int>& dst,
    std::vector<int>& tmp,
    const size_t N) {
  // Do nothing if there is not any disk
  if (N == 0)
    return;

  // Move N - 1 disk to temp.
  tower_of_hanoi(src, tmp, dst, N - 1);

  // Move the first disk to dst
  dst.push_back(src.back());
  src.pop_back();

  // Move all disks in temp to dst
  tower_of_hanoi(tmp, dst, src, N - 1);
}
}  // namespace algorithm

TEST_CASE("Tower of Hanoi") {
  SECTION("Empty disk") {
    std::vector<int> src, dst, tmp;
    algorithm::tower_of_hanoi(src, dst, tmp, src.size());
    REQUIRE(src.empty());
    REQUIRE(dst.empty());
  }

  SECTION("One disk") {
    std::vector<int> src{1}, dst, tmp;
    algorithm::tower_of_hanoi(src, dst, tmp, src.size());
    REQUIRE(src.empty());
    REQUIRE(dst == std::vector<int>{1});
  }

  SECTION("Two disks") {
    const std::vector<int> disks = {3, 1};
    std::vector<int> src = disks, dst, tmp;
    fmt::print("src = {}\n", utilities::to_json(src));
    algorithm::tower_of_hanoi(src, dst, tmp, src.size());
    REQUIRE(src.empty());
    REQUIRE(dst == disks);
    fmt::print("dst = {}\n", utilities::to_json(dst));
  }

  SECTION("Five disks") {
    const std::vector<int> disks = {31, 15, 7, 3, 1};
    std::vector<int> src = disks, dst, tmp;
    fmt::print("src = {}\n", utilities::to_json(src));
    algorithm::tower_of_hanoi(src, dst, tmp, src.size());
    REQUIRE(src.empty());
    REQUIRE(dst != disks);
    fmt::print("dst = {}\n", utilities::to_json(dst));
  }
}
