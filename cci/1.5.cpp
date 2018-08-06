#include <iostream>
#include <string>

namespace cci {

    // This algorithm assume that length(first) =< length(second)
    bool is_valid_same_size(const char *begin1, const char *end1,
                            const char *begin2) {
        int count = 0;
        auto ptr1(begin1);
        auto ptr2(begin2);
        while (ptr1 != end1) {
            if (*ptr1 != *ptr2) {
                if (count) return false;
                ++count;
            }
            ++ptr1;
            ++ptr2;
        }
        return true;
    }

    bool is_valid(const char *begin1, const char *end1, const char *begin2) {
        int count = 0;
        auto ptr1(begin1);
        auto ptr2(begin2);
        while (ptr1 != end1) {
            if (*ptr1 != *ptr2) {
                if (count) {
                    return false;
                } else {
                    ++ptr1;
                }
                ++count;
            } else {
                ++ptr1;
                ++ptr2;
            }
        }
        return true;
    }

    bool is_valid(const std::string &s1, const std::string &s2) {
        if (s1.size() == s2.size()) {
            return is_valid_same_size(s1.data(), s1.data() + s1.size(),
                                      s2.data());
        }

        if (s2.size() == (s1.size() + 1)) {
            return is_valid(s1.data(), s1.data() + s1.size(), s2.data());
        }

        if (s1.size() == (s2.size() + 1)) {
            return is_valid(s2.data() + s2.size(), s1.data());
        }

        return false;
    }

    void test(const std::string &s1, const std::string &s2) {
        std::cout << "The edit distance between "
                  << "\"" << s1 << "\""
                  << " and "
                  << "\"" << s2 << "\""
                  << " is "
                  << (is_valid(s1, s2) ? "less than 2" : "greater than one")
                  << "\n";
    }

} // namespace cci

int main() {
    cci::test("foo", "boo");
    cci::test("go", "goo");
    cci::test("goo", "go1o");
    cci::test("foo1234", "boo");
    cci::test("foo", "co");
    cci::test("fcoo", "co1o");
}
