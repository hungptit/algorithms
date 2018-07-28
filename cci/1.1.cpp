#include <array>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

namespace cci {
    template <typename T> void print(T &&data) {
        for (auto val : data) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }

    // Assumption:
    // 1. 8 bit characters
    // 2. N/8 extra storage
    // 3. O(n) runtime complexity.

    template <typename T> bool has_unique_chars(const std::string &s) {
        T map = {{0}};
        for (auto ch : s) {
            if (!map[ch]) {
                map[ch] = 1;
            } else {
                return false;
            }
        }
        return true;
    }

    template <typename T> void test(const std::vector<std::string> &data) {
        for (auto const &s : data) {
            std::cout << s << ": " << (has_unique_chars<T>(s) ? "yes" : "no") << "\n";
        }
    }
} // namespace cci

int main() {
    cci::test<std::array<int, 256>>({"foo", "abcdef"});
    cci::test<std::array<char, 256>>({"foo", "abcdef"});
    cci::test<std::bitset<256>>({"foo", "abcdef"});
    return EXIT_SUCCESS;
}
