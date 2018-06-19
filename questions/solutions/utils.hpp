#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>

template <typename Iterator> void print(Iterator begin, Iterator end) {
    if (begin == end) {
        std::cout << "[]";
        return;
    }
    std::cout << "[";
    std::cout << *begin;
    for (auto iter = ++begin; iter != end; ++iter) {
        std::cout << "," << *iter;
    }
    std::cout << "]";
}
