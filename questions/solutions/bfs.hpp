#pragma once

namespace graph {
    namespace algorithms {
        // A simple implementation of the BFS algorithm.
        template <typename Policy> struct BFS : public Policy {
            using index_type = typename Policy::index_type;
            using graph_type = typename Policy::graph_type;
            explicit BFS(graph_type &g) : Policy(g) {}

            // Perform non-recursive DFS traversal from given vertices.
            void traverse(const std::vector<index_type> &vids) {
                std::deque<index_type> queue(vids.cbegin(), vids.cend());
                while (!queue.empty()) {
                    auto vid = queue.front();
                    queue.pop_front();
                    Policy::visit(vid);
                    auto range = Policy::graph.edges(vid);
                    for (auto iter = range.begin; iter != range.end; ++iter) {
                        if (Policy::states[*iter] == NONE) {
                            queue.push_back(*iter);
                        }
                    }
                }
            }
        };

    } // namespace algorithms
} // namespace graph
