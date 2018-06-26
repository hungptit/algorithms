#pragma once
#include "cereal/archives/binary.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/archives/portable_binary.hpp"
#include "cereal/archives/xml.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"
#include <string>

// TODO: Speedup string comparison using AVX2 version.

// Define data structures for nodes and edges.
namespace graph {
    // BasicNode data structure.
    struct BasicNode {
        std::string name;
        template <typename Archive> void serialize(Archive &ar) { ar(CEREAL_NVP(name)); }
    };

    bool operator==(const BasicNode &lhs, const BasicNode &rhs) { return lhs.name == rhs.name; }
    bool operator!=(const BasicNode &lhs, const BasicNode &rhs) { return lhs.name != rhs.name; }
    bool operator>(const BasicNode &lhs, const BasicNode &rhs) { return lhs.name > rhs.name; }
    bool operator<(const BasicNode &lhs, const BasicNode &rhs) { return lhs.name < rhs.name; }

    // WeightedNode
    template <typename T> struct WeightedNode {
        std::string name;
        T value;
        template <typename Archive> void serialize(Archive &ar) {
            ar(CEREAL_NVP(name), CEREAL_NVP(value));
        }
    };

    template <typename T>
    bool operator==(const WeightedNode<T> &lhs, const WeightedNode<T> &rhs) {
        return std::tie(lhs.name, lhs.value) == std::tie(rhs.name, rhs.value);
    }

    template <typename T>
    bool operator!=(const WeightedNode<T> &lhs, const WeightedNode<T> &rhs) {
        return std::tie(lhs.name, lhs.value) != std::tie(rhs.name, rhs.value);
    }

    template <typename T>
    bool operator>(const WeightedNode<T> &lhs, const WeightedNode<T> &rhs) {
        return std::tie(lhs.name, lhs.value) > std::tie(rhs.name, rhs.value);
    }

    template <typename T>
    bool operator<(const WeightedNode<T> &lhs, const WeightedNode<T> &rhs) {
        return std::tie(lhs.name, lhs.value) < std::tie(rhs.name, rhs.value);
    }

    // BasicEdge
    template <typename T> struct BasicEdge {
        using index_type = T;
        index_type source;
        index_type destination;
        template <typename Archive> void serialize(Archive &ar) {
            ar(CEREAL_NVP(source), CEREAL_NVP(destination));
        }
    };

    template <typename index_type>
    bool operator==(const BasicEdge<index_type> &lhs, const BasicEdge<index_type> &rhs) {
        return std::tie(lhs.source, lhs.destination) == std::tie(rhs.source, rhs.destination);
    }

    template <typename index_type>
    bool operator!=(const BasicEdge<index_type> &lhs, const BasicEdge<index_type> &rhs) {
        return std::tie(lhs.source, lhs.destination) != std::tie(rhs.source, rhs.destination);
    }

    template <typename index_type>
    bool operator>(const BasicEdge<index_type> &lhs, const BasicEdge<index_type> &rhs) {
        return std::tie(lhs.source, lhs.destination) > std::tie(rhs.source, rhs.destination);
    }

    template <typename index_type>
    bool operator<(const BasicEdge<index_type> &lhs, const BasicEdge<index_type> &rhs) {
        return std::tie(lhs.source, lhs.destination) < std::tie(rhs.source, rhs.destination);
    }

    // BasicEdge
    template <typename T1, typename T2> struct WeightedEdge {
        using index_type = T1;
        using weight_type = T2;
        
        index_type source;
        index_type destination;
        weight_type weight;
        template <typename Archive> void serialize(Archive &ar) {
            ar(CEREAL_NVP(source), CEREAL_NVP(destination), CEREAL_NVP(weight));
        }
    };

    template <typename index_type, typename T>
    bool operator==(const WeightedEdge<index_type, T> &lhs,
                    const WeightedEdge<index_type, T> &rhs) {
        return std::tie(lhs.source, lhs.destination, lhs.weight) ==
               std::tie(rhs.source, rhs.destination, rhs.weight);
    }

    template <typename index_type, typename T>
    bool operator!=(const WeightedEdge<index_type, T> &lhs,
                    const WeightedEdge<index_type, T> &rhs) {
        return std::tie(lhs.source, lhs.destination, lhs.weight) !=
               std::tie(rhs.source, rhs.destination, rhs.weight);
    }

    template <typename index_type, typename T>
    bool operator>(const WeightedEdge<index_type, T> &lhs,
                   const WeightedEdge<index_type, T> &rhs) {
        return std::tie(lhs.source, lhs.destination, lhs.weight) >
               std::tie(rhs.source, rhs.destination, rhs.weight);
    }

    template <typename index_type, typename T>
    bool operator<(const WeightedEdge<index_type, T> &lhs,
                   const WeightedEdge<index_type, T> &rhs) {
        return std::tie(lhs.source, lhs.destination, lhs.weight) <
               std::tie(rhs.source, rhs.destination, rhs.weight);
    }

    // Range of elements i.e [begin, end)
    template <typename Iter> struct Range {
        Iter begin;
        Iter end;
    };
} // namespace graph
