#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace algorithms {
  template <typename T, typename InputContainer> bool is_unique(InputContainer &s) {
        std::array<T, 256> map{};
        for (unsigned char ch : s) {
            if (map[ch]) {
                return false;
            } else {
                map[ch] = true;
            }
        }
        return true;
    }

  template <typename T, typename InputContainer> bool is_unique_vector(InputContainer &s) {
    std::vector<T> map(256, 0);
        for (unsigned char ch : s) {
            if (map[ch]) {
                return false;
            } else {
                map[ch] = true;
            }
        }
        return true;
    }

    bool is_unique_map(const std::string &s) {
        std::unordered_set<char> map;
        map.reserve(256);
        for (unsigned char ch : s) {
          if (map.find(ch) != map.end()) {
            return false;
          } else {
            map.emplace(ch);
          }
        }
        return true;
    }
}
