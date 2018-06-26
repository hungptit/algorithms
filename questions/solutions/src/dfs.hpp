#pragma once

#include <vector>
#include "traversal_policies.hpp"
namespace graph {
    namespace algorithms {
        // A simple implementation of the DFS algorithm.
        template <typename Policy> struct DFS : public Policy {
            using index_type = typename Policy::index_type;
            using graph_type = typename Policy::graph_type;

            template <typename gtype, typename... Args>
            explicit DFS(gtype &&g, Args... args) : Policy(std::forward<gtype>(g), args...) {}

            // Perform non-recursive DFS traversal from given vertices.
            void traverse(const std::vector<index_type> &vids) {
                std::vector<index_type> stack(vids.cbegin(), vids.cend());
                while (!stack.empty()) {
                    auto vid = stack.back();
                    stack.pop_back();
                    Policy::visit(vid);
                    auto range = Policy::graph.edges(vid);
                    for (auto iter = range.begin; iter != range.end; ++iter) {
                        if (Policy::states[*iter] == NONE) {
                            stack.push_back(*iter);
                        }
                    }
                }
            }
        };
    } // namespace algorithms
} // namespace graph
