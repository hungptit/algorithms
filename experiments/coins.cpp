#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

void print(std::vector<int> &solutions) {
    std::for_each(solutions.begin(), solutions.end(), [](auto item) { std::cout << item << " "; });
    std::cout << "\n";
}

class MinNumberOfCoints {
  public:
    int min(const int val) {
        std::vector<int> solutions(val + 1, 0);
        for (int idx = 1; idx <= val; ++idx) {
            int count = idx;
            for (size_t coinIdx = 0; coinIdx < Coins.size(); ++coinIdx) {
                auto currentCoin = Coins[coinIdx];
                if (idx > currentCoin) {
                    count = std::min(count, 1 + solutions[idx - currentCoin]);
                } else if (idx == currentCoin) {
                    count = std::min(count, 1);
                }
            }
            solutions[idx] = count;
        }

        // For debugging purpose.
        // print(solutions);

        return solutions[val];
    }

  private:
    std::vector<int> Coins{1, 5, 8, 10, 15, 25};
};

int main() {
    MinNumberOfCoints solver;

    {
        int value = 5;
        std::cout << "Minimum number of coins for " << value << " is " << solver.min(value) << "\n";
    }

    {
        int value = 9;
        std::cout << "Minimum number of coins for " << value << " is " << solver.min(value) << "\n";
    }

    {
        int value = 21;
        std::cout << "Minimum number of coins for " << value << " is " << solver.min(value) << "\n";
    }
}
