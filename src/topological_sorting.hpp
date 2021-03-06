#pragma once
#include "traversal_policies.hpp"
#include <algorithm>
#include <vector>

namespace graph {
    namespace algorithms {
        namespace minimum {
            template <typename Policy> struct LoopDetector : public Policy {
                using index_type = typename Policy::index_type;
                using graph_type = typename Policy::graph_type;
                explicit LoopDetector(graph_type &g) : Policy(g) {}

                // Perform non-recursive DFS traversal from given vertexes.
                bool traverse() {
                    for (index_type v = 0; v < Policy::states.size(); ++v) {
                        if (Policy::states[v] != NONE)
                            continue;
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

            template <typename Policy> struct TopologicalSort : public Policy {
                using index_type = typename Policy::index_type;
                using graph_type = typename Policy::graph_type;
                explicit TopologicalSort(graph_type &g) : Policy(g) {}
                bool traverse() {
                    std::vector<index_type> results;
                    for (index_type v = 0; v < Policy::states.size(); ++v) {
                        if (Policy::states[v] != NONE)
                            continue;
                        bool isok = visit(v);
                        if (!isok)
                            return false; // Found a loop
                    }
                    return true;
                }

                bool visit(const index_type v) {
                    std::vector<index_type> stack{v};
                    while (!stack.empty()) {
                        auto vid = stack.back();
                        if (Policy::states[vid] == NONE) {
                            Policy::states[vid] = VISITED;
                        } else if (Policy::states[vid] == VISITED) {
                            Policy::states[vid] = PROCESSED;
                            stack.pop_back();
                            sorted_list.push_front(vid);
                        } else {
                            return false; // Found a cycle
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
                    return true;
                }

                // Keep a found sorted list.
                std::deque<index_type> sorted_list;
            };

            template <typename Policy> struct TopologicalSortRecursive : public Policy {
                using index_type = typename Policy::index_type;
                using graph_type = typename Policy::graph_type;
                explicit TopologicalSortRecursive(graph_type &g) : Policy(g) {}
                bool traverse() {
                    std::vector<index_type> results;
                    for (index_type v = 0; v < Policy::states.size(); ++v) {
                        if (Policy::states[v] != NONE)
                            continue;
                        bool isok = visit(v);
                        if (!isok)
                            return false; // Found a loop
                    }
                    return true;
                }

                bool visit(const index_type vid) {
                    if (Policy::states[vid] == PROCESSED) {
                        return true;
                    } else if (Policy::states[vid] == VISITED) {
                        return false; // Found a loop.
                    }

                    Policy::states[vid] = VISITED;

                    // Visit children.
                    auto range = Policy::graph.edges(vid);
                    for (auto iter = range.begin; iter != range.end; ++iter) {
                        visit(*iter);
                    }

                    // Update parent status and the sorted list.
                    Policy::states[vid] = VISITED;
                    sorted_list.push_front(vid);
                    return true;
                }

                // Keep a found sorted list.
                std::deque<index_type> sorted_list;
            };
        } // namespace minimum
    } // namespace algorithms
} // namespace graph
