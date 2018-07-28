#include <array>
#include <bitset>
#include <iostream>
#include <string>

namespace cci {
    // Runtime complexity O(n)
    // Required memory O(n)
    // Why this solution is the best interm of run time?
    // 1. The hash is fited into cache.
    // 2. Do not see any obvious cache miss.
    // Really need to save memory -> use bitset.
    // Assume two string has the same size. If they are not then check that their sizes are mathced at the
    // beginging.
    template <typename T> bool is_perm_hash(const std::string &s1, const std::string &s2) {
        if (s1.size() != s2.size()) return false;
        if (s1 == s2) return true;
        T h1 = {{0}};
        for (auto ch : s1) ++h1[ch];
        T h2 = {{0}};
        for (auto ch : s2) ++h2[ch];
        return h1 == h2;
    }

    template <typename T> void test(const std::string &s1, const std::string &s2) {
        std::cout << s1 << (is_perm_hash<T>(s1, s2) ? " is " : " isn't ") << "a permutation of " << s2
                  << "\n";
    }
} // namespace cci

int main() {
    cci::test<std::array<unsigned char, 256>>("foo", "boo");
    cci::test<std::array<unsigned char, 256>>("foo", "foo");
    cci::test<std::array<unsigned char, 256>>("foo", "oof");
    cci::test<std::array<unsigned char, 256>>("foo", "ooff");

    return EXIT_SUCCESS;
}
