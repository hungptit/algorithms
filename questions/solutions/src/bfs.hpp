#pragma once

#include "traversal_policies.hpp"
#include <deque>
#include <vector>

namespace graph {
    namespace algorithms {
        namespace minimum {
            // A non-revursive implementation of the BFS algorithm.
            template <typename Policy> struct BFS : public Policy {
                using index_type = typename Policy::index_type;
                using graph_type = typename Policy::graph_type;
                explicit BFS(graph_type &g) : Policy(g) {}

                // Perform non-recursive DFS traversal from given vertices.
                auto traverse(const std::vector<index_type> &vids) {
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
                    return Policy::results;
                }
            };
        } // namespace minimum
    } // namespace algorithms
} // namespace graph
