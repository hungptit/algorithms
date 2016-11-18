#include "boost/unordered_map.hpp"
#include <iostream>
#include <vector>

#include "utils/Timer.hpp"

using Bucket = std::vector<int>;

void print(Bucket &buckets) {
    std::for_each(buckets.begin(), buckets.end(), [](auto item) { std::cout << item << " "; });
    std::cout << "\n";
}

class CountAllPermutations {
  public:
    size_t count(Bucket &buckets, size_t numsols) {
        size_t numberOfSolutions = numsols;
        bool isEmpty = std::all_of(buckets.cbegin(), buckets.cend(), [](auto value) { return value == 0; });

        if (isEmpty) {
            numberOfSolutions++;
            return numberOfSolutions;
        };

        for (size_t idx = 0; idx < buckets.size(); ++idx) {
            const int value = buckets[idx];
            if (value > 0) {
                Bucket newBuckets(buckets);
                newBuckets[idx] = value - 1;
                numberOfSolutions = count(newBuckets, numberOfSolutions);
            }
        }

        return numberOfSolutions;
    }
};

int main() {
    {
        utils::ElapsedTime<utils::MILLISECOND> t("Run time: ");
        Bucket buckets{2, 1};
        CountAllPermutations alg;
        std::cout << "Number of valid solutions: " << alg.count(buckets, 0) << "\n";
    }

    {
        Bucket buckets{2, 1, 2, 2};
        CountAllPermutations alg;
        std::cout << "Number of valid solutions: " << alg.count(buckets, 0) << "\n;
    }

    return 0;
}
