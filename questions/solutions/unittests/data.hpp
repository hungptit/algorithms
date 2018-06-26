#pragma once

#include "data_structures.hpp"
#include "graph.hpp"
#include "utils.hpp"
#include <string>
#include <vector>

namespace graph {
    namespace test {

        using index_type = unsigned int;
        using weight_type = int;
        using edge_type = typename graph::BasicEdge<index_type>;
        using node_type = typename graph::WeightedNode<weight_type>;
        using range_type = typename graph::Range<index_type>;
        using Graph = typename graph::simple::Graph<node_type, edge_type>;

        Graph directed_graph() {
            std::vector<node_type> nodes{{"Zero", 0},  {"One", 0},  {"Two", 0}, {"Three", 0},
                                         {"Four", 0},  {"Five", 0}, {"Six", 0}, {"Seven", 0},
                                         {"Eight", 0}, {"Nine", 0}, {"Ten", 0}};
            std::vector<edge_type> edges{{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 5}, {2, 7}, {4, 3},
                                         {4, 5}, {5, 6}, {6, 7}, {6, 9}, {7, 8}, {9, 8}};
            return Graph(nodes, edges);
        }

        // This graph data is obtained from
        // https://en.wikipedia.org/wiki/Topological_sorting#Depth-first_search.
        Graph directed_graph2() {
            std::vector<node_type> nodes{{"One", 0},  {"Two", 0}, {"Three", 0}, {"Four", 0},
                                         {"Five", 0}, {"Six", 0}, {"Seven", 0}, {"Eight", 0},
                                         {"Nine", 0}, {"Ten", 0}, {"Ten", 0},   {"Eleven", 0}};
            std::vector<edge_type> edges{{5, 11}, {7, 11}, {7, 8},   {3, 8}, {3, 10},
                                         {11, 2}, {11, 9}, {11, 10}, {8, 9}};
            return Graph(nodes, edges);
        }

        Graph directed_graph_with_loop() {
            std::vector<node_type> nodes{{"Zero", 0},  {"One", 0},  {"Two", 0}, {"Three", 0},
                                         {"Four", 0},  {"Five", 0}, {"Six", 0}, {"Seven", 0},
                                         {"Eight", 0}, {"Nine", 0}, {"Ten", 0}};
            std::vector<edge_type> edges{{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 5},
                                         {2, 7}, {4, 3}, {4, 5}, {5, 6}, {6, 7},
                                         {6, 9}, {7, 8}, {9, 8}, {9, 2}};
            return Graph(nodes, edges);
        }
    } // namespace test
} // namespace graph
