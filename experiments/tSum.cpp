#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

#include "gtest/gtest.h"

template <typename InputIterator, typename OutputIterator>
auto addCarry(InputIterator begin, InputIterator end, OutputIterator obegin, const bool carryBit) {
    auto oit = obegin;
    bool carryFlag = carryBit;
    for (auto it = begin; it != end; ++it, ++oit) {
        *it += carryFlag;
        if (*it > 9) {
            carryFlag = true;
            *oit = (*it) % 10;
        } else {
            *oit = (*it);
        }
    }
    return oit;
}

template <typename FirstIterator, typename SecondIterator, typename OutputIterator>
auto sum(FirstIterator xbegin, FirstIterator xend, SecondIterator ybegin, SecondIterator yend,
         OutputIterator obegin, const bool carryBit) {

    auto firstIt = xbegin;
    auto secondIt = ybegin;
    auto outIt = obegin;
    bool carryFlag = carryBit;

    for (; (firstIt != xend) && (secondIt != yend); ++firstIt, ++secondIt, ++outIt) {
        auto sum = (*firstIt) + (*secondIt) + carryFlag;
        if (sum > 9) {
            carryFlag = true;
            *outIt = sum % 10;
        } else {
            *outIt = sum;
        }
    }

    if (firstIt == xend) {
        outIt = addCarry(secondIt, yend, outIt, carryBit);
    }

    if (secondIt == yend) {
        outIt = addCarry(firstIt, xend, outIt, carryBit);
    }

    return outIt;
}

template <typename Container> auto mysum(Container &x, Container &y) {
    Container results(std::max(x.size(), y.size()) + 1, 0);
    auto outIt = sum(x.begin(), x.end(), y.begin(), y.end(), results.begin(), 0);
    results.resize(std::distance(results.begin(), outIt));
    return results;
}

template <typename Container> void print(Container &data) {
    std::for_each(data.begin(), data.end(), [](auto item) { std::cout << item << " "; });
    std::cout << "\n";
}

TEST(BasicTests, Positive) {
    {
        std::vector<int> x{3, 1, 5}, y{5, 9, 2}, z{8, 0, 8};
        auto results = mysum(x, y);
        print(x);
        print(y);
        print(results);
        EXPECT_EQ(results, z);
    }

    {
        std::list<int> x{3, 1, 5, 1}, y{5, 9, 2}, z{8, 0, 8, 1};
        auto results = mysum(x, y);
        print(x);
        print(y);
        print(results);
        EXPECT_EQ(results, z);
    }
}
