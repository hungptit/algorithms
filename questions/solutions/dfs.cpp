#include "data.hpp"
#include "graph.hpp"
#include <string>
#include <vector>

int main() {
    auto g = experiments::directed_graph();
    g.print();
    using graph_type = decltype(g);
    using Policy = graph::algorithms::BasicPolicy<graph_type>;
    graph::algorithms::DFS<Policy> dfs(g);

    // Reset the node status and visit node 2
    {
        dfs.reset_states();
        const graph_type::index_type vid = 2;
        fmt::print("---- dfs({}) ----\n", vid);
        dfs.pre_order({vid});
    }

    // // Visit several nodes at the same time.
    // {
    //     dfs.reset_states();
    //     fmt::print("---- dfs(1, 5) ----\n");
    //     dfs.pre_order({1, 5});
    // }
}
