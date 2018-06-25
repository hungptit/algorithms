#include "data.hpp"
#include "graph.hpp"
#include <string>
#include <vector>

namespace {
    
} // namespace

int main() {
    auto g = experiments::directed_graph();
    g.print();
    using graph_type = decltype(g);
    graph::algorithms::DFS<graph_type> dfs(g);

    // Visit node 0.
    dfs.pre_order({0});

    // Visit node 1.
    dfs.pre_order({1});

    // Reset the node status and visit node 2
    {
        dfs.reset_states();
        const graph_type::index_type vid = 2;
        fmt::print("---- dfs({}) ----\n", vid);
        dfs.pre_order({vid});
    }

    // Visit several nodes at the same time.
    {
        dfs.reset_states();
        fmt::print("---- dfs(1, 5) ----\n");
        dfs.pre_order({1, 5});
    }
}
