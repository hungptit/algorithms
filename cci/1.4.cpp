#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

namespace cci {

    // Use a fixed array as a map. This approach require O(1) memory
    // and the runtime complexity is O(N)
    bool is_palindrome(const std::string &str1, const std::string &str2) {
        std::string s1(str1.size(), 0), s2(str2.size(), 0);
        std::transform(str1.begin(), str1.end(), s1.begin(), tolower);
        std::transform(str2.begin(), str2.end(), s2.begin(), tolower);
        if (s1.size() != s2.size()) return false;
        std::array<char, 256> map1{}, map2{};
        for (auto ch : s1) { map1[ch]++; }
        for (auto ch : s2) { map2[ch]++; }
        return map1 == map2;
    }

    // We can also use map and unordered_map that can also have O(n)
    // runtime complexity.

    // We can also sort two string then compare this approach does not
    // require memory, however, the run-time complexity is O(nlog())

    void test(const std::string &s1, const std::string &s2) {
        std::cout << "\"" << s1 << "\""
                  << (is_palindrome(s1, s2) ? " is " : " is not ")
                  << "a palindrome of "
                  << "\"" << s2 << "\""
                  << "\n";
    }
} // namespace cci

int main() {
    cci::test("foo", "boo");
    cci::test("foo", "Foo");
    cci::test("taco cat", "cat ocat");
    cci::test("foo", "foofdfd");
}
