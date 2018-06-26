#include "data.hpp"
#include "graph.hpp"
#include "traversal_policies.hpp"
#include "topological_sorting.hpp"
#include <string>
#include <vector>

namespace {
    template <typename Graph> void sorted_list(Graph &g) {
        g.print();
        using graph_type = Graph;
        using Policy = graph::algorithms::MinimumPolicy<graph_type>;
        graph::algorithms::TopologicalSort<Policy> dfs(g);
        bool isok = dfs.traverse();

        // Display results
        if (isok) {
            fmt::print("Sorted list:");
            for (auto item : dfs.sorted_list) {
                fmt::print(" {}", item);
            }
            fmt::print("\n");
        } else {
            fmt::print("The given graph has a cycle.\n");
        }
    }

} // namespace

int main() {
    // Has loop
    auto g1 = experiments::directed_graph_with_loop();
    sorted_list(g1);

    // Does not have loop
    auto g2 = experiments::directed_graph();
    sorted_list(g2);

    auto g3 = experiments::directed_graph2();
    sorted_list(g3);
}
