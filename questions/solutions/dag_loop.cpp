#include "data.hpp"
#include "graph.hpp"
#include "detect_cycle.hpp"
#include <string>
#include <vector>

// We will need two bfs operations to check that there is a path from node A to node B.
namespace graph {
    namespace algorithms {
    } // namespace algorithms

    template <typename Graph>
    bool detect_loop(Graph & g) {
        g.print();
        using graph_type = Graph;
        using Policy = graph::algorithms::BasicPolicy<graph_type>;
        graph::algorithms::LoopDetector<Policy> dfs(g);
        return dfs.traverse();
    }
    
} // namespace graph

int main() {
    // Has loop
    auto g1 = experiments::directed_graph_with_loop();
    fmt::print("The given graph {}\n", (graph::detect_loop<decltype(g1)>(g1) ? "has a cycle." : "is DAG."));

    // Does not have loop
    auto g2 = experiments::directed_graph();
    fmt::print("The given graph {}\n", graph::detect_loop(g2) ? "has loop." : "is DAG.");
}
