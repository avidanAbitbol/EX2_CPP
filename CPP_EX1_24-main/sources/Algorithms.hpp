#pragma once

#include "Graph.hpp"
#include <string>
#include <vector>

#ifndef CPP_EX4_ALGORITHMS_HPP
#define CPP_EX4_ALGORITHMS_HPP

namespace ariel {
    class Graph; // Forward declaration

    /**
     * @brief Class containing various graph algorithms.
     */
    class Algorithms {
    public:
        /**
         * @brief Check if the graph is connected.
         *
         * @param graph The graph to check.
         * @return True if the graph is connected, false otherwise.
         */
        static bool isConnected(Graph &graph);

        /**
         * @brief Check if the graph contains a cycle.
         *
         * @param graph The graph to check.
         * @return True if the graph contains a cycle, false otherwise.
         */
        static bool isContainsCycle(Graph &graph);

        /**
         * @brief Check if the graph is bipartite and return its partition sets.
         *
         * @param graph The graph to check.
         * @return A string representation of the bipartite sets if the graph is bipartite, "0" otherwise.
         */
        static std::string isBipartite(Graph &graph);

        /**
         * @brief Find the shortest path between two vertices in the graph.
         *
         * @param graph The graph to search in.
         * @param src The source vertex.
         * @param dest The destination vertex.
         * @return A string representing the shortest path from src to dest, or "-1" if no path exists.
         */
        static std::string shortestPath(Graph &graph, int src, int dest);

        /**
         * @brief Check if the graph contains a negative weight cycle.
         *
         * @param graph The graph to check.
         * @return True if the graph contains a negative weight cycle, false otherwise.
         */
        static bool negativeCycle(Graph &graph);

        /**
         * @brief Default constructor.
         */
        Algorithms();
    };
} // namespace ariel

#endif //CPP_EX4_ALGORITHMS_HPP
