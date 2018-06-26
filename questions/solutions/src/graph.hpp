#pragma once

#include "fmt/format.h"
#include <deque>
#include <string>
#include <vector>
#include "data_structures.hpp"

namespace graph {
    namespace simple {
        template <typename T1, typename T2> struct Graph {
          public:
            using node_type = T1;
            using edge_type = T2;
            using index_type = typename edge_type::index_type;
            using container_type = std::vector<index_type>;

          public:
            Graph(const std::vector<node_type> &nodes,
                  const std::vector<edge_type> &edges)
                : vertices(nodes), data(nodes.size()) {
                for (auto an_edge : edges) {
                    data[an_edge.source].push_back(an_edge.destination);
                }
            }

            void print() const {
                // Print vertex information
                fmt::print("Vertices:");
                for (size_t vid = 0; vid < vertices.size(); ++vid) {
                    auto &v = vertices[vid];
                    fmt::print(" ({0},{1})", v.name, v.value);
                }
                fmt::print("\n");
                for (size_t vid = 0; vid < data.size(); ++vid) {
                    fmt::print("{}: ", vid);
                    fmt::print("[ ");
                    auto rg = edges(vid);
                    for (auto iter = rg.begin; iter != rg.end; ++iter) {
                        fmt::print("{0} ", *iter);
                    }
                    fmt::print("]\n");
                }
            }

            size_t get_number_of_vertices() const { return vertices.size(); }

            typename container_type::const_iterator begin(const index_type vid) const {
                return data[vid].cbegin();
            }

            typename container_type::const_iterator end(const index_type vid) const {
                return data[vid].cbegin();
            }

            auto edges(index_type vid) const {
                const container_type &children = data[vid];
                return Range<typename container_type::const_iterator>{children.cbegin(),
                                                                      children.cend()};
            }

            auto redges(index_type vid) const {
                const container_type &children = data[vid];
                return Range<typename container_type::const_reverse_iterator>{
                    children.crbegin(), children.crend()};
            }

          private:
            std::vector<node_type> vertices;
            std::vector<container_type> data;
        };
    } // namespace simple
} // namespace graph
