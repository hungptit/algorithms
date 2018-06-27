#include <iostream>
#include <tuple>

/**
 * Compute the Fibonaci number at compile time using an optimum algorithm.
 *
 * @return A tuple which contains two consecutive Fibonaci numbers f{k} and
 * f_{k-1}
 */
template <size_t N>
constexpr std::tuple<size_t, size_t> fibonaci() {
    constexpr auto fk = fibonaci<N - 1>();
    return std::make_tuple(std::get<0>(fk) + std::get<1>(fk), std::get<0>(fk));
}

template <>
constexpr std::tuple<size_t, size_t> fibonaci<0>() {
    return std::make_tuple(1, 1);
}

template <size_t N>
void print() {
    constexpr std::tuple<size_t, size_t> f = fibonaci<N>();
    std::cout << "f(" << N << ") = (" << std::get<0>(f) << "," << std::get<1>(f)
              << ")" << std::endl;
}

int main() {
    print<0>();
    print<4>();
    print<10>();
    print<100>();
    return 0;
}
