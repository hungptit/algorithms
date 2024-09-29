// https://leetcode.com/problems/decode-string/description/
#include <catch2/catch_test_macros.hpp>
#include <cctype>
#include <cstdio>
#include <fmt/format.h>
#include <string>
#include <vector>

namespace {
using Iterator = std::string::const_iterator;

auto decode_string(const Iterator begin, const Iterator end) -> std::string {
  if (begin == end)
    return "";

  // Get the head
  Iterator it = begin;
  for (; it != end; ++it) {
    if (!std::isalpha(*it)) {
      break;
    }
  }
  std::string results = std::string(begin, it);

  // Get the count
  int count = 0;
  while (it != end) {
    if (!std::isdigit(*it))
      break;
    count = count * 10 + *it - '0';
    ++it;
  }

  std::vector<Iterator> stack;
  for (; it != end; ++it) {
    if (*it == '[') {
      stack.push_back(it + 1);
    } else if (*it == ']') {
      auto left = stack.back();
      stack.pop_back();
      if (stack.empty()) {
        auto str = decode_string(left, it);
        for (auto idx = 0; idx < count; ++idx) {
          results += str;
        }
        results += decode_string(it + 1, end);
        break;
      }
    }
  }

  return results;
}

auto decode_string(std::string input) -> std::string {
  return decode_string(input.cbegin(), input.cend());
}

}  // namespace

TEST_CASE("") {
  CHECK(decode_string("3[a]2[bc]") == "aaabcbc");
  CHECK(decode_string("3[a2[c]]") == "accaccacc");
  CHECK(decode_string("2[abc]3[cd]ef") == "abcabccdcdcdef");
}
