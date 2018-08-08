#include <iostream>
#include <string>
#include <vector>

namespace cci {
    // The runtime complexity of pop, push, and min is O(1), however,
    // we do need O(N) memory to hold min values.
    template <typename T> class MyStack {
      public:
        void push(T val) {
            data.push_back(val);
            if (!min_values.empty()) {
                min_values.push_back(std::min(val, min_values.back()));
            } else {
                min_values.push_back(val);
            }
        }

        T pop() {
            T val = data.back();
            min_values.pop_back();
            data.pop_back();
            return val;
        }

        T min() const { return min_values.back(); }

      private:
        std::vector<T> data;
        std::vector<T> min_values;
    };
} // namespace cci

namespace {
    template <typename T> void test() {
        cci::MyStack<T> stack;
        stack.push(2);
        std::cout << "min => " << stack.min() << "\n";
        stack.push(4);
        std::cout << "min => " << stack.min() << "\n";
        stack.push(1);
        std::cout << "min => " << stack.min() << "\n";
        stack.push(0);
        std::cout << "min => " << stack.min() << "\n";
        stack.pop();
        std::cout << "min => " << stack.min() << "\n";
        stack.push(-1);
        std::cout << "min => " << stack.min() << "\n";
    }
} // namespace

int main() {
    test<int>();
    test<double>();
}
