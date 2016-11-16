#include <iostream>
#include <vector>

#include "gtest/gtest.h"

namespace algorithms {

    void print_matrix(std::vector<int> &data, const size_t N) {
        std::cout << "--------------\n";
        for (size_t j = 0; j < N; ++j) {
            for (size_t i = 0; i < N; ++i) {
                std::cout << data[i + j * N] << " ";
            }
            std::cout << "\n";
        }
    }

    void transpose(std::vector<int> &x, const size_t N) {
        if (N < 2) return;

        print_matrix(x, N);
        // Do transpose x(i,j) = x(j,i)
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = i + 1; j < N; ++j) {
                int tmpValue = x[i + j * N];
                x[i + j * N] = x[j + i * N];
                x[j + i * N] = tmpValue;
            }
        }
        std::cout << "transpose\n";
        print_matrix(x, N);
    }

    void mirror(std::vector<int> &x, const size_t N) {
        if (N < 2) return;
        print_matrix(x, N);
        // Do mirror x(i,j) = x(i, N - j - 1)
        size_t len = N / 2;
        for (size_t j = 0; j < len; ++j) {
            for (size_t i = 0; i < N; ++i) {
                size_t firstIdx = i + j * N;
                size_t secondIdx = i + (N - j - 1) * N;

                std::cout << firstIdx << "<->" << secondIdx << "\n";
                
                int tmpValue = x[firstIdx];
                x[firstIdx] = x[secondIdx];
                x[secondIdx] = tmpValue;
            }
        }
        std::cout << "Mirror\n";
        print_matrix(x, N);
    }

    void rotate(std::vector<int> &x, const size_t N) {
        transpose(x, N);
        mirror(x, N);
    }
}

TEST(BasicTests, Positive) {
    using namespace algorithms;
    std::vector<int> data = {1, 4, 7, 2, 5, 8, 3, 6, 9};
    std::vector<int> expectedResults = {7, 8, 9, 4, 5, 6, 1, 2, 3};

    print_matrix(data, 3);
    print_matrix(expectedResults, 3);
    // x-> MxN, y -> NxM and x(i,j) == y(j, M - i);

    // transpose then do mirror.
    // 1, 2, 3    1 4 7    7 4 1
    // 4, 5, 6 => 2 5 8 => 8 5 2
    // 7, 8, 9    3 6 9    9 6 3

    rotate(data, 3);
    EXPECT_EQ(data, expectedResults);
}
