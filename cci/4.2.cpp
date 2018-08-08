#include "tree.hpp"
#include <iostream>

int main() {
    {
        auto root = cci::binary_tree::test_tree1<int>();
        std::cout << "A simple tree:\n";
        cci::binary_tree::print<int>(root, 0);
        delete_tree(root);
    }

    {
        std::vector<int> data{1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto root = cci::binary_tree::create_tree1<decltype(data)::value_type>(data.cbegin(), data.cend());
        std::cout << "A tree constructed from a sorted vector:\n";
        cci::binary_tree::print<int>(root, 0);
        delete_tree(root);
    }
}
