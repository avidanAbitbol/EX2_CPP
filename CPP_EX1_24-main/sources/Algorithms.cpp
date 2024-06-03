#include "Algorithms.hpp"
#include <stack>
#include <queue>
#include <algorithm>
#include <functional>
#include <sstream>
#include <tuple>
#include <climits>
#include <iostream> // Include for debug prints

using namespace std;

namespace ariel {

#include <iostream> // Include for debug prints
//this function to check whether a graph is connected.
// You start by checking if the graph is empty,
// in which case you return true. Otherwise,
// you perform a breadth-first search (BFS) traversal starting from vertex 0.
// During the BFS traversal, you mark visited vertices using a boolean array.
// If all vertices are visited, you conclude that the graph is connected.
    bool Algorithms::isConnected(Graph &graph) {
        size_t numVertices = graph.vertices();
        if (numVertices == 0) {
            return true;
        }

        std::vector<bool> visited(numVertices, false);
        std::queue<int> q;
        q.push(0); // Start BFS from node 0
        visited[0] = true; // Mark the starting node as visited
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            for (std::size_t adjacent = 0; adjacent < graph.vertices(); ++adjacent) {
                if (graph.adj(node)[adjacent] != 0) { // There is an edge
                    if (!visited[adjacent]) {
                        visited[adjacent] = true;
                        q.push(static_cast<int>(adjacent));
                    }
                }
            }
        }

        // Check if all vertices were visited
        bool allVisited = true;
        for (size_t i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                allVisited = false;
            }
        }
        return allVisited;
    }
//This function detects whether the given graph contains a cycle.
// You've implemented it using a depth-first search (DFS) traversal.
// Within the DFS traversal, you maintain two boolean arrays:
// one for visited vertices and another to track vertices in the recursion stack.
// If you encounter a visited vertex that is also in the recursion stack, you've detected a cycle.
    bool Algorithms::isContainsCycle(Graph &graph) {
        size_t numVertices = graph.vertices();
        std::vector<bool> visited(numVertices, false);
        std::vector<bool> recStack(numVertices, false);
        std::vector<int> parent(numVertices, -1);
        std::vector<int> cyclePath;

        std::function<bool(int, int)> dfs = [&](int v, int parentV) {
            visited[static_cast<std::size_t>(v)] = true;
            recStack[static_cast<std::size_t>(v)] = true;
            for (std::size_t neighbor = 0; neighbor < graph.adj(v).size(); ++neighbor) {
                if (graph.adj(v)[neighbor] != 0) { // There is an edge
                    if (!visited[neighbor]) {
                        parent[neighbor] = v;
                        if (dfs(static_cast<int>(neighbor), v)) {
                            return true;
                        }
                    } else if (neighbor != static_cast<std::size_t>(parentV) && recStack[neighbor]) { // Check for a cycle
                        // Capture the cycle path
                        for (int current = v; current != static_cast<int>(neighbor); current = parent[static_cast<std::size_t>(current)]) {
                            cyclePath.push_back(current);
                        }
                        cyclePath.push_back(static_cast<int>(neighbor));
                        cyclePath.push_back(v);
                        std::reverse(cyclePath.begin(), cyclePath.end());
                        return true;
                    }
                }
            }
            recStack[static_cast<std::size_t>(v)] = false;
            return false;
        };

        for (size_t i = 0; i < numVertices; ++i) {
            if (!visited[i]) {
                if (dfs(static_cast<int>(i), -1)) {
                    std::cout << "The cycle is: ";
                    for (size_t j = 0; j < cyclePath.size(); ++j) {
                        if (j > 0) std::cout << "->";
                        std::cout << cyclePath[j];
                    }
                    std::cout << std::endl;
                    return true;
                }
            }
        }
        return false;
    }


