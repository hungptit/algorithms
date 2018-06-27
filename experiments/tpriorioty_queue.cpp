#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

template <typename T> void print(T &&data, const std::string &title = "") {
    std::cout << title << ':';
    std::for_each(data.begin(), data.end(), [](auto value) { std::cout << value << " "; });
    std::cout << '\n';
}

template <typename T> void print_queue(T &&q, const std::string &title = "priority_queue") {
    std::cout << title << ": ";
    while (!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> data{1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
    std::priority_queue<int, decltype(data), std::less<int>> q(data.begin(), data.end());

    print(data, "test data: ");
    print_queue(q, "Min queue");

    std::priority_queue<int, std::vector<int>, std::greater<int>> q2(data.begin(), data.end());
    ;
    print_queue(q2, "Max queue");

    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { return (left > right); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(data.begin(), data.end(), cmp);

    print_queue(q3, "Lambda comparator");
}
