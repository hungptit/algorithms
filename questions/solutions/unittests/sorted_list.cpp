#include "data.hpp"
#include "graph.hpp"
#include "topological_sorting.hpp"
#include "traversal_policies.hpp"
#include <string>
#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

namespace {
    template <typename Algorithm>
    void sorted_list(typename Algorithm::graph_type &g, bool is_dag,
                     std::deque<typename Algorithm::index_type> &&sorted_list) {
        // std::cout << utils::save<decltype(g), cereal::JSONOutputArchive>(g);
        Algorithm dfs(g);
        bool isok = dfs.traverse();
        CHECK(isok == is_dag);
        if (isok) {
            CHECK(dfs.sorted_list == sorted_list);
            fmt::print("Sorted list:");
            for (auto item : dfs.sorted_list) {
                fmt::print(" {}", item);
            }
            fmt::print("\n");
        } else {
            fmt::print("The given graph has a cycle.\n");
        }
    }
} // namespace

TEST_CASE("Non-recusrive implementation - graph has loop") {
    auto g = graph::test::minimum::directed_graph_with_loop();
    sorted_list<graph::algorithms::minimum::TopologicalSort<
        typename graph::algorithms::minimum::MinimumPolicy<decltype(g)>>>(
        g, false, {7, 6, 5, 11, 4, 3, 10, 8, 9, 2, 1, 0});
}

TEST_CASE("Non-recusrive implementation - g1", "") {
    auto g = graph::test::minimum::directed_graph();
    sorted_list<graph::algorithms::minimum::TopologicalSort<
        typename graph::algorithms::minimum::MinimumPolicy<decltype(g)>>>(
            g, true, {1, 2, 4, 5, 6, 7, 9, 8, 0, 3});
}

TEST_CASE("Non-recusrive implementation - g2", "") {
    auto g = graph::test::minimum::directed_graph2();
    sorted_list<graph::algorithms::minimum::TopologicalSortRecursive<
        typename graph::algorithms::minimum::MinimumPolicy<decltype(g)>>>(
        g, true, {7, 6, 5, 11, 4, 3, 10, 8, 9, 2, 1, 0});
}

TEST_CASE("Recusrive implementation - g1", "") {
    auto g = graph::test::minimum::directed_graph();
    sorted_list<graph::algorithms::minimum::TopologicalSortRecursive<
        typename graph::algorithms::minimum::MinimumPolicy<decltype(g)>>>(
            g, true, {1, 4, 2, 5, 6, 9, 7, 8, 0, 3});
}

TEST_CASE("Recusrive implementation - g2", "") {
    auto g = graph::test::minimum::directed_graph2();
    sorted_list<graph::algorithms::minimum::TopologicalSortRecursive<
        typename graph::algorithms::minimum::MinimumPolicy<decltype(g)>>>(
        g, true, {7, 6, 5, 11, 4, 3, 10, 8, 9, 2, 1, 0});
}
