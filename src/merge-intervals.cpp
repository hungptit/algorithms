#include "fmt/base.h"
#include "helpers.h"
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <fmt/format.h>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

namespace algorithm {
struct interval {
  int begin;
  int end;
};

// We can merge two intervals if there is any overlap.
auto is_mergeable(const interval lhs, const interval rhs) -> bool {
  return lhs.end >= rhs.begin;
}

auto merge_intervals(std::vector<interval>& data) -> std::vector<interval> {
  if (data.size() < 2)
    return {data.cbegin(), data.cend()};

  // Sort the data before merging the interval, O(nlog(n))
  std::ranges::sort(
      data, [](const interval lhs, const interval rhs) {
        return std::tie(lhs.begin, lhs.end) < std::tie(rhs.begin, rhs.end);
      });

  // Merge intervals if overlaped, O(n).
  std::vector<interval> results;
  auto it = data.cbegin();
  auto current = *it;
  for (; it != data.cend(); ++it) {
    if (is_mergeable(current, *it)) {
        current.end = it->end;
    } else {
        results.push_back(current);
        current = *it;
    }
  }
  results.push_back(current);

  return results;
}

auto operator==(const interval lhs, const interval rhs) -> bool {
  return std::tie(lhs.begin, lhs.end) == std::tie(rhs.begin, rhs.end);
}
}  // namespace algorithm

namespace std {
auto to_string(const std::vector<algorithm::interval> value) -> string {
  return utilities::to_json(value);
}

auto operator<<(ostream& os, algorithm::interval data) -> ostream& {
  return os << utilities::to_json(data);
}
}  // namespace std

TEST_CASE("Operators") {
  std::vector<algorithm::interval> data = {{.begin=1, .end=3}, {.begin=6, .end=7}, {.begin=2, .end=5}};
  const std::vector<algorithm::interval> expected_results = {
      {.begin=1, .end=3}, {.begin=2, .end=5}, {.begin=6, .end=7}};
  std::ranges::sort(
      data,
     
      [](const algorithm::interval lhs, const algorithm::interval rhs) {
        return std::tie(lhs.begin, lhs.end) < std::tie(rhs.begin, rhs.end);
      });

  CHECK(data == expected_results);
}

TEST_CASE("Basic tests") {
  SECTION("Empty intervals") {
  }

  SECTION("One interval") {
  }

  SECTION("Three intervals") {
    std::vector<algorithm::interval> data = {{.begin=2, .end=4}, {.begin=1, .end=3}, {.begin=6, .end=7}, {.begin=2, .end=5}};
    auto results = algorithm::merge_intervals(data);
    CHECK(results == std::vector<algorithm::interval>{{1, 5}, {6, 7}});
  }
}
