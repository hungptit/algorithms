#include "graph/DataStructures.hpp"
#include <iostream>
#include <string>
#include <vector>

#include "cereal/archives/binary.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/archives/portable_binary.hpp"
#include "cereal/archives/xml.hpp"
#include "cereal/types/array.hpp"
#include "cereal/types/string.hpp"
#include "cereal/types/vector.hpp"

template <typename Graph> class TreeHeight {
  public:
    TreeHeight()
        : CurrentHeight(0), MaxHeight(std::numeric_limits<size_t>::min()),
          MinHeight(std::numeric_limits<size_t>::max()) {}

    void compute_height(const Graph &g, size_t vid, size_t currentHeight) {
        auto const begin = g.begin(vid);
        auto const end = g.end(vid);

        if (begin == end) {
            if (MaxHeight < currentHeight) {
                MaxHeight = currentHeight;
            }

            if (MinHeight > currentHeight) {
                MinHeight = currentHeight;
            }

            return;
        } else {
            for (auto idx = begin; idx != end; ++idx) {
                auto const anEdge = g.edge(idx);
                compute_height(g, anEdge.DstId, currentHeight + 1);
            }
        }
    }

    auto getMaxHeight() const { return MaxHeight; }
    auto getMinHeight() const { return MinHeight; }

  private:
    size_t CurrentHeight = 0;
    size_t MaxHeight;
    size_t MinHeight;
};

template <typename Graph> auto compute_height_iterative(const Graph &g) {
    size_t max_height = std::numeric_limits<size_t>::min();
    size_t min_height = std::numeric_limits<size_t>::max();
    using Index = typename Graph::index_type;
    using Info = std::tuple<Index, size_t>;
    std::vector<Info> stack;
    stack.emplace_back(std::make_tuple(0, 0));
    while (!stack.empty()) {
        auto info = stack.back();
        stack.pop_back();
        auto const begin = g.begin(std::get<0>(info));
        auto const end = g.end(std::get<0>(info));

        if (begin == end) {
            // This is a leaf node
            if (max_height < std::get<1>(info)) {
                max_height = std::get<1>(info);
            }

            if (min_height > std::get<1>(info)) {
                min_height = std::get<1>(info);
            }
        } else {
            auto const newHeight = std::get<1>(info) + 1;
            for (auto vid = begin; vid != end; ++vid) {
                auto const anEdge = g.edge(vid);
                stack.emplace_back(std::make_tuple(anEdge.DstId, newHeight));
            }
        }
    }
    return std::make_tuple(max_height, min_height);
}

int main() {
    using Index = size_t;
    using edge_type = graph::BasicEdgeData<Index>;
    using Graph = graph::SparseGraph<Index, edge_type>;

    // Prepare the test data
    const size_t N = 8;
    std::vector<edge_type> edges{{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {2, 6}, {3, 7}};
    Graph g(edges, N, true);

    // Compute both max height and min height at the the same
    // time. The complexity for this algorithm is O(n).
    {
        TreeHeight<Graph> h;
        h.compute_height(g, 0, 0);
        std::cout << "Recursive implementation: \n";
        std::cout << "Max height: " << h.getMaxHeight() << "\n";
        std::cout << "Min height: " << h.getMinHeight() << "\n";
    }

    // Iterative approach.
    {
        std::cout << "Iterative implementation: \n";
        auto results = compute_height_iterative(g);
        std::cout << "Max height: " << std::get<0>(results) << "\n";
        std::cout << "Min height: " << std::get<1>(results) << "\n";
    }
}
