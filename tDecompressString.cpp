#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cassert>

bool isNumber(const char ch) {
  int diff = ch - '0';
  return (diff >= 0) && (diff <= 9);
}

std::string decompress(const std::string &input, size_t begin, size_t end) {
  std::string results;
  if (begin == end) return results;
 
  std::cout << "Input: " << input.substr(begin, end - begin) << "\n";
  
  for (size_t idx = begin; idx < end; ++idx ) {
    const char ch = input[idx];
    if (isdigit(ch)) {
      // Get the number of loop
      int loop = ch - '0';
      size_t endOfNumStr = idx + 1;
      for (; endOfNumStr < end; ++endOfNumStr) {
        if (!isdigit(input[endOfNumStr])) {          
          break;
        } else {
          loop = loop * 10 + (ch - '0');
        }
      }
      idx = endOfNumStr - 1;

      // Throw an error if the string format is invalid.
      if (input[idx + 1] != '[') {
        throw(std::runtime_error("Imbalanced string!"));
      }

      // Detect the substring
      size_t newStop = idx + 2;
      int count = 1;
      for (; newStop < end; ++newStop) {
        if (input[newStop] == '[') {
          count ++;
        } else if (input[newStop] == ']') {
          count --;
          if (count == 0) {
            break;
          }
        }
      }

      // Decompress the middle part
      auto substr = decompress(input, idx + 2, newStop);      
      for (int counter = 0; counter < loop; ++counter) {
        results += substr;
      }

      // Decompress the tail
      results += decompress(input, newStop + 1, end);
      
      break;
    } else {
      results.push_back(ch);
    }
  }
  return results;
}


int main() {
    {
        std::string input("a3[b2[c]]");
        std::cout << "Results: " << decompress(input, 0, input.size())
                  << "\n";
    }

    {
      std::string input("a3[b2[c]d]");
      std::cout << "Results: " << decompress(input, 0, input.size())
                << "\n";
    }

    {
      std::string input("a3[b2[c]13[e]]d");
      std::cout << "Results: " << decompress(input, 0, input.size())
                << "\n";
    }
}
