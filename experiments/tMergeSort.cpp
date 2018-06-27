#include <iostream>
#include <deque>
#include <list>
#include <vector>
#include "Utils.hpp"

template <typename FirstIterator, typename SecondIterator,
          typename ResultIterator>
void merge_sort(FirstIterator x_begin, FirstIterator x_end,
                SecondIterator y_begin, SecondIterator y_end,
                ResultIterator results) {
    if (x_begin == x_end) {
        std::move(y_begin, y_end, results);
        return;
    }

    if (y_begin == y_end) {
        std::move(x_begin, x_end, results);
        return;
    }

    // Now we can merge two array
    while (true) {
        if (*y_begin < *x_begin) {
            std::swap(*results, *y_begin);
            ++y_begin;
        } else {
            std::swap(*results, *x_begin);
            ++x_begin;
        }

        // Increase results
        ++results;

        // Check for stop condition
        if (x_begin == x_end) {
            std::move(y_begin, y_end, results);
            break;
        }

        if (y_begin == y_end) {
            std::move(x_begin, x_end, results);
            break;
        }
    }
}

int main() {
    
    std::deque<double> x = {1, 2, 3, 4};
    std::list<decltype(x)::value_type> y = {3, 7, 9};
    algorist::print(x, "x: { ", "}\n");
    algorist::print(y, "y: { ", "}\n");
    std::vector<decltype(x)::value_type> results(x.size() + y.size());
    merge_sort(x.begin(), x.end(), y.begin(), y.end(), results.begin());
    algorist::print(results, "results: { ", "}\n");
    algorist::print(x, "new x: { ", "}\n");
    algorist::print(y, "new y: { ", "}\n");
}
