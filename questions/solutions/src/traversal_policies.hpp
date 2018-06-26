#pragma once

#include <vector>
#include "fmt/format.h"

namespace graph {
    namespace algorithms {
        enum Status : uint8_t { NONE, VISITED, PROCESSED };

        template <typename Graph> struct MinimumPolicy {
            using graph_type = Graph;
            using index_type = typename graph_type::index_type;
            explicit MinimumPolicy(Graph &g) : graph(g), states(g.get_number_of_vertices(), NONE) {}
            void reset_states() {
                states.assign(states.size(), NONE); // Reset node status
            }
            graph_type graph;
            std::vector<index_type> states;
        };

        template <typename Graph> struct BasicPolicy {
            using graph_type = Graph;
            using index_type = typename graph_type::index_type;
            explicit BasicPolicy(Graph &g) : graph(g), states(g.get_number_of_vertices(), NONE) {}
            void reset_states() {
                states.assign(states.size(), NONE); // Reset node status
            }

            void visit(const index_type vid) {
                if (states[vid] == NONE) {
                    states[vid] = VISITED;
                    fmt::print("visit: {}\n", vid);
                }
            }
            graph_type graph;
            std::vector<index_type> states;
        };

    } // namespace algorithms
} // namespace graph
