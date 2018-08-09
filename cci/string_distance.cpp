#include "string.hpp"
#include <iostream>
#include <string>

int main() {
    std::string s1("Hello");
    std::string s2("Hull");
    std::cout << "Distance between " << s1 << " and " << s2 << " is "
              << cci::edit_distance1(s1.cbegin(), s1.cend(), s2.cbegin(),
                                     s2.cend())
              << "\n";
}
