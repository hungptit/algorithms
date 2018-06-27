#pragma once

#include "fmt/format.h"
#include <vector>

namespace graph {
    namespace algorithms {
        enum Status : uint8_t { NONE, VISITED, PROCESSED };

        namespace minimum {
            template <typename Graph> struct MinimumPolicy {
                using graph_type = Graph;
                using index_type = typename graph_type::index_type;
                using result_type = std::vector<index_type>;
                using state_type = std::vector<Status>;

                explicit MinimumPolicy(Graph &g)
                    : graph(g), states(g.get_number_of_vertices(), NONE) {}

                void reset_states() {
                    states.assign(states.size(), NONE); // Reset node status
                }

                void reset_results() { results.clear(); }

                const result_type &get_results() const { return results; }

                graph_type graph;
                std::vector<index_type> states;
                std::vector<index_type> results;
            };

            template <typename Graph> struct BasicPolicy {
                using graph_type = Graph;
                using index_type = typename graph_type::index_type;
                using result_type = std::vector<index_type>;
                using state_type = std::vector<Status>;
                explicit BasicPolicy(Graph &g)
                    : graph(g), states(g.get_number_of_vertices(), NONE) {}

                void reset_states() {
                    states.assign(states.size(), NONE); // Reset node status
                }

                void reset_results() { results.clear(); }

                const result_type &get_results() const { return results; }

                void visit(const index_type vid) {
                    if (states[vid] == NONE) {
                        states[vid] = VISITED;
                        results.push_back(vid);
                    }
                }
                graph_type graph;
                state_type states;
                result_type results;
            };
        } // namespace minimum
    } // namespace algorithms
} // namespace graph
