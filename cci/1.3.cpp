#include <iostream>
#include <string>

namespace cci {
    constexpr char SPACE = ' ';
    // Run time complexity is O(N)
    // Require a minimum number of memory moves.
    // Doing in-place transformation.
    void replace_space(std::string &s) {
        // Count the number of spaces
        size_t counter(0);
        for (auto ch : s) counter += (ch == SPACE);
        s.resize(s.size() + 2 * counter);

        // Shift string by 2 * counter
        auto N = s.size();
        for (auto idx = N; idx != 0; --idx) {
            s[idx + 2 * counter - 1] = s[idx - 1];
        }

        // Update the string.
        size_t len = N + 2 * counter;
        size_t pos = 0;
        for (size_t idx = 2 * counter; idx < len; ++idx) {
            if (s[idx] != SPACE) {
                s[pos] = s[idx];
                pos++;
            } else {
                s[pos] = '%';
                s[pos + 1] = '2';
                s[pos + 2] = '0';
                pos += 3;
            }
        }
    }

    void test(const std::string &s1) {
        std::string s(s1);
        replace_space(s);
        std::cout << s1 << " <---> " << s << "\n";
    }
} // namespace cci

int main() {
    cci::test("Hello");
    cci::test("Hello world!");
    cci::test("This is my test string");
}
