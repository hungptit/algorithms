#pragma once

#include "graph.hpp"
#include <string>
#include <vector>

namespace experiments {
    using index_type = unsigned int;
    using edge_type = typename graph::experiments::Edge<index_type>;
    using node_type = typename graph::experiments::BasicNode;
    using range_type = typename graph::experiments::Range<index_type>;
    using Graph = typename graph::experiments::Graph<node_type, index_type>;

    Graph directed_graph() {
        std::vector<node_type> nodes{{"Zero", 0},  {"One", 0},  {"Two", 0}, {"Three", 0},
                                     {"Four", 0},  {"Five", 0}, {"Six", 0}, {"Seven", 0},
                                     {"Eight", 0}, {"Nive", 0}, {"Ten", 0}};
        std::vector<edge_type> edges{{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 5}, {2, 7}, {4, 3},
                                     {4, 5}, {5, 6}, {6, 7}, {6, 9}, {7, 8}, {9, 8}};
        return Graph(nodes, edges);
    }

    Graph directed_graph_with_loop() {
        std::vector<node_type> nodes{{"Zero", 0},  {"One", 0},  {"Two", 0}, {"Three", 0},
                                     {"Four", 0},  {"Five", 0}, {"Six", 0}, {"Seven", 0},
                                     {"Eight", 0}, {"Nive", 0}, {"Ten", 0}};
        std::vector<edge_type> edges{{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 5}, {2, 7}, {4, 3},
                                     {4, 5}, {5, 6}, {6, 7}, {6, 9}, {7, 8}, {9, 8}, {9, 2}};
        return Graph(nodes, edges);
    }

    
} // namespace experiments
