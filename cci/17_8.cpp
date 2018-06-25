#include <iostream>
#include <tuple>
#include <vector>

namespace {
    struct Person {
        int weight;
        int height;
    };

    bool operator>(const Person &a, const Person &b) {
        return std::tie(a.weight, a.height) > std::tie(b.weight, b.height);
    }

    bool operator<(const Person &a, const Person &b) {
        return std::tie(a.weight, a.height) < std::tie(b.weight, b.height);
    }

    bool operator==(const Person &a, const Person &b) {
        return std::tie(a.weight, a.height) == std::tie(b.weight, b.height);
    }
    using container_type = std::vector<Person>;

    void print(const container_type &data) {
        if (data.empty()) return;
        auto iter = data.cbegin();
        std::cout << "(" << iter->weight << "," << iter->height << ")";
        ++iter;
        for (; iter != data.cend(); ++iter) {
            std::cout << " (" << iter->weight << "," << iter->height << ")";
        }
        std::cout << "\n";
    }

    // The complexity of this algorithm is O(n^2)
    struct CircusTower {
        void search(const container_type &data) {
            size_t N = data.size();
            size_t max_height = 0;
            for (size_t i = 0; i < (N - 1); ++i) {
                size_t current_height = 1;
                Person prev = data[i];
                for (size_t j = i + 1; j < N; ++j) {
                    if (is_valid(prev, data[j])) {
                        prev = data[j];
                        ++current_height;
                    }
                }
                max_height = std::max(max_height, current_height);
            }
            print(data);
            std::cout << "max height: " << max_height << "\n";
        }

        bool is_valid(const Person &a, const Person &b) {
            return (a.weight <= b.weight) && (a.height <= b.height);
        }
    };

} // namespace
int main() {
    CircusTower tower;
    {
        container_type data1{{65, 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 100}};
        std::sort(data1.begin(), data1.end());
        tower.search(data1);
    }
    
    {
        container_type data1{{65, 160}, {70, 150}, {66, 90}};
        std::sort(data1.begin(), data1.end());
        tower.search(data1);
    }
}
