#include "fmt/base.h"
#include <catch2/catch_test_macros.hpp>
#include <cstddef>
#include <cstdio>
#include <fmt/format.h>
#include <string>
#include <unordered_set>
#include <vector>

namespace algorithm {
bool is_word(const std::string& word) {
  static const std::unordered_set<std::string> dict = {
      "a", "both", "earth", "and", "saturn", "spin"};
  return dict.contains(word);
}

bool is_splitable(const std::string& input) {
  if (input.empty())
    return true;

  // Setup the initial state
  const auto len = input.length();
  std::vector<int> status(len + 1, 0);
  status[0] = 1;

  // Update the status
  for (auto left = 0; left < len; ++left) {
    for (auto right = left + 1; right <= len; ++right) {
      if (status[left] && !status[right]) {
        if (is_word(input.substr(left, right - left))) {
          if (right == len)
            return true;
          status[right] = 1;
        }
      }
    }
  }
  return status[len];
}

bool is_splitable_backward(const std::string& input) {
  if (input.empty())
    return true;

  // Setup the initial state
  const auto len = input.length();
  std::vector<int> status(len + 1, 0);
  status[len] = 1;

  // Update the status
  for (auto right = len; right > 0; --right) {
    for (auto left = 0; left < right; ++left) {
      if (status[right] && is_word(input.substr(left, right - left))) {
        status[left] = 1;
      }
    }
  }
  return status[0];
}

bool text_segmentation(
    const std::string& input,
    const size_t pos,
    std::vector<std::string>& results) {
  if (pos >= input.length()) {
    return true;
  }

  for (auto idx = pos; idx < input.length(); ++idx) {
    const auto a_word = input.substr(pos, idx + 1 - pos);
    if (is_word(a_word)) {
      results.push_back(a_word);
      if (text_segmentation(input, idx + 1, results)) {
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
    std::vector<std::string>& results) {
  if (left == right) {
    return true;
  }

  for (auto it = left; it != right; ++it) {
    const auto key = std::string(left, it + 1);
    if (is_word(key)) {
      results.push_back(key);
      if (text_segmentation_iterator(it + 1, right, results)) {
        return true;
      }
      results.pop_back();
    }
  }

  return false;
}

std::vector<std::string> text_segmentation(const std::string& input) {
  std::vector<std::string> results;
  return text_segmentation_iterator(input.cbegin(), input.cend(), results)
      ? results
      : std::vector<std::string>{};
}

}  // namespace algorithm

TEST_CASE("Basic tests") {
  SECTION("Basic test") {
    const auto results = algorithm::text_segmentation("bothearthandsaturnspin");
    CHECK(
        results ==
        std::vector<std::string>{"both", "earth", "and", "saturn", "spin"});
  }

  SECTION("Could not segment the string") {
    const auto results =
        algorithm::text_segmentation("bothearth1andsaturnspin");
    CHECK(results == std::vector<std::string>{});
  }
}

TEST_CASE("Check that a string is splitable") {
  CHECK(algorithm::is_splitable(""));
  CHECK(algorithm::is_splitable("a"));
  CHECK(algorithm::is_splitable("bothearthandsaturnspin"));
  CHECK(algorithm::is_splitable("bothearthaandsaturnspin"));

  CHECK_FALSE(algorithm::is_splitable("b"));
}

TEST_CASE("Check that a string is splitable - dp-backward") {
    CHECK(algorithm::is_splitable_backward(""));
    CHECK(algorithm::is_splitable_backward("a"));
    CHECK(algorithm::is_splitable_backward("bothearthandsaturnspin"));
    CHECK(algorithm::is_splitable_backward("bothearthaandsaturnspin"));

    CHECK_FALSE(algorithm::is_splitable_backward("b"));
}
