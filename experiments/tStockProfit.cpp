#include <iostream>
#include <vector>
// This is the text editor interface.
// Anything you type or change here will be seen by the other person in real time.

// Given an array where each element is the closing stock price at day i. If you are only permitted to
// perform "at most one" round-trip transaction(buy and then sell). Design an algorithm to find the maximum
// profit
// [10, 15, 5, 7, 16, 12] = 11
//  1,   2, 3, 4, 5, 6

int find_max_diff(const std::vector<int> &data) {
    size_t N = data.size();
    if (N < 2) {
        return 0;
    } else {
        int max_gain = data[1] - data[0];
        int gain = max_gain;
        for (size_t idx = 1; idx < (N - 1); ++idx) {
            int diff = data[idx + 1] - data[idx];
            if (diff > 0) {
                gain += diff;
            } else {
                if (gain > max_gain) {
                    max_gain = gain;
                }
                gain = 0;
            }
        }
        return max_gain;
    }
}

int main() {
    {
        std::vector<int> x{10};
        std::cout << "max gain: " << find_max_diff(x) << "\n";
    }

    {
        std::vector<int> x{10, 15, 5, 7, 16, 12};
        std::cout << "max gain: " << find_max_diff(x) << "\n";
    }
}
