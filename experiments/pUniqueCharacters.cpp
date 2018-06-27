#include "celero/Celero.h"
#include "UniqueCharacters.hpp"

constexpr int NumberOfSamples = 5000;
constexpr int NumberOfIterations = 10;

const std::string s = "abcdefghijABCDEFGHIJ12142432432535";
const std::vector<char> vs(s.begin(), s.end());

using namespace algorithms;

CELERO_MAIN

BASELINE(basic, bool, NumberOfSamples, NumberOfIterations) {  
  celero::DoNotOptimizeAway(is_unique<bool, decltype(s)>(s));
}

BENCHMARK(basic, unsigned_char, NumberOfSamples, NumberOfIterations) {
  celero::DoNotOptimizeAway(is_unique<unsigned char>(s));
}

BENCHMARK(basic, bool_vector_char, NumberOfSamples, NumberOfIterations) {
  celero::DoNotOptimizeAway(is_unique<bool>(vs));
}

BENCHMARK(basic, unsigned_char_vector_char, NumberOfSamples, NumberOfIterations) {
  celero::DoNotOptimizeAway(is_unique<unsigned char>(vs));
}

BENCHMARK(basic, vector_bool, NumberOfSamples, NumberOfIterations) {
  celero::DoNotOptimizeAway(is_unique_vector<bool>(vs));
}

BENCHMARK(basic, vector_unsigned_char, NumberOfSamples, NumberOfIterations) {
  celero::DoNotOptimizeAway(is_unique_vector<unsigned char>(vs));
}

BENCHMARK(basic, unordered_map, NumberOfSamples, NumberOfIterations) {
  celero::DoNotOptimizeAway(algorithms::is_unique_map(s));
}
