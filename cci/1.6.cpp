#include <iostream>
#include <string>

namespace cci {
    // The complexity of this algorithm is O(n), where n is the size of the given string.
    // How can we do better?
    // Terminate early.
    std::string compress(const std::string &input) {
        std::string results;

        // Preallocate memory to improve the performance.
        results.reserve(input.size());
        
        auto it = input.cbegin();
        int count = 1;
        auto prev = it;
        ++it;
        for (; it != input.cend(); ++it) {
            if (*it == *prev) {
                ++count;
            } else {
                results.push_back(*prev);
                results.append(std::to_string(count));

                // Terminate early if the compression algorithm is not helpful.
                // if (results.size() >= input.size()) {
                //     return input;
                // }
                
                count = 1;
                prev = it;
            }
        }

        // Process the rest
        if (prev != input.cend()) {
            results.push_back(*prev);
            results.append(std::to_string(count));
        }

        // std::cout << results << "\n";
        return (results.size() < input.size()) ? results : input;
    }
} // namespace cci

namespace {
    void test(const std::string &s) { std::cout << s << " -> " << cci::compress(s) << "\n"; }
} // namespace

int main() {
    test("aabcccccaaa");
    test("Hello");
}
