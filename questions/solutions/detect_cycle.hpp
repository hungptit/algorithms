#pragma once
#include <vector>

namespace graph {
    namespace algorithms {
        template <typename Policy> struct LoopDetector : public Policy {
            using index_type = typename Policy::index_type;
            using graph_type = typename Policy::graph_type;
            explicit LoopDetector(graph_type &g) : Policy(g) {}

            // Perform non-recursive DFS traversal from given vertexes.
            bool traverse() {
                for (index_type v = 0; v < Policy::states.size(); ++v) {
                    if (Policy::states[v] != NONE) continue;
                    std::vector<index_type> stack{v};
                    while (!stack.empty()) {
                        auto vid = stack.back();
                        if (Policy::states[vid] == NONE) {
                            Policy::states[vid] = VISITED;
                        } else if (Policy::states[vid] == VISITED) {
                            Policy::states[vid] = PROCESSED;
                            stack.pop_back();
                        } else {
                            return true;
                        }

                        // Visit children.
                        auto range = Policy::graph.edges(vid);
                        for (auto iter = range.begin; iter != range.end; ++iter) {
                            auto const status = Policy::states[*iter];
                            if (status == NONE) {
                                stack.push_back(*iter);
                            }
                        }
                    }
                }
                return false;
            }
        };

    } // namespace algorithms
} // namespace graph