//Here, i implemented a function to determine whether the graph is bipartite.
// You've used BFS traversal with vertex coloring. During the traversal,
// you assign alternating colors (0 and 1) to adjacent vertices.
// If any adjacent vertices have the same color,the graph is not bipartite.
    std::string Algorithms::isBipartite(Graph &graph) {
        size_t numVertices = graph.vertices();
        vector<int> color(numVertices, -1); // -1 means uncolored
        queue<size_t> q; // Use size_t for queue indices
        bool isBipartite = true;

        // Perform BFS traversal for each uncolored vertex
        for (size_t i = 0; i < numVertices; i++) {
            if (color[i] == -1) { // Node not colored yet
                color[i] = 0; // Assign color 0
                q.push(i);
                // BFS traversal to color vertices and check bipartiteness
                while (!q.empty() && isBipartite) {
                    size_t u = q.front();
                    q.pop();
                    // Iterate over adjacent vertices
                    for (size_t v = 0; v < numVertices; ++v) {
                        // Check if there is an edge between u and v
                        if (graph.adj(u)[v] != 0) {
                            if (color[v] == -1) { // Node not colored
                                color[v] = 1 - color[u]; // Assign opposite color
                                q.push(v);
                            } else if (color[v] == color[u]) { // Same color as parent
                                isBipartite = false;
                                break;
                            }
                        }
                    }
                }
                if (!isBipartite) break; // Exit if not bipartite
            }
        }

        if (!isBipartite) {
            return "0"; // Return 0 if not bipartite
        }

        // Construct the bipartite sets string
        vector<int> setA, setB;
        for (size_t i = 0; i < numVertices; ++i) {
            if (color[i] == 0) {
                setA.push_back(static_cast<int>(i));
            } else if (color[i] == 1) {
                setB.push_back(static_cast<int>(i));
            }
        }

        std::sort(setA.begin(), setA.end());
        std::sort(setB.begin(), setB.end());

        // Construct the result string
        stringstream ss;
        ss << "The graph is bipartite: A={";
        for (size_t i = 0; i < setA.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << setA[i];
        }
        ss << "}, B={";
        for (size_t i = 0; i < setB.size(); ++i) {
            if (i > 0) ss << ", ";
            ss << setB[i];
        }
        ss << "}";
        return ss.str(); // Return the result string
    }
//This function finds the shortest path between two vertices using BFS traversal.
// Starting from the source vertex, you explore the graph layer by layer until you reach the destination vertex.
// You maintain a parent array to reconstruct the shortest path once the destination is reached.
    std::string Algorithms::shortestPath(Graph& graph, int src, int dest) {
        size_t numVertices = graph.vertices();
        std::vector<int> parent(numVertices, -1); // Parent array to reconstruct the shortest path
        std::vector<bool> visited(numVertices, false); // Visited array to mark visited vertices
        std::queue<int> q; // Queue for BFS traversal

        q.push(src); // Start BFS from source vertex
        visited[static_cast<std::vector<bool>::size_type>(src)] = true; // Mark the source vertex as visited

        // Perform BFS traversal
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == dest) {
                break; // If destination is reached, exit the loop
            }

            // Explore adjacent vertices
            for (size_t v = 0; v < graph.adj(u).size(); ++v) {
                if (graph.adj(u)[v] != 0 && !visited[v]) {
                    visited[v] = true; // Mark vertex as visited
                    parent[v] = u; // Set parent of vertex v to u
                    q.push(static_cast<int>(v)); // Enqueue vertex v
                }
            }
        }

        // If destination is not reachable from source, return "-1"
        if (!visited[static_cast<std::vector<bool>::size_type>(dest)]) {
            return "-1"; // No path found
        }

        // Reconstruct the shortest path from destination to source
        std::vector<int> path;
        for (int v = dest; v != -1; v = parent[static_cast<std::vector<int>::size_type>(v)]) {
            path.push_back(v); // Add vertex to path
        }
        std::reverse(path.begin(), path.end()); // Reverse the path to get source to destination order

        // Construct the path string
        std::stringstream ss;
        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) ss << "->"; // Add "->" separator between vertices
            ss << path[i]; // Add vertex to string
        }
        return ss.str(); // Return the shortest path string
    }


    /**
 This function checks whether the graph contains a negative weight cycle using the Bellman-Ford algorithm.
     You initialize distances to vertices as INT_MAX and relax edges iteratively.
     If any edge can still be relaxed after the maximum number of iterations,
     it indicates the presence of a negative weight cycle.
 */
    bool Algorithms::negativeCycle(Graph &graph) {
        size_t numVertices = graph.vertices();
        vector<int> distance(numVertices, INT_MAX); // Initialize distances to vertices as INT_MAX
        distance[0] = 0; // Set distance to source vertex as 0

        // Relax edges repeatedly
        for (size_t i = 0; i < numVertices - 1; i++) {
            for (const auto& edge : graph.edges()) {
                int u, v, weight;
                tie(u, v, weight) = edge; // Unpack edge tuple
                // If relaxing the edge results in a shorter path, update the distance
                if (distance[static_cast<std::size_t>(u)] != INT_MAX && distance[static_cast<std::size_t>(u)] + weight < distance[static_cast<std::size_t>(v)]) {
                    distance[static_cast<std::size_t>(v)] = distance[static_cast<std::size_t>(u)] + weight;
                }
            }
        }

        // Check for negative weight cycles
        for (const auto& edge : graph.edges()) {
            int u, v, weight;
            tie(u, v, weight) = edge; // Unpack edge tuple
            // If relaxing the edge further results in a shorter path, a negative weight cycle exists
            if (distance[static_cast<std::size_t>(u)] != INT_MAX && distance[static_cast<std::size_t>(u)] + weight < distance[static_cast<std::size_t>(v)]) {
                return true;
            }
        }

        return false; // No negative weight cycle found
    }
    Algorithms::Algorithms() { }
} // namespace ariel
