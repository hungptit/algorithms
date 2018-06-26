#pragma once

#include "fmt/format.h"
#include <deque>
#include <string>
#include <vector>

namespace graph {
    namespace simple {
        using index_type = unsigned int;
        struct Node {
            std::string name;
            int value;
            std::vector<index_type> children;
        };

        struct Edge {
            index_type source;
            index_type destination;
        };

        struct Graph {
            Graph(const std::vector<Node> &v, const std::vector<Edge> &edges)
                : nodes(v.cbegin(), v.cend()) {}
            std::vector<Node> nodes;
        };
        
    } // namespace simple
    namespace experiments {
        struct BasicNode {
            std::string name;
            int value;
        };

        template <typename T> void print_nodes(const std::vector<T> &data, const std::string &title);

        template <>
        void print_nodes<BasicNode>(const std::vector<BasicNode> &data, const std::string &title) {
            fmt::print("{}", title);
            for (auto const &item : data) {
                fmt::print(" ({0}, {1})", item.name, item.value);
            }
            fmt::print("\n");
        }

        template <typename Index> struct Edge {
            using index_type = Index;
            index_type source;
            index_type destination;
        };

        template <typename T> void print_edges(const T &edges, const std::string &title = "Edges: ") {
            fmt::print("{}", title);
            for (auto const edge : edges) {
                fmt::print(" ({0}, {1})", edge.source, edge.destination);
            }
            fmt::print("\n");
        }

        template <typename Iter> struct Range {
            Iter begin;
            Iter end;
        };

        template <typename T1, typename T2> struct Graph {
            using node_type = T1;
            using index_type = T2;
            using container_type = std::vector<index_type>;
            std::vector<node_type> vertices;
            std::vector<container_type> data;

            Graph(const std::vector<node_type> &nodes, const std::vector<Edge<index_type>> &edges)
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
                return Range<typename container_type::const_iterator>{children.cbegin(), children.cend()};
            }

            auto redges(index_type vid) const {
                const container_type &children = data[vid];
                return Range<typename container_type::const_reverse_iterator>{children.crbegin(), children.crend()};
            }
        };
    } // namespace experiments
} // namespace graph
