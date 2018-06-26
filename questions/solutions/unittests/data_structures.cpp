#include <algorithm>
#include <string>
#include <vector>

#include "data_structures.hpp"
#include "utils.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

TEST_CASE("BasicNode") {
    using Node = graph::BasicNode;
    Node n1{"Hello"};
    Node n2{"Hello"};
    Node n3{"Hello world"};
    Node n4{"Hole"};

    CHECK(n1 == n2);
    CHECK(n1 != n3);
    CHECK(n4 > n2);
    CHECK(n3 > n2);
    CHECK(n1 < n4);

    CHECK_FALSE(n1 != n1);
    CHECK_FALSE(n1 == n3);
    CHECK_FALSE(n4 < n2);

    std::vector<Node> v{n1, n4, n3, n2};
    std::cout << "Original data: ";
    utils::print(v.cbegin(), v.cend());
    std::cout << "\n";

    std::sort(v.begin(), v.end());
    std::cout << "Sorted data: ";
    utils::print(v.cbegin(), v.cend());
    std::cout << "\n";
}

TEST_CASE("WeightedNode") {
    using T = int;
    using Node = graph::WeightedNode<T>;
    Node n1{"Hello", 1};
    Node n2{"Hello", 1};
    Node n3{"Hello", 2};
    Node n4{"Hole", 3};

    CHECK(n1 == n2);
    CHECK(n1 != n3);
    CHECK(n1 < n3);
    CHECK(n3 > n1);
    CHECK(n4 > n2);
    CHECK(n3 > n2);
    CHECK(n1 < n4);

    CHECK_FALSE(n1 != n1);
    CHECK_FALSE(n1 == n3);
    CHECK_FALSE(n4 < n2);

    std::vector<Node> v{n1, n4, n3, n2};
    std::cout << "Original data: ";
    utils::print(v.cbegin(), v.cend());
    std::cout << "\n";

    std::sort(v.begin(), v.end());
    std::cout << "Sorted data: ";
    utils::print(v.cbegin(), v.cend());
    std::cout << "\n";
}

TEST_CASE("BasicEdge") {
    using index_type = unsigned int;
    using Edge = graph::BasicEdge<index_type>;
    Edge e1{1, 2};
    Edge e2{4, 2};
    Edge e3{6, 2};
    Edge e4{6, 5};
    Edge e5{6, 5};

    CHECK(e1 < e2);
    CHECK(e3 < e4);

    CHECK(e2 > e1);
    CHECK(e4 > e3);

    CHECK(e1 != e4);
    CHECK(e5 == e4);

    std::vector<Edge> edges{e5, e1, e4, e3, e2};
    std::cout << "Unsorted edges: ";
    utils::print(edges.cbegin(), edges.cend());
    std::cout << "\n";
    CHECK_FALSE(std::is_sorted(edges.begin(), edges.end()));

    std::sort(edges.begin(), edges.end());
    std::cout << "Unsorted edges: ";
    utils::print(edges.cbegin(), edges.cend());
    std::cout << "\n";
    CHECK(std::is_sorted(edges.begin(), edges.end()));
}

TEST_CASE("WeightedEdge") {
    using index_type = unsigned int;
    using T = int;
    using Edge = graph::WeightedEdge<index_type, T>;
    Edge e1{1, 2, 1};
    Edge e2{4, 2, 4};
    Edge e3{6, 2, 3};
    Edge e4{6, 5, 2};
    Edge e5{6, 5, 2};
    Edge e6{6, 5, 5};

    CHECK(e1 < e2);
    CHECK(e3 < e4);
    CHECK(e4 < e6);

    CHECK(e2 > e1);
    CHECK(e4 > e3);
    CHECK(e6 > e4);

    CHECK(e1 != e4);
    CHECK(e5 == e4);

    std::vector<Edge> edges{e5, e1, e4, e3, e2, e6};
    std::cout << "Unsorted edges: ";
    utils::print(edges.cbegin(), edges.cend());
    std::cout << "\n";

    CHECK_FALSE(std::is_sorted(edges.begin(), edges.end()));

    std::sort(edges.begin(), edges.end());
    std::cout << "Unsorted edges: ";
    utils::print(edges.cbegin(), edges.cend());
    std::cout << "\n";
    CHECK(std::is_sorted(edges.begin(), edges.end()));
}
