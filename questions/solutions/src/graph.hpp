#pragma once

#include "data_structures.hpp"
#include "fmt/format.h"
#include <deque>
#include <string>
#include <vector>

#include "cereal/archives/binary.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/archives/portable_binary.hpp"
#include "cereal/archives/xml.hpp"
#include "cereal/types/deque.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"

namespace graph {
    namespace minimum {
        // A bare graph data structure which only has vetices information.
        template <typename T1, typename T2> struct Graph {
          public:
            using index_type = T1;
            using edge_type = T2;
            using container_type = std::vector<index_type>;

          public:
            Graph(const std::vector<edge_type> &edges, const size_t nnodes) : data(nnodes) {
                for (auto an_edge : edges) {
                    data[an_edge.source].push_back(an_edge.destination);
                }
            }

            template <typename Archive> void serialize(Archive &ar) { ar(CEREAL_NVP(data)); }

            size_t get_number_of_vertices() const { return data.size(); }

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

            void print() const {
                for (size_t idx = 0; idx < data.size(); ++idx) {
                    fmt::print("{}: [ ", idx);
                    for (auto item : data[idx]) {
                        fmt::print("{} ", item);
                    }
                    fmt::print("]\n");
                }
            }
            
          private:
            std::vector<container_type> data;
        };
    } // namespace minimum

    namespace simple {
        template <typename T1, typename T2> struct Graph {
          public:
            using node_type = T1;
            using edge_type = T2;
            using index_type = typename edge_type::index_type;
            using container_type = std::vector<edge_type>;

          public:
            Graph(const std::vector<node_type> &nodes, const std::vector<edge_type> &edges)
                : vertices(nodes), data(nodes.size()) {
                for (auto an_edge : edges) {
                    data[an_edge.source].push_back(an_edge);
                }
            }

            template <typename Archive> void serialize(Archive &ar) {
                ar(CEREAL_NVP(vertices), CEREAL_NVP(data));
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
