# Nauty Wrapper

A C++ wrapper for the Nauty graph isomorphism library.

# Overview
This wrapper provides a modern C++ interface to Nauty, a powerful tool for:

Graph isomorphism testing
Computing automorphism groups
Working with graph symmetries

# Prerequisites

CMake (3.10 or higher)
C++ compiler with C++17 support
Make

# Installation

Download Nauty:

Copymkdir external
cd external
wget https://pallini.di.uniroma1.it/nauty2_8_9.tar.gz
tar -xzf nauty2_8_9.tar.gz
rm nauty2_8_9.tar.gz

Build Nauty:

cd nauty2_8_9
./configure
make
cd ../..


## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Testing
Run all tests:

```bash
cd build
make test
```
Or run test executable directly:
./test/wrapper_test

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
License
This wrapper is provided under the MIT License. Note that Nauty itself has its own license terms which must be respected.
Acknowledgments

Based on Nauty by Brendan McKay and Adolfo Piperno
More information about Nauty can be found at: http://pallini.di.uniroma1.it

## License

This wrapper is provided under the MIT License. Note that Nauty itself has its own license terms which must be respected.
