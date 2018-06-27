#pragma once

#include "data_structures.hpp"
#include "graph.hpp"
#include "utils.hpp"
#include <string>
#include <vector>

namespace graph {
    namespace test {
        namespace minimum {
            using index_type = unsigned int;
            using weight_type = int;
            using edge_type = typename graph::BasicEdge<index_type>;
            using range_type = typename graph::Range<index_type>;
            using Graph = typename graph::minimum::Graph<index_type, edge_type>;

            Graph directed_graph() {
                std::vector<edge_type> edges{{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 5},
                                             {2, 7}, {4, 3}, {4, 5}, {5, 6}, {6, 7},
                                             {6, 9}, {7, 8}, {9, 8}};
                return Graph(edges, 10);
            }

            // This graph data is obtained from
            // https://en.wikipedia.org/wiki/Topological_sorting#Depth-first_search.
            Graph directed_graph2() {
                std::vector<edge_type> edges{{5, 11}, {7, 11}, {7, 8},   {3, 8}, {3, 10},
                                             {11, 2}, {11, 9}, {11, 10}, {8, 9}};
                return Graph(edges, 12);
            }

            Graph directed_graph_with_loop() {
                std::vector<edge_type> edges{{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 5},
                                             {2, 7}, {4, 3}, {4, 5}, {5, 6}, {6, 7},
                                             {6, 9}, {7, 8}, {9, 8}, {9, 2}};
                return Graph(edges, 10);
            }
        } // namespace minimum

        namespace weighted_node {
            using index_type = unsigned int;
            using weight_type = int;
            using edge_type = typename graph::BasicEdge<index_type>;
            using node_type = typename graph::WeightedNode<index_type, weight_type>;
            using range_type = typename graph::Range<index_type>;
            using Graph = typename graph::simple::Graph<node_type, edge_type>;

            Graph directed_graph() {
                std::vector<node_type> nodes{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0},
                                             {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}};
                std::vector<edge_type> edges{{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 5},
                                             {2, 7}, {4, 3}, {4, 5}, {5, 6}, {6, 7},
                                             {6, 9}, {7, 8}, {9, 8}};
                return Graph(nodes, edges);
            }

            // This graph data is obtained from
            // https://en.wikipedia.org/wiki/Topological_sorting#Depth-first_search.
            Graph directed_graph2() {
                std::vector<node_type> nodes{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0},  {5, 0},
                                             {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}, {11, 0}};
                std::vector<edge_type> edges{{5, 11}, {7, 11}, {7, 8},   {3, 8}, {3, 10},
                                             {11, 2}, {11, 9}, {11, 10}, {8, 9}};
                return Graph(nodes, edges);
            }

            Graph directed_graph_with_loop() {
                std::vector<node_type> nodes{{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0},
                                             {6, 0}, {7, 0}, {8, 0}, {9, 0}, {10, 0}};
                std::vector<edge_type> edges{{0, 3}, {1, 0}, {1, 2}, {1, 4}, {2, 5},
                                             {2, 7}, {4, 3}, {4, 5}, {5, 6}, {6, 7},
                                             {6, 9}, {7, 8}, {9, 8}, {9, 2}};
                return Graph(nodes, edges);
            }
        } // namespace weighted_node
    }     // namespace test
} // namespace graph
