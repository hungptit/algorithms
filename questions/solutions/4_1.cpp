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
    using Policy = graph::algorithms::BasicPolicy<graph_type>;
    graph::algorithms::DFS<Policy> dfs(g);
}
