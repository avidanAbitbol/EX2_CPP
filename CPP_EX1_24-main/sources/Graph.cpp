#include "Graph.hpp"
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <sstream> // For std::istringstream

namespace ariel {

    // Constructor definition without noexcept if it's not declared in the header
    Graph::Graph() : numVertices(0), graph(), adjacency_matrix() {}

    // Single implementation of loadGraph that checks if the matrix is square and then loads it.
    void Graph::loadGraph(const std::vector<std::vector<int>>& graph) {
        // Check if the graph is a square matrix
        if (!isSquareMatrix(graph)) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        // Assuming that you are maintaining both graph and adjacency_matrix, and they are intended to store the same data.
        this->graph = graph;
        this->adjacency_matrix = graph;
        this->numVertices = graph.size();
    }

    std::string Graph::printGraph() const {
        std::ostringstream oss;
        size_t numRows = adjacency_matrix.size();
        for (size_t i = 0; i < numRows; ++i) {
            oss << "[";
            for (size_t j = 0; j < adjacency_matrix[i].size(); ++j) {
                oss << adjacency_matrix[i][j];
                if (j != adjacency_matrix[i].size() - 1) {
                    oss << ", ";
                }
            }
            oss << "]";
            if (i != numRows - 1) {
                oss << "\n";
            }
        }
        return oss.str();
    }


    // Get the adjacency matrix of the graph
    const std::vector<std::vector<int>>& Graph::getGraph() const {
        return graph;
    }

    // Get the number of vertices in the graph
    std::size_t Graph::vertices() const {
        return numVertices;
    }

    // Get the adjacency list of a vertex
    const std::vector<int>& Graph::adj(int index) const {
        if (index < 0 || static_cast<std::size_t>(index) >= numVertices) {
            throw std::out_of_range("Index out of range");
        }
        return graph[static_cast<std::size_t>(index)];
    }

