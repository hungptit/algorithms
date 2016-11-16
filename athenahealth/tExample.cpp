#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"

class NumberOfPaths {
public:
  NumberOfPaths(const std::string &first, const std::string &second)
      : FirstString(first), SecondString(second), HashSet() {}

  void calculate(const std::string &results, const size_t firstIt, const size_t secondIt) {
    if (secondIt == SecondString.size()) {
      const std::string aKey = results + FirstString.substr(firstIt, FirstString.size() - firstIt);
      HashSet.emplace(aKey);
      return;
    }
    const char ch = SecondString[secondIt];
    auto pos = FirstString.find_first_of(ch, firstIt);
    for (auto idx = firstIt; pos != std::string::npos;) {
      const std::string prefix = results + FirstString.substr(firstIt, pos - firstIt);
      idx = pos + 1;
      calculate(prefix, idx, secondIt + 1);
      pos = FirstString.find_first_of(ch, idx);
    }
  }

  size_t getNumberOfPaths() const { return HashSet.size(); }

private:
  std::string FirstString;
  std::string SecondString;
  std::unordered_set<std::string> HashSet;
};

int main() {
  namespace po = boost::program_options;
  // po::options_description desc("Allowed options");

  // std::string firstMessage;
  // std::string secondMessage;

  // // clang-format off
  // desc.add_options()
  //   ("help,h", "produce help message")
  //   ("verbose","Dislay verbose information")
  //   ("first", po::value<std::string>(&firstMessage), "First message")
  //   ("second", po::value<std::string>(&secondMessage), "Second message");
  // // clang-format on

  // po::variables_map vm;
  // po::store(po::parse_command_line(argc, argv, desc), vm);
  // po::notify(vm);

  // if (vm.count("help")) {
  //     std::cout << desc;
  //     return 0;
  // }

  {
      std::string first("*-*");
      std::string second("*-*");
      std::cout << "First message: " << first << "\n";
      std::cout << "First message: " << second << "\n";
      NumberOfPaths p(first, second);
      std::string prefix;
      p.calculate(prefix, 0, 0);
      std::cout << "Number of paths: " << p.getNumberOfPaths() << "\n";
  }

  {
    std::string first("*-_-***");
    std::string second("*-*");
    std::cout << "First message: " << first << "\n";
    std::cout << "First message: " << second << "\n";
    NumberOfPaths p(first, second);
    p.calculate("", 0, 0);
    std::cout << "Number of paths: " << p.getNumberOfPaths() << "\n";
  }

  {
    std::string first("****_*_*-**_*-**_---___*--_---_*-*_*-**_-**");
    std::string second("****_*_*-**_*--*");
    std::cout << "First message: " << first << "\n";
    std::cout << "First message: " << second << "\n";
    NumberOfPaths p(first, second);
    std::string prefix;
    p.calculate("", 0, 0);
    std::cout << "Number of paths: " << p.getNumberOfPaths() << "\n";
  }
}
