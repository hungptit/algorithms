#include "dfs.hpp"
#include "data.hpp"
#include "graph.hpp"
#include "utils.hpp"
#include <string>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

TEST_CASE("minimum-dfs-preorder") {
    auto g = graph::test::minimum::directed_graph();
    using index_type = decltype(g)::index_type;
    g.print();
    using graph_type = decltype(g);
    using Policy = graph::algorithms::minimum::BasicPolicy<graph_type>;
    graph::algorithms::DFS<Policy> dfs(g);

    // First run
    std::vector<index_type> vids1{2, 7, 8, 5, 6, 9};
    CHECK(dfs.traverse({2}) == vids1);

    // Second run
    dfs.reset_states();
    dfs.reset_results();
    auto results = dfs.traverse({1,5});
    utils::print(results.cbegin(), results.cend());
    std::vector<index_type> vids2{5, 6, 9, 8, 7, 1, 4, 3, 2, 0};
    CHECK(results == vids2);
}
