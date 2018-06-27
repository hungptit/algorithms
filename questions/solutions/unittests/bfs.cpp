#include "bfs.hpp"
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
    graph::algorithms::minimum::BFS<Policy> bfs(g);

    // First run
    std::vector<index_type> vids1{2, 5, 7, 6, 8, 9};
    CHECK(bfs.traverse({2}) == vids1);

    // Second run
    bfs.reset_states();
    bfs.reset_results();
    auto results = bfs.traverse({5, 1});
    utils::print(results.cbegin(), results.cend());
    std::cout << "\n";
    std::vector<index_type> vids2{5, 1, 6, 0, 2, 4, 7, 9, 3, 8};
    CHECK(results == vids2);
}
