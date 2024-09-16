#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdio>
#include <fmt/format.h>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

namespace algorithm {
bool text_segmentation(
    const std::string& input,
    const std::unordered_set<std::string>& dict,
    const size_t pos,
    std::vector<std::string>& results) {
  if (pos >= input.length()) {
    return true;
  }

  for (auto idx = pos; idx < input.length(); ++idx) {
    const auto key = input.substr(pos, idx + 1 - pos);
    if (dict.count(key)) {
      results.push_back(key);
      if (text_segmentation(input, dict, idx + 1, results)) {
        return true;
      }
      results.pop_back();
    }
  }

  return false;
}

using iterator_type = std::string::const_iterator;
bool text_segmentation_iterator(
    const iterator_type left,
    const iterator_type right,
    const std::unordered_set<std::string>& dict,
    std::vector<std::string>& results) {
  if (left == right) {
    return true;
  }

  for (auto it = left; it != right; ++it) {
    const auto key = std::string(left, it + 1);
    if (dict.count(key)) {
      results.push_back(key);
      if (text_segmentation_iterator(it + 1, right, dict, results)) {
        return true;
      }
      results.pop_back();
    }
  }

  return false;
}

std::vector<std::string> text_segmentation(
    const std::string& input, const std::unordered_set<std::string>& dict) {
  std::vector<std::string> results;
  return text_segmentation_iterator(input.cbegin(), input.cend(), dict, results)
      ? results
      : std::vector<std::string>{};
}

}  // namespace algorithm

TEST_CASE("Basic tests") {
  const std::unordered_set<std::string> dict = {
      "both", "earth", "and", "saturn", "spin"};

  SECTION("Basic test") {
    const auto results =
        algorithm::text_segmentation("bothearthandsaturnspin", dict);
    CHECK(
        results ==
        std::vector<std::string>{"both", "earth", "and", "saturn", "spin"});
  }

  SECTION("Could not segment the string") {
    const auto results =
        algorithm::text_segmentation("bothearthaandsaturnspin", dict);
    CHECK(results == std::vector<std::string>{});
  }
}
