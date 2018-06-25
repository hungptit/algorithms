#include "data.hpp"
#include "graph.hpp"
#include <string>
#include <vector>

int main() {
    auto g = experiments::directed_graph();
    g.print();
    using graph_type = decltype(g);
    using Policy = graph::algorithms::BasicPolicy<graph_type>;
    graph::algorithms::BFS<Policy> bfs(g);

    // Reset the node status and visit node 2
    {
        bfs.reset_states();
        const graph_type::index_type vid = 2;
        fmt::print("---- bfs({}) ----\n", vid);
        bfs.pre_order({vid});
    }

    // Visit several nodes at the same time.
    {
        bfs.reset_states();
        fmt::print("---- bfs(1, 5) ----\n");
        bfs.pre_order({1, 5});
    }
}