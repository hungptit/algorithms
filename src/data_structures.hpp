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
    template <typename T> struct BasicNode {
        T id;
        template <typename Archive> void serialize(Archive &ar) { ar(CEREAL_NVP(id)); }
    };

    template <typename T> bool operator==(const BasicNode<T> &lhs, const BasicNode<T> &rhs) {
        return lhs.id == rhs.id;
    }
    template <typename T> bool operator!=(const BasicNode<T> &lhs, const BasicNode<T> &rhs) {
        return lhs.id != rhs.id;
    }
    template <typename T> bool operator>(const BasicNode<T> &lhs, const BasicNode<T> &rhs) {
        return lhs.id > rhs.id;
    }
    template <typename T> bool operator<(const BasicNode<T> &lhs, const BasicNode<T> &rhs) {
        return lhs.id < rhs.id;
    }

    // WeightedNode
    template <typename T1, typename T2> struct WeightedNode {
        T1 id;
        T2 value;
        template <typename Archive> void serialize(Archive &ar) {
            ar(CEREAL_NVP(id), CEREAL_NVP(value));
        }
    };

    template <typename T1, typename T2>
    bool operator==(const WeightedNode<T1, T2> &lhs, const WeightedNode<T1, T2> &rhs) {
        return std::tie(lhs.id, lhs.value) == std::tie(rhs.id, rhs.value);
    }

    template <typename T1, typename T2>
    bool operator!=(const WeightedNode<T1, T2> &lhs, const WeightedNode<T1, T2> &rhs) {
        return std::tie(lhs.id, lhs.value) != std::tie(rhs.id, rhs.value);
    }

    template <typename T1, typename T2>
    bool operator>(const WeightedNode<T1, T2> &lhs, const WeightedNode<T1, T2> &rhs) {
        return std::tie(lhs.id, lhs.value) > std::tie(rhs.id, rhs.value);
    }

    template <typename T1, typename T2>
    bool operator<(const WeightedNode<T1, T2> &lhs, const WeightedNode<T1, T2> &rhs) {
        return std::tie(lhs.id, lhs.value) < std::tie(rhs.id, rhs.value);
    }

    // Minimum edge which only has destination information.
    template <typename T> struct MinimumEdge {
        using index_type = T;
        index_type destination;
        template <typename Archive> void serialize(Archive &ar) { ar(CEREAL_NVP(destination)); }
    };

    template <typename index_type>
    bool operator==(const MinimumEdge<index_type> &lhs, const MinimumEdge<index_type> &rhs) {
        return lhs.destination == rhs.destination;
    }

    template <typename index_type>
    bool operator!=(const MinimumEdge<index_type> &lhs, const MinimumEdge<index_type> &rhs) {
        return lhs.destination != rhs.destination;
    }

    template <typename index_type>
    bool operator>(const MinimumEdge<index_type> &lhs, const MinimumEdge<index_type> &rhs) {
        return lhs.destination > rhs.destination;
    }

    template <typename index_type>
    bool operator<(const MinimumEdge<index_type> &lhs, const MinimumEdge<index_type> &rhs) {
        return lhs.destination < rhs.destination;
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
