#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace cci {

    template <typename T> struct Matrix {
        explicit Matrix(const int n) : N(n), data(N * N, 0) {}
        explicit Matrix(const int n, const std::vector<T> &x) : N(n), data(x.begin(), x.end()) {}

        T operator()(const int i, const int j) { return data[i * N + j]; }

        void print(const std::string &msg) const {
            std::cout << "---- " << msg << " ----\n";
            for (auto i = 0; i < N; ++i) {
                for (auto j = 0; j < N; ++j) {
                    std::cout << " " << std::setw(3) << data[i * N + j];
                }
                std::cout << "\n";
            }
        }

        // transpose the matrix
        void trans() {
            for (auto i = 0; i < N; ++i) {
                for (auto j = 0; j < i; ++j) {
                    T tmp = data[i * N + j];
                    data[i * N + j] = data[j * N + i];
                    data[j * N + i] = tmp;
                }
            }
        }

        // mirror-x
        void mirror_row() {
            for (auto i = 0; i < N; ++i) {
                const int M = N / 2;
                for (auto j = 0; j < M; ++j) {
                    T tmp = data[i * N + j];
                    data[i * N + j] = data[i * N + N - 1 - j];
                    data[i * N + N - 1 - j] = tmp;
                }
            }
        }

        int N;
        std::vector<T> data;
    };
} // namespace cci

namespace {
    template <typename T> void test() {
        cci::Matrix<T> x(4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
        x.print("Before");
        x.trans();
        x.mirror_row();
        x.print("After");
    }
} // namespace

int main() {
    test<int>();
    test<short>();
}
