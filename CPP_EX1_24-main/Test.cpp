#include "doctest.h"
#include "sources/Algorithms.hpp"
#include "sources/Graph.hpp"
#include <vector>
#include <sstream>
#include <limits>
using namespace std;
using namespace ariel;
#define SIZE_TYPE static_cast<std::vector<int>::size_type> // Correct macro definition

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}};
    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph multiplication") {
    ariel::Graph g1;
    vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
            {1, 0, 2},
            {1, 3, 1},
            {1, 0, 2}};
    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
}


TEST_CASE("Invalid operations") {
    ariel::Graph g1, g2, g5, g6;
    // Correctly sized graphs
    vector<vector<int>> graph = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    vector<vector<int>> graph2 = {{0, 1, 0, 0, 1}, {1, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 1, 0}};

    // Load graphs without throwing an exception
    g1.loadGraph(graph);
    g5.loadGraph(graph2);

    // Incorrectly sized graph for operations
    vector<vector<int>> nonSquareGraph = {{0, 1, 1, 1}, {1, 0, 2, 1}, {1, 2, 0, 1}};
    vector<vector<int>> graph3 = {{0, 1, 0, 0, 1}, {1, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 1, 0, 1}, {1, 0, 0, 1, 0}};

    // Load without exception to check operation
    g2.loadGraph(graph);
    g6.loadGraph(graph3);

    // Ensure operations throw due to size mismatch
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 + g6);
}
TEST_CASE("Test graph addition") {
    Graph g1;
    vector<vector<int>> graph1 = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    g1.loadGraph(graph1);
    Graph g2;
    vector<vector<int>> graph2 = {{0, 1, 1}, {1, 0, 2}, {1, 2, 0}};
    g2.loadGraph(graph2);
    Graph result = g1 + g2;
    vector<vector<int>> expected = {{0, 2, 1}, {2, 0, 3}, {1, 3, 0}};
    CHECK(result.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph multiplication") {
    Graph g1;
    vector<vector<int>> graph1 = {{0, 1, 0}, {1, 0, 1}, {0, 1, 0}};
    g1.loadGraph(graph1);
    Graph g2;
    vector<vector<int>> graph2 = {{0, 1, 1}, {1, 0, 2}, {1, 2, 0}};
    g2.loadGraph(graph2);
    Graph result = g1 * g2;
    vector<vector<int>> expected = {{1, 0, 2}, {1, 3, 1}, {1, 0, 2}};
    CHECK(result.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
}

TEST_CASE("Empty graph operations") {
    Graph g;
    vector<vector<int>> emptyGraph = {};
    g.loadGraph(emptyGraph);
    CHECK(g.vertices() == 0); // Check if the graph reports correctly no vertices
    CHECK_THROWS(g.adj(0)); // Accessing adjacency list should throw as there are no vertices
    CHECK_THROWS(g + g); // Addition should throw or handle gracefully
    CHECK_THROWS(g * g); // Multiplication should throw or handle gracefully
}

TEST_CASE("Single vertex graph") {
    Graph g;
    vector<vector<int>> singleVertex = {{0}};
    g.loadGraph(singleVertex);
    CHECK(g.vertices() == 1);
    CHECK_NOTHROW(g.adj(0)); // Should not throw, one vertex exists
    CHECK(g.printGraph() == "[0]"); // Check if the output is as expected
}

TEST_CASE("Graphs with maximum integer weights") {
    Graph g;
    int maxInt = numeric_limits<int>::max();
    vector<vector<int>> maxWeightGraph = {{0, maxInt}, {maxInt, 0}};
    g.loadGraph(maxWeightGraph);
    CHECK(g.printGraph() == "[0, " + to_string(maxInt) + "]\n[" + to_string(maxInt) + ", 0]");
    Graph g2 = g; // Copy for operation
    CHECK_THROWS(g + g2); // Addition may overflow
    CHECK_NOTHROW(g * g2); // Multiplication should be implemented to handle large values or limit cases
}

TEST_CASE("Very large graphs") {
    Graph g;
    // For practical purposes, let's define 'very large' as a manageable size for unit testing
    int size = 100; // Adjust based on system capabilities for unit testing
    vector<vector<int>> largeGraph(SIZE_TYPE(size), vector<int>(SIZE_TYPE(size), 1));
    g.loadGraph(largeGraph);
    CHECK(g.vertices() == size);
    CHECK_NOTHROW(g + g); // Addition of large graphs
    CHECK_NOTHROW(g * g); // Multiplication of large graphs
}

TEST_CASE("Graphs with zero weights") {
    Graph g;
    vector<vector<int>> zeroWeightGraph = {{0, 0}, {0, 0}};
    g.loadGraph(zeroWeightGraph);
    CHECK(g.printGraph() == "[0, 0]\n[0, 0]");
    Graph g2 = g; // Copy for operations
    CHECK_NOTHROW(g + g2); // Addition should handle zero weights gracefully
    CHECK_NOTHROW(g * g2); // Multiplication should handle zero weights gracefully
}
TEST_CASE("Division by zero") {
    Graph g;
    vector<vector<int>> graph = {{2, 4}, {6, 8}};
    g.loadGraph(graph);
    CHECK_THROWS(g / 0);
}

TEST_CASE("Subtraction with different sizes") {
    Graph g1;
    vector<vector<int>> graph1 = {{0, 1}, {1, 0}};
    g1.loadGraph(graph1);
    Graph g2;
    vector<vector<int>> graph2 = {{0, 1, 1}, {1, 0, 2}, {1, 2, 0}};
    g2.loadGraph(graph2);
    CHECK_THROWS(g1 - g2);
}

TEST_CASE("Graph input with non-square matrix") {
    Graph g;
    vector<vector<int>> nonSquare = {{1, 2}, {3, 4}, {5, 6}};
    CHECK_THROWS(g.loadGraph(nonSquare));
}


TEST_CASE("Invalid vertex index") {
    Graph g;
    vector<vector<int>> graph = {{0, 1}, {1, 0}};
    g.loadGraph(graph);
    CHECK_THROWS(g.adj(2)); // Index out of bounds
}
TEST_CASE("Fully connected graph operations") {
    Graph g;
    int size = 3;
    vector<vector<int>> completeGraph(SIZE_TYPE(size), vector<int>(SIZE_TYPE(size), 1));
    for (std::vector<int>::size_type i = 0; i < SIZE_TYPE(size); ++i) completeGraph[i][i] = 0;
    g.loadGraph(completeGraph);
    Graph result = g + g;
    vector<vector<int>> expected(SIZE_TYPE(size), vector<int>(SIZE_TYPE(size), 2));
    for (std::vector<int>::size_type i = 0; i < SIZE_TYPE(size); ++i) expected[i][i] = 0;
    CHECK(result.printGraph() == "[0, 2, 2]\n[2, 0, 2]\n[2, 2, 0]");
}

TEST_CASE("Graph input with non-square matrix") {
    Graph g;
    vector<vector<int>> nonSquare = {{1, 2}, {3, 4}, {5, 6}};
    CHECK_THROWS(g.loadGraph(nonSquare));
}


TEST_CASE("Input/output test") {
    std::stringstream ss;
    ss << "0 1\n1 0";
    Graph g;
    ss >> g;
    std::ostringstream os;
    os << g;
    CHECK(os.str() == "[0 1]\n[1 0]");
}

TEST_CASE("Copy and assignment") {
    Graph g1;
    vector<vector<int>> graph = {{0, 2}, {2, 0}};
    g1.loadGraph(graph);
    Graph g2 = g1; // Copy constructor
    Graph g3;
    g3 = g1; // Assignment operator
    CHECK(g2.printGraph() == g1.printGraph());
    CHECK(g3.printGraph() == g1.printGraph());
}
