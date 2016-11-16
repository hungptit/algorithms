#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"

template <typename Container>
void print(Container &data, const std::string &msg) {
  std::cout << msg << "\n";
  std::for_each(data.begin(), data.end(), [](auto item) {
      std::cout << item << " ";
    });
  std::cout << "\n";
}

int main(int argc, char *argv[]) {
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");

    int number;
    std::vector<std::string> data;
    std::vector<int> idata;
    
    // clang-format off
    desc.add_options()
      ("help,h", "produce help message")
      ("verbose","Dislay verbose information")
      ("data,d", po::value<std::vector<std::string>>(&data), "Data")
      ("idata", po::value<std::vector<int>>(&idata), "Data")
      ("number,n", po::value<int>(&number)->default_value(0), "Number");
    // clang-format on

    po::positional_options_description p;
    p.add("data", -1);
    
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc;
        return 0;
    }

    print(data, "Test strings");
    print(idata, "Test intergers");
}
