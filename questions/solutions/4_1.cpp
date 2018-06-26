#include "data.hpp"
#include "graph.hpp"
#include "traversal_policies.hpp"
#include <string>
#include <vector>

// We will need two bfs operations to check that there is a path from node A to node B.
namespace {
    // A simple implementation of a pre-order BFS traversal.
    template <typename Policy> struct BFS : public Policy {
        using index_type = typename Policy::index_type;
        using graph_type = typename Policy::graph_type;
        explicit BFS(graph_type &g) : Policy(g) {}

        // Perform non-recursive DFS traversal from given vertexes.
        bool traverse(const index_type v1, const index_type v2) {
            if (v1 == v2) return true;
            std::deque<index_type> queue{v1};
            while (!queue.empty()) {
                auto vid = queue.front();
                if (vid == v2) return true; // Terminate the search if we reach the
                queue.pop_front();
                Policy::visit(vid);
                auto range = Policy::graph.edges(vid);
                for (auto iter = range.begin; iter != range.end; ++iter) {
                    if (Policy::states[*iter] == graph::algorithms::NONE) {
                        queue.push_back(*iter);
                    }
                }
            }
            return false;
        }
    };
} // namespace

int main() {
    auto g = experiments::directed_graph();
    g.print();
    using graph_type = decltype(g);
    using index_type = typename graph_type::index_type;
    // Modify BFS so we can terminate early after a path is found.
    using Policy = graph::algorithms::BasicPolicy<graph_type>;
    BFS<Policy> dfs(g);

    auto find = [&dfs](index_type v1, index_type v2) {
        fmt::print("{0} path from ({1}) to ({2})\n", dfs.traverse(v1, v2) ? "Found a" : "Cannot find any",
                   v1, v2);
    };

    // Tests
    find(1, 8);

    dfs.reset_states();
    find(0, 8);

    dfs.reset_states();
    find(5, 8);

    dfs.reset_states();
    find(8, 1);
}
