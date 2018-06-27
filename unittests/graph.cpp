#include <vector>
#include <string>
#include "data.hpp"
#include "graph.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

TEST_CASE("Minimum graph") {
    auto g = graph::test::minimum::directed_graph();
    g.print();
}
