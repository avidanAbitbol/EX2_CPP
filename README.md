
# Graph Library Documentation

## Overview
The Graph Library is a robust C++ library designed for manipulating and analyzing graphs through a comprehensive suite of operations and functionalities. This library supports representing graphs as adjacency matrices and provides methods for graph operations such as addition, subtraction, multiplication, and division, alongside utility functions for graph comparison and manipulation.

## Features
- **Graph Construction**: Load and initialize graphs using adjacency matrices.
- **Graph Operations**:
  - Addition, subtraction, and multiplication of graphs.
  - Scalar multiplication and division.
  - Increment and decrement operations.
- **Utility Functions**:
  - Checking if a matrix is square.
  - Retrieving the adjacency matrix, vertex count, and adjacency list.
  - Edge list retrieval and edge count.

## Installation
To use the Graph Library, include the `Graph.hpp` header in your C++ project and ensure that your compiler supports C++17 or later due to the usage of modern C++ features and STL.

```cpp
#include "Graph.hpp"
```

## How to Run
To compile and run a sample program using the Graph Library, follow these steps:

### Compiling the Program
Assuming you have a C++ compiler that supports C++17, you can compile your program as follows:

```bash
g++ -std=c++17 -o my_graph_program my_program.cpp
```

Replace `my_program.cpp` with the name of your file that includes the main function and uses the Graph library.

### Running the Program
After compilation, run the program by executing the output binary:

```bash
./my_graph_program
```

### Sample Program
Here is a simple example of a program that creates a graph, performs some operations, and prints the results:

```cpp
#include "Graph.hpp"
#include <iostream>

int main() {
    ariel::Graph g;
    std::vector<std::vector<int>> matrix = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g.loadGraph(matrix);

    // Display original graph
    std::cout << "Original Graph:\n" << g.printGraph() << std::endl;

    // Performing addition
    ariel::Graph g2 = g;
    ariel::Graph sum = g + g2;
    std::cout << "Graph After Addition:\n" << sum.printGraph() << std::endl;

    return 0;
}
```

## Usage

### Creating a Graph
```cpp
#include "Graph.hpp"

ariel::Graph g;
std::vector<std::vector<int>> matrix = {
    {0, 1, 0},
    {1, 0, 1},
    {0, 1, 0}
};
g.loadGraph(matrix);
```

### Performing Operations
You can perform various graph operations as follows:

#### Addition
```cpp
ariel::Graph g1, g2;
g1.loadGraph(matrix1);
g2.loadGraph(matrix2);
ariel::Graph g3 = g1 + g2;
```

#### Multiplication
```cpp
ariel::Graph result = g1 * g2;
```

#### Scalar Operations
```cpp
ariel::Graph scaledUp = g * 2;   // Scalar multiplication
ariel::Graph scaledDown = g / 2; // Scalar division
```

### Advanced Functionalities
Accessing the adjacency list and printing the graph:

```cpp
std::cout << "Adjacency List for vertex 0: ";
const auto& adjList = g.adj(0);
for (int adj : adjList) {
    std::cout << adj << " ";
}
std::cout << std::endl;

std::cout << "Graph structure:\n" << g.printGraph() << std::endl;
```

## Error Handling
The library is designed to throw exceptions in case of errors such as invalid operations (e.g., adding graphs of different sizes or dividing by zero).

```cpp
try {
    ariel::Graph result = g1 + g2;
} catch (const std::invalid_argument& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
```

## Contributing
Contributions to the Graph Library are welcome. Please feel free to fork the repository, make changes, and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

