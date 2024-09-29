#include "fmt/base.h"
#include "src/helpers.h"
#include <catch2/catch_test_macros.hpp>
#include <cstdio>
#include <ctime>
#include <fmt/format.h>
#include <vector>

// 1. How do we handle large files that do not fit the memory?
// Solution:
// a. Map the file. We want the kernel fetch the data for us.
// b. Detect lines using the EOL characters.
// c. Parse the data and do something with it. We can store the log data in a
// more compressed format.

// 2. How do we speed up the parser code?
// Solution:
// a. Use SIMD
// b.
namespace {
auto is_seperator(const char ch) -> bool {
  return ch == ' ' || ch == '[' || ch == ']' || ch == '"';
}

auto is_open_square_bracket(const char ch) -> bool {
  return ch == '[';
}

auto is_close_square_bracket(const char ch) -> bool {
  return ch == ']';
}

auto parse(const std::string& line) -> std::vector<std::string> {
  std::vector<std::string> results;
  int begin = 0, current = 0, end = line.length();
  bool has_square_bracket = false;
  std::vector<char> stack;
  while (current < end) {
    const auto ch = line[current];
    if (is_open_square_bracket(ch)) {
      begin = current;
      has_square_bracket = true;
    } else if (is_close_square_bracket(ch)) {
      if (current != begin) {
        results.push_back(line.substr(begin, current - begin + 1));
      }
      begin = current + 1;
      has_square_bracket = false;
    } else if (is_seperator(ch) && !has_square_bracket) {
      if (current != begin) {
        results.push_back(line.substr(begin, current - begin));
      }
      begin = current + 1;
    }

    ++current;  // Move to the next char
  }
  return results;
}
}  // namespace

TEST_CASE("Basic tests") {
  const std::string line =
      R"(127.0.0.1 - - [18/Aug/2023:17:54:36 +0100] "GET / HTTP/1.1" 200 12345)";
  fmt::print("results: {}\n", utilities::to_json(parse(line)));
}
