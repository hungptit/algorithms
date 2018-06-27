#pragma once

#include "data_structures.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>

namespace graph {
    std::ostream &operator<<(std::ostream &os, const BasicNode &val) {
        os << "(\"" << val.name << "\")";
        return os;
    }

    template <typename T>
    std::ostream &operator<<(std::ostream &os, const WeightedNode<T> &val) {
        os << "(\"" << val.name << "\"," << val.value << "\")";
        return os;
    }

    template <typename index_type>
    std::ostream &operator<<(std::ostream &os, const BasicEdge<index_type> &val) {
        os << "(\"" << val.source << "\"," << val.destination << "\")";
        return os;
    }

    template <typename index_type, typename T>
    std::ostream &operator<<(std::ostream &os, const WeightedEdge<index_type, T> &val) {
        os << "(\"" << val.source << "\"," << val.destination << "," << val.weight << "\")";
        return os;
    }

    
} // namespace graph

namespace utils {
    template <typename Iterator> void print(Iterator begin, Iterator end) {
        if (begin == end) {
            std::cout << "[]";
            return;
        }
        std::cout << "[";
        std::cout << *begin;
        for (auto iter = ++begin; iter != end; ++iter) {
            std::cout << "," << *iter;
        }
        std::cout << "]";
    }

    template <typename T, typename OArchive> std::string save(const T &data) {
        std::stringstream os;
        {
            OArchive oar(os);
            oar(data);
        }
        return os.str();
    }
} // namespace utils
