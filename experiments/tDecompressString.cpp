#include <cassert>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "gtest/gtest.h"

std::string decompress_recursive(const std::string &input, size_t begin, size_t end) {
    std::string results;
    if (begin == end) return results;

    // std::cout << "Input: " << input.substr(begin, end - begin) << "\n";

    for (size_t idx = begin; idx < end; ++idx) {
        const char ch = input[idx];
        if (isdigit(ch)) {
            // Get the number of loops
            int loop = ch - '0';
            size_t endOfNumStr = idx + 1;
            for (; endOfNumStr < end; ++endOfNumStr) {
                if (!isdigit(input[endOfNumStr])) {
                    break;
                } else {
                    loop = loop * 10 + (ch - '0');
                }
            }
            idx = --endOfNumStr;

            // Throw an error if the string format is invalid.
            if (input[idx + 1] != '[') {
                throw(std::runtime_error("Ill-formed string!"));
            }

            // Detect the substring
            size_t newStop = idx + 2;
            int count = 1;
            for (; newStop < end; ++newStop) {
                if (input[newStop] == '[') {
                    count++;
                } else if (input[newStop] == ']') {
                    count--;
                    if (count == 0) {
                        break;
                    }
                }
            }

            // Decompress the middle part
            auto substr = decompress_recursive(input, idx + 2, newStop);
            for (int counter = 0; counter < loop; ++counter) {
                results += substr;
            }

            // Decompress the tail
            results += decompress_recursive(input, newStop + 1, end);

            break;
        } else {
            results.push_back(ch);
        }
    }
    return results;
}

TEST(Serialization, Positive) {
  {
    std::string input("a3[b2[c]]");
    EXPECT_EQ("abccbccbcc", decompress_recursive(input, 0, input.size()));
  }

  {
    std::string input("a3[b2[c]d]");
    EXPECT_EQ("abccdbccdbccd", decompress_recursive(input, 0, input.size()));
  }

  {
    std::string input("a3[b2[c]13[e]]d");
    EXPECT_EQ("abcceeeeeeeeeeebcceeeeeeeeeeebcceeeeeeeeeeed", decompress_recursive(input, 0, input.size()));
  }
}

// int main() {
//     {
//         std::string input("a3[b2[c]]");
//         std::cout << "Results: " << decompress(input, 0, input.size()) << "\n";
//     }

//     {
//         std::string input("a3[b2[c]d]");
//         std::cout << "Results: " << decompress(input, 0, input.size()) << "\n";
//     }

//     {
//         std::string input("a3[b2[c]13[e]]d");
//         std::cout << "Results: " << decompress(input, 0, input.size()) << "\n";
//     }
// }
