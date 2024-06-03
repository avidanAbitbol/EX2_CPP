#pragma once

#include <vector>
#include <tuple> // For std::tuple
#include <iostream> // For std::ostream and std::istream

#ifndef CPP_EX4_GRAPH_HPP
#define CPP_EX4_GRAPH_HPP

namespace ariel {
    /**
     * @brief Class representing a graph.
     */
    class Graph {
    public:
        // Only one default constructor needed
        /**
         * @brief Default constructor.
         */
        /**
         * @brief Load the graph from an adjacency matrix.
         *
         * @param graph The adjacency matrix representing the graph.
         * @throw std::invalid_argument If the input matrix is not a square matrix.
         */
        Graph();
        void loadGraph(const std::vector<std::vector<int>>& graph);

        std::string printGraph() const;

        /**
         * @brief Get the adjacency matrix of the graph.
         *
         * @return The adjacency matrix.
         */
        const std::vector<std::vector<int>>& getGraph() const;

        /**
         * @brief Get the number of vertices in the graph.
         *
         * @return The number of vertices.
         */
        std::size_t vertices() const;

        /**
         * @brief Get the adjacency list of a vertex.
         *
         * @param index The index of the vertex.
         * @return The adjacency list of the vertex.
         * @throw std::out_of_range If the index is out of range.
         */
        const std::vector<int>& adj(int index) const;

        /**
         * @brief Get the list of edges in the graph.
         *
         * @return The list of edges.
         */
        std::vector<std::tuple<int, int, int>> edges() const;

        /**
         * @brief Count the total number of edges in the graph.
         *
         * @return The total number of edges.
         */
        int countEdges() const;
        Graph operator+(const Graph& other) const;
        Graph operator*(const Graph& other) const;
        // Operator overloads
        Graph& operator+=(const Graph& other);

        Graph operator-(const Graph& other) const;
        Graph& operator-=(const Graph& other);

        Graph& operator*=(const Graph& other);

        Graph operator*(int scalar) const;
        Graph& operator*=(int scalar);

        Graph operator/(int scalar) const;
        Graph& operator/=(int scalar);

        bool operator==(const Graph& other) const;
        bool operator!=(const Graph& other) const;

        bool operator<(const Graph& other) const;
        bool operator<=(const Graph& other) const;
        bool operator>(const Graph& other) const;
        bool operator>=(const Graph& other) const;

        Graph operator+() const; // Unary plus
        Graph operator-() const; // Unary minus
        Graph& operator++();    // Pre-increment
        Graph operator++(int);  // Post-increment
        Graph& operator--();    // Pre-decrement
        Graph operator--(int);  // Post-decrement

        // Friend function for output stream operator
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
        // Friend function for input stream operator
        friend std::istream& operator>>(std::istream& is, Graph& graph);

    private:
        std::vector<std::vector<int>> graph; // Adjacency matrix
        std::size_t numVertices; // Number of vertices
        std::vector<std::vector<int>> adjacency_matrix;

        /**
         * @brief Check if a given matrix is square (has the same number of rows and columns).
         *
         * @param matrix The matrix to check.
         * @return True if the matrix is square, false otherwise.
         */
        bool isSquareMatrix(const std::vector<std::vector<int>>& matrix) const;
    };
} // namespace ariel

#endif //CPP_EX4_GRAPH_HPP
