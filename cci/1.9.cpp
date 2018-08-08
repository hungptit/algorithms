#include <iostream>
#include <string>

namespace cci {
    // The runtime complexity of this problem is O(n)
    template <typename Iter> bool is_rotated(Iter beg1, Iter end1, Iter beg2, Iter end2, Iter it) {
        auto it1 = beg1;
        auto it2 = it;
        while (it1 != end1) {
            if (*it1 != *it2) return false;
            ++it1;
            ++it2;
            if (it2 == end2) it2 = beg2; // Move to the beginning if needed.
        }
        return true;
    }
} // namespace cci

namespace {
    // The runtime complexity of this problem is O(n^2)
    void test(const std::string &s1, const std::string &s2) {
        bool isok = false;
        if (s1.size() == s2.size()) {
            for (auto it = s2.cbegin(); it != s2.cend(); ++it) {
                isok = cci::is_rotated(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), it);
                if (isok) {
                    break;
                }
            }
        }
        std::cout << s1 << (isok ? " is " : " is not ") << "a rotated version of " << s2 << "\n";
    }

    // The runtime complexity of this problem is O(n^2) but it is better than the previous solution.
    void test2(const std::string &s1, const std::string &s2) {
        bool isok = false;
        if (s1.size() == s2.size()) {
            for (auto it = s2.cbegin(); it != s2.cend(); ++it) {
                if (*s1.cbegin() == *it) {
                    isok = cci::is_rotated(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), it);
                }
                if (isok) {
                    break;
                }
            }
        }
        std::cout << s1 << (isok ? " is " : " is not ") << "a rotated version of " << s2 << "\n";
    }
} // namespace

int main() {
    test("waterbottle", "erbottlewat");
    test("waterbottle", "erbottlewbt");
    test("waterbottle", "erbottlewbt2");

    test2("waterbottle", "erbottlewat");
    test2("waterbottle", "erbottlewbt");
    test2("waterbottle", "erbottlewbt2");
}
