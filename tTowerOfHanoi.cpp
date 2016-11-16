#include <algorithm>
#include <iostream>
#include <vector>

using Stack = std::vector<int>;

void print(const Stack &data, const std::string &msg) {
    std::cout << "---" << msg << "---\n";
    std::for_each(data.rbegin(), data.rend(), [](auto item) { std::cout << item << "\n"; });
}

// Move the discs from a -> c
void move(Stack &a, Stack &b, Stack &c, const int N) {
    if (N == 1) {
        c.push_back(a.back());
        a.pop_back(); 
    } else {
        // Move N-1 discs from a to b
        move(a, c, b, N - 1);

        // Move the last disc from a to c
        c.push_back(a.back());
        a.pop_back();

        // Move discs from b to c
        move(b, a, c, N - 1);
    }
}

int main() {
    {
        Stack a{8, 5, 3}, b{}, c{};
        move(a, b, c, a.size());
        print(a, "a");
        print(b, "b");
        print(c, "c");
    }

    {
      Stack a{10, 8, 5, 3}, b{}, c{};
        move(a, b, c, a.size());
        print(a, "a");
        print(b, "b");
        print(c, "c");
    }

    {
      Stack a{20, 16, 12, 10, 8, 5, 3}, b{}, c{};
      move(a, b, c, a.size());
      print(a, "a");
      print(b, "b");
      print(c, "c");
    }
}
