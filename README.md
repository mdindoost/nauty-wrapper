# Nauty Wrapper

A C++ wrapper for the Nauty graph isomorphism library.

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Testing

```bash
make test
```

## Usage

```cpp
#include <nauty_wrapper.hpp>

nauty::Graph g(3);  // Create a graph with 3 vertices
g.addEdge(0, 1);    // Add an edge between vertices 0 and 1
g.addEdge(1, 2);    // Add an edge between vertices 1 and 2

// Check if two graphs are isomorphic
nauty::Graph h(3);
h.addEdge(1, 2);
h.addEdge(0, 1);
bool isomorphic = g.isomorphicTo(h);  // Should return true

// Get automorphisms
auto autos = g.getAutomorphisms();
```

## License

This wrapper is provided under the MIT License. Note that Nauty itself has its own license terms which must be respected.