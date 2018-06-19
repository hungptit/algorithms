#include "utils.hpp"
#include <iostream>
#include <vector>

namespace {
    int max_sum(const std::vector<int> &data) {
        assert(!data.empty()); // Assume data is not empty.
        auto begin = data.begin();
        auto end = data.end();
        int sum = *begin;
        int current_sum = sum;
        int max_sum = current_sum;

        for (auto iter = ++begin; iter != end;) {
            if (*iter > 0) {
                sum += *iter;
                ++iter;
                max_sum = std::max(max_sum, sum);
                continue;
            } else {
                auto current_sum = sum + *iter;
                if (current_sum <= 0) {
                    max_sum = std::max(max_sum, current_sum);

                    // Reset our search
                    ++iter;
                    if (iter == end) break;
                    begin = iter;
                    sum = *iter;
                    ++iter;
                } else {
                    // Move to the next element.
                    sum += *iter;
                    ++iter;
                }
            }
        }

        return max_sum;
    }

} // namespace

int main() {
    auto find_max_sum = [](std::vector<int> &&data) {
        std::cout << "max_sum(";
        print(data.cbegin(), data.cend());
        std::cout << ") = " << max_sum(data) << "\n";
    };

    find_max_sum({1, 2, -5, 2, 5, -3, 7, -4});
    find_max_sum({-1, -2, -3});
    find_max_sum({1, 2, 3});
}