    // Get the list of edges in the graph
    std::vector<std::tuple<int, int, int>> Graph::edges() const {
        std::vector<std::tuple<int, int, int>> edgeList;
        std::unordered_set<std::string> uniqueEdges;

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                if (graph[i][j] != 0) {
                    std::string edge = std::to_string(i) + "-" + std::to_string(j);
                    std::string reverseEdge = std::to_string(j) + "-" + std::to_string(i);

                    // Avoid duplicate edges
                    if (uniqueEdges.find(reverseEdge) == uniqueEdges.end()) {
                        edgeList.emplace_back(i, j, graph[i][j]);
                        uniqueEdges.insert(edge);
                    }
                }
            }
        }
        return edgeList;
    }

    // Count the total number of edges in the graph
    int Graph::countEdges() const {
        return edges().size();
    }

    // Check if a given matrix is square (has the same number of rows and columns)
    bool Graph::isSquareMatrix(const std::vector<std::vector<int>>& matrix) const {
        size_t n = matrix.size();
        for (const auto& row : matrix) {
            if (row.size() != n) return false;
        }
        return true;
    }
    Graph Graph::operator+(const Graph& other) const {
        if (this->vertices() == 0 || other.vertices() == 0) {
            throw std::logic_error("Attempted to add empty graphs");
        }
        if (adjacency_matrix.size() != other.adjacency_matrix.size()) {
            throw std::invalid_argument("Cannot add graphs with different sizes");
        }
        Graph result;
        result.adjacency_matrix.resize(adjacency_matrix.size(), std::vector<int>(adjacency_matrix.size(), 0));
        for (size_t i = 0; i < adjacency_matrix.size(); ++i) {
            for (size_t j = 0; j < adjacency_matrix[i].size(); ++j) {
                result.adjacency_matrix[i][j] = adjacency_matrix[i][j] + other.adjacency_matrix[i][j];
                if (this->graph[i][j] > std::numeric_limits<int>::max() - other.graph[i][j]) {
                    throw std::overflow_error("Integer overflow in graph addition");
                }
            }
        }
        return result;
    }


    Graph& Graph::operator+=(const Graph& other) {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Cannot add graphs with different sizes");
        }

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                graph[i][j] += other.graph[i][j];
            }
        }

        return *this;
    }

    Graph Graph::operator-(const Graph& other) const {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Cannot subtract graphs with different sizes");
        }

        Graph result;
        result.numVertices = numVertices;
        result.graph.resize(numVertices, std::vector<int>(numVertices));

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                result.graph[i][j] = graph[i][j] - other.graph[i][j];
            }
        }

        return result;
    }

    Graph& Graph::operator-=(const Graph& other) {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Cannot subtract graphs with different sizes");
        }

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                graph[i][j] -= other.graph[i][j];
            }
        }

        return *this;
    }

    Graph Graph::operator*(const Graph& other) const {
        if (this->vertices() == 0 || other.vertices() == 0) {
            throw std::logic_error("Attempted to multiply empty graphs");
        }
        if (adjacency_matrix.size() != other.adjacency_matrix.size()) {
            throw std::invalid_argument("Cannot multiply graphs with different sizes");
        }
        Graph result;
        size_t n = adjacency_matrix.size();
        result.adjacency_matrix.resize(n, std::vector<int>(n, 0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                result.adjacency_matrix[i][j] = 0; // Initialize to zero before summing
                for (size_t k = 0; k < n; ++k) {
                    result.adjacency_matrix[i][j] += adjacency_matrix[i][k] * other.adjacency_matrix[k][j];
                }
            }
        }
        return result;
    }

    Graph& Graph::operator*=(const Graph& other) {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Cannot multiply graphs with different sizes");
        }

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                graph[i][j] *= other.graph[i][j];
            }
        }

        return *this;
    }

    Graph Graph::operator*(int scalar) const {
        Graph result;
        result.numVertices = numVertices;
        result.graph.resize(numVertices, std::vector<int>(numVertices));

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                result.graph[i][j] = graph[i][j] * scalar;
            }
        }

        return result;
    }

    Graph& Graph::operator*=(int scalar) {
        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                graph[i][j] *= scalar;
            }
        }

        return *this;
    }

    Graph Graph::operator/(int scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Cannot divide by zero");
        }

        Graph result;
        result.numVertices = numVertices;
        result.graph.resize(numVertices, std::vector<int>(numVertices));

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                result.graph[i][j] = graph[i][j] / scalar;
            }
        }

        return result;
    }

    Graph& Graph::operator/=(int scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Cannot divide by zero");
        }

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                graph[i][j] /= scalar;
            }
        }

        return *this;
    }

    bool Graph::operator==(const Graph& other) const {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Cannot compare graphs with different sizes");
        }

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                if (graph[i][j] != other.graph[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Graph::operator!=(const Graph& other) const {
        return !(*this == other);
    }

    bool Graph::operator<(const Graph& other) const {
        if (numVertices != other.numVertices) {
            throw std::invalid_argument("Cannot compare graphs with different sizes");
        }

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                if (graph[i][j] >= other.graph[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Graph::operator<=(const Graph& other) const {
        return (*this < other) || (*this == other);
    }

    bool Graph::operator>(const Graph& other) const {
        return !(*this <= other);
    }

    bool Graph::operator>=(const Graph& other) const {
        return !(*this < other);
    }

    Graph Graph::operator+() const {
        return *this;
    }

    Graph Graph::operator-() const {
        Graph result;
        result.numVertices = numVertices;
        result.graph.resize(numVertices, std::vector<int>(numVertices));

        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                result.graph[i][j] = -graph[i][j];
            }
        }

        return result;
    }

    Graph& Graph::operator++() {
        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                ++graph[i][j];
            }
        }

        return *this;
    }

    Graph Graph::operator++(int) {
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    Graph& Graph::operator--() {
        for (std::size_t i = 0; i < numVertices; ++i) {
            for (std::size_t j = 0; j < numVertices; ++j) {
                --graph[i][j];
            }
        }

        return *this;
    }

    Graph Graph::operator--(int) {
        Graph temp = *this;
        --(*this);
        return temp;
    }

    std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        for (std::size_t i = 0; i < graph.numVertices; ++i) {
            os << "[";
            for (std::size_t j = 0; j < graph.numVertices; ++j) {
                os << graph.graph[i][j];
                if (j < graph.numVertices - 1) {
                    os << " ";
                }
            }
            os << "]";
            if (i < graph.numVertices - 1) {
                os << std::endl;
            }
        }
        return os;
    }

    std::istream& operator>>(std::istream& is, Graph& graph) {
        std::vector<std::vector<int>> tempGraph;
        std::string line;
        while (std::getline(is, line)) {
            std::vector<int> row;
            std::istringstream rowStream(line);
            int value;
            while (rowStream >> value) {
                row.push_back(value);
            }
            tempGraph.push_back(row);
        }

        if (!graph.isSquareMatrix(tempGraph)) {
            throw std::invalid_argument("Invalid input: The graph is not a square matrix.");
        }

        graph.loadGraph(tempGraph);
        return is;
    }

} // namespace ariel