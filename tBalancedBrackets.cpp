#include "gtest/gtest.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

class Simple {
  public:
  bool operator()(const std::string &expression) {
        std::vector<char> stack;
        if (expression.empty()) {
            return true;
        }

        for (char ch : expression) {
            // If the current character is the open bracket then we push a
            // close bracket into the stack. We do this to improve the
            // performance.
            if (isOpenBracket(ch)) {
                stack.push_back(getCloseBracket(ch));
                continue;
            }

            if (isCloseBracket(ch)) {
                if (stack.empty()) {
                    // If the stack is empty then it is obvious that a given
                    // expression is imbalanced.
                    return false;
                }

                if (ch == stack.back()) {
                    // If the current close bracket is matched with the back
                    // element then we pop this element out of the stack.
                    stack.pop_back();
                } else {
                    // Otherwise the expression is imbalanced.
                    return false;
                }
            }
        }

        return stack.empty();
    }

  private:
    bool isOpenBracket(const char ch) {
        bool result = false;
        switch (ch) {
        case '{':
        case '[':
        case '(':
            result = true;
        }
        return result;
    }

    bool isCloseBracket(const char ch) {
        bool result = false;
        switch (ch) {
        case '}':
        case ']':
        case ')':
            result = true;
        }
        return result;
    }

    char getCloseBracket(const char openBraket) {
        switch (openBraket) {
        case '{':
            return '}';
        case '[':
            return ']';
        case '(':
            return ')';
        }
        return 0;
    }
};

struct UsingVector {
  bool operator()(const std::string &expression) {
        std::array<char, 3> openBrakets = {{'{', '[', '('}};
        std::array<char, 3> closeBrakets = {{'}', ']', ')'}};
        std::vector<char> stack;

        if (expression.empty()) {
            return true;
        }

        for (char ch : expression) {
            for (auto och : openBrakets) {
                if (ch == och) {
                    stack.push_back(ch);
                    break;
                }
            }

            for (size_t idx = 0; idx < closeBrakets.size(); ++idx) {
                if (closeBrakets[idx] == ch) {
                    if (stack.empty()) {
                        return false;
                    }

                    if (openBrakets[idx] == stack.back()) {
                        stack.pop_back();
                        break;
                    } else {
                        return false;
                    }
                }
            }
        }

        return stack.empty();
    }
};

template <typename F> void test() {
    F f;
    EXPECT_TRUE(f("(dsdd(dsds[]dsds))"));
    EXPECT_TRUE(f("(dsdd({ds}d{s}[]dsds))"));
    EXPECT_TRUE(f(""));

    EXPECT_FALSE(f("{dsds[}]"));
    EXPECT_FALSE(f("{"));
    EXPECT_FALSE(f("}"));
    EXPECT_FALSE(f("["));
    EXPECT_FALSE(f("]"));
    EXPECT_FALSE(f("("));
    EXPECT_FALSE(f(")"));
}

TEST(BasicTests, Positive) {
    test<Simple>();
    test<UsingVector>();
}
