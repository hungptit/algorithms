#include "data.hpp"
#include "graph.hpp"
#include <string>
#include <vector>

namespace {
    enum Status : uint8_t { NONE, VISITED, PROCESSED };

    template <typename Graph> struct DFS {
        using index_type = unsigned int;
        explicit DFS(Graph &g) : graph(g), states(g.get_number_of_vertexes(), NONE) {}

        // Perform DFS traversal from given vertex.
        void pre_order(const std::vector<index_type> &vids) {
            std::vector<index_type> stack(vids.cbegin(), vids.cend());
            while (!stack.empty()) {
                auto vid = stack.back();
                stack.pop_back();
                visit(vid);
                auto range = graph.edges(vid);
                for (auto iter = range.begin; iter != range.end; ++iter) {
                    if (states[*iter] == NONE) { // Only check in a vertex if it has not been visited yet.
                        stack.push_back(*iter);
                    }
                }
            }
        }

        void reset_states() {
            states.assign(states.size(), NONE); // Reset node status
        }

        void visit(const index_type vid) {
            if (states[vid] == NONE) {
                states[vid] = VISITED;
                fmt::print("visit: {}\n", vid);
            }
        }

        Graph graph;
        std::vector<index_type> states;
    };
} // namespace

int main() {
    auto g = experiments::directed_graph();
    g.print();
    using graph_type = decltype(g);
    DFS<graph_type> dfs(g);

    // Visit node 0.
    dfs.pre_order({0});

    // Visit node 1.
    dfs.pre_order({1});
}
