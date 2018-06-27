#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "celero/Celero.h"

using IndexContainer = std::vector<int>;
using CounterContainer = std::vector<int>;

namespace {
    template <typename Container> void print(Container &&data, const std::string &msg) {
        std::cout << msg << "\n";
        std::for_each(data.cbegin(), data.cend(), [](auto val) { std::cout << val << " "; });
        std::cout << "\n";
    }

    auto createData(const std::string &s) {
        std::unordered_map<char, int> table;
        for (auto const ch : s) {
            table[ch] += 1;
        }

        CounterContainer counter(table.size(), 0);
        std::vector<char> characters(table.size(), 0);

        size_t idx = 0;
        for (auto const item : table) {
            characters[idx] = item.first;
            counter[idx] = item.second;
            ++idx;
        }
        return std::make_tuple(characters, counter);
    }
}

class FindAllPermutations {
  public:
    FindAllPermutations() : Permutations(), Counter(0) {}

    void find(const CounterContainer &counter, const IndexContainer &indexes) {
        bool isEmpty = std::all_of(counter.cbegin(), counter.cend(), [](auto val) { return val == 0; });
        if (isEmpty) {
            Permutations.emplace_back(indexes);
            Counter++;
            return;
        }

        for (size_t idx = 0; idx < counter.size(); ++idx) {
            const int value = counter[idx];
            if (value > 0) {
                CounterContainer newCounter(counter);
                newCounter[idx] = value - 1;
                IndexContainer newIndexes(indexes);
                newIndexes.push_back(idx);
                find(newCounter, newIndexes);
            }
        }
    }

    void disp(std::vector<char> &) { std::cout << "Number of unique solutions: " << Counter << "\n"; }

  private:
    std::vector<IndexContainer> Permutations;
    size_t Counter;
};

class FindAllPermutations_Simple {
  public:
    FindAllPermutations_Simple(const CounterContainer &input) : counter(input) {}

    size_t find(const size_t nsols) {
        bool isEmpty = std::all_of(counter.cbegin(), counter.cend(), [](auto val) { return val == 0; });
        if (isEmpty) {
            return nsols + 1;
        }

        size_t numberOfSolutions(nsols);
        for (size_t idx = 0; idx < counter.size(); ++idx) {
            const int value = counter[idx];
            if (value > 0) {
                counter[idx] = value - 1;
                numberOfSolutions = find(numberOfSolutions);
                counter[idx] = value;
            }
        }
        return numberOfSolutions;
    }

  private:
    CounterContainer counter;
};

class FindAllPermutations_Iter {
  public:
    FindAllPermutations_Iter(const CounterContainer &input) : counter(input) {}

    size_t find(const size_t nsols) {
        bool isEmpty = std::all_of(counter.cbegin(), counter.cend(), [](auto val) { return val == 0; });
        if (isEmpty) {
            return nsols + 1;
        }

        size_t numberOfSolutions(nsols);
        for (auto it = counter.begin(); it != counter.end(); ++it) {
            auto const value = *it;
            if (value > 0) {
                *it = value - 1;
                numberOfSolutions = find(numberOfSolutions);
                *it = value;
            }
        }
        return numberOfSolutions;
    }

  private:
    CounterContainer counter;
};

size_t find_recursive_version_1(const CounterContainer &counter, const size_t numsols) {
    bool isEmpty = std::all_of(counter.cbegin(), counter.cend(), [](auto val) { return val == 0; });
    if (isEmpty) {
        return numsols + 1;
    }

    size_t N(numsols);

    for (size_t idx = 0; idx < counter.size(); ++idx) {
        const int value = counter[idx];
        if (value > 0) {
            CounterContainer newCounter(counter);
            newCounter[idx] = value - 1;
            N = find_recursive_version_1(newCounter, N);
        }
    }
    return N;
}

size_t find_recursive_version_2(CounterContainer &counter, const size_t numsols) {
    bool isEmpty = std::all_of(counter.cbegin(), counter.cend(), [](auto val) { return val == 0; });
    if (isEmpty) {
        return numsols + 1;
    }

    size_t N(numsols);

    for (size_t idx = 0; idx < counter.size(); ++idx) {
        const int value = counter[idx];
        if (value > 0) {
            counter[idx] = value - 1;
            N = find_recursive_version_2(counter, N);
            counter[idx] = value;
        }
    }
    return N;
}

size_t find_iterative_version_1(const CounterContainer &counter) {
  std::vector<CounterContainer> stack{counter};
    size_t numsols = 0;

    while (!stack.empty()) {
        auto aCounter = stack.back();
        stack.pop_back();

        bool isEmpty = std::all_of(aCounter.cbegin(), aCounter.cend(), [](auto val) { return val == 0; });
        if (isEmpty) {
            numsols++;
            continue;
        }

        for (size_t idx = 0; idx < aCounter.size(); ++idx) {
            const int value = aCounter[idx];
            if (value > 0) {
                CounterContainer newCounter(aCounter);
                newCounter[idx] = value - 1;
                stack.emplace_back(newCounter);
            }
        }
    }
    return numsols;
}

size_t find_iterative_version_2(const CounterContainer &input) {
    CounterContainer counter(input);
    std::vector<size_t> stack{};
    size_t numsols = 0;

    while (!stack.empty()) {

        bool isEmpty = std::all_of(counter.cbegin(), counter.cend(), [](auto val) { return val == 0; });
        if (isEmpty) {
            numsols++;
            continue;
        }

        for (size_t idx = 0; idx < counter.size(); ++idx) {
            const int value = counter[idx];
            if (value > 0) {
              
            }
        }
    }
    return numsols;
}

void search(const std::string &s) {
    CounterContainer counter;
    std::vector<char> characters;
    std::tie(characters, counter) = createData(s);

    print(counter, "Counter");
    print(characters, "Characters");

    IndexContainer indexes;

    // auto numsols = find1(counter, 0);
    // std::cout << "Number of solutions: " << numsols << "\n";

    std::cout << "Number of solutions: " << find_iterative_version_1(counter) << "\n";

    // FindAllPermutations alg;
    // alg.find(counter, indexes);
    // alg.disp(characters);
}

constexpr int NumberOfSamples = 2;
constexpr int NumberOfIterations = 2;

std::string s("abcdeeffgh");
auto data = createData(s);

CELERO_MAIN

BASELINE(combinatorial_search, class_simple, NumberOfSamples, NumberOfIterations) {
    FindAllPermutations_Simple alg(std::get<1>(data));
    std::cout << "Number of solutions: " << alg.find(0) << "\n";
}

BENCHMARK(combinatorial_search, class_iter, NumberOfSamples, NumberOfIterations) {
    FindAllPermutations_Iter alg(std::get<1>(data));
    std::cout << "Number of solutions: " << alg.find(0) << "\n";
}


BENCHMARK(combinatorial_search, recursive_version_1, NumberOfSamples, NumberOfIterations) {
    std::cout << "Number of solutions: " << find_recursive_version_1(std::get<1>(data), 0) << "\n";
}

BENCHMARK(combinatorial_search, recursive_version_2, NumberOfSamples, NumberOfIterations) {
    std::cout << "Number of solutions: " << find_recursive_version_2(std::get<1>(data), 0) << "\n";
}

BENCHMARK(combinatorial_search, iterative, NumberOfSamples, NumberOfIterations) {
    std::cout << "Number of solutions: " << find_iterative_version_1(std::get<1>(data)) << "\n";
}

// int main() {
//     search("alll");
//     search("Hello");
//     search("abcdeefffgh");
// }
