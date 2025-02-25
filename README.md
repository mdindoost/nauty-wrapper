# Nauty Wrapper

A C++ wrapper for the Nauty graph analysis library, specifically designed for integration with Chapel. This wrapper provides a clean interface to Nauty's graph isomorphism and automorphism computation capabilities.

# Overview
This wrapper provides a modern C++ interface to Nauty, a powerful tool for:

A C++ wrapper around Nauty's core functionality
Object files ready for Chapel integration
Support for graph isomorphism testing
Easy integration with Chapel projects

# Prerequisites

C++ compiler with C++17 support
Make build system
Nauty (automatically downloaded and built)

# Project Structure

nauty-wrapper/
├── bin/                   # Compiled object files
├── external/
│   └── nauty2_8_9/       # Nauty source code
├── include/
│   └── nautyClassify.h   # Wrapper header file
└── src/
    ├── nautyClassify.cpp # Wrapper implementation
    └── test_nautyClassify.cpp # Test program

# Building

Clone the repository:

```bash
git clone (https://github.com/mdindoost/nauty-wrapper)
cd nauty-wrapper
```

Download and extract Nauty:


```bash
# Create external directory and download Nauty
mkdir -p external
cd external
wget https://pallini.di.uniroma1.it/nauty2_8_9.tar.gz
tar -xzf nauty2_8_9.tar.gz
rm nauty2_8_9.tar.gz

# Build Nauty
cd nauty2_8_9
./configure CFLAGS="-fPIC -O3"
make
cd ../..
```
# Create necessary directories:

mkdir -p bin
mkdir -p include
mkdir -p src

# Build the wrapper and all necessary object files:
make clean
make

# Verify the build:

make verify_objects
make test


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
# Integration with Chapel
To use this wrapper in your Chapel project:

Add this repository as a submodule:

git submodule add <repository-url> path/to/nauty-wrapper

In your Chapel code, require the necessary files:

chapelCopyrequire "nauty-wrapper/bin/nautyClassify.o",
        "nauty-wrapper/include/nautyClassify.h",
        "nauty-wrapper/bin/nauty.o",
        "nauty-wrapper/bin/nautil.o",
        "nauty-wrapper/bin/naugraph.o",
        "nauty-wrapper/bin/schreier.o",
        "nauty-wrapper/bin/naurng.o",
        "nauty-wrapper/bin/nausparse.o";

// Declare the external function
extern proc c_nautyClassify(
    subgraph: [] int(64), 
    subgraphSize: int(64), 
    results: [] int(64),
    performCheck: int(64),
    verbose: int(64)
) : int(64);
Function Documentation
nautyClassify

int64_t nautyClassify(
    int64_t subgraph[],     // Input adjacency matrix
    int64_t subgraphSize,   // Size of the matrix
    int64_t results[],      // Output array for vertex mappings
    int64_t performCheck,   // Validation flag
    int64_t verbose         // Debug output flag
);
Parameters:

subgraph: Adjacency matrix representing the graph
subgraphSize: Number of vertices in the graph
results: Array to store the resulting vertex mappings
performCheck: Flag to enable additional validation
verbose: Flag to enable detailed debug output

Returns:

0 on success
Negative values indicate specific errors

Examples
C++ usage:
cppCopyint64_t subgraph[] = {
    0, 1, 0,
    0, 0, 1,
    0, 0, 0
};
int64_t results[3];
int64_t ret = nautyClassify(subgraph, 3, results, 1, 1);
Chapel usage:
chapelCopyvar subgraph: [0..8] int(64) = [0, 1, 0, 0, 0, 1, 0, 0, 0];
var results: [0..2] int(64);
var ret = c_nautyClassify(subgraph, 3, results, 1, 1);
# Arachne users
```bash
git submodule update --init --recursive
```
1. First, create the external directory and download nauty:

```bash
# From nauty-wrapper directory
mkdir -p external
cd external
wget https://pallini.di.uniroma1.it/nauty2_8_9.tar.gz
tar -xzf nauty2_8_9.tar.gz
rm nauty2_8_9.tar.gz
cd ..
```
2. Now let's copy the automake config files:


```bash
# First check if they exist
ls /usr/share/automake*/config.guess
ls /usr/share/automake*/config.sub

# Then copy them
cp /usr/share/automake-1.16/config.guess external/nauty2_8_9/
cp /usr/share/automake-1.16/config.sub external/nauty2_8_9/
```
3. Now try building:
```bash
make clean
make
make verify_objects
```

# License
This wrapper is provided under the MIT License. Note that Nauty itself has its own license terms which must be respected.
Acknowledgments

Based on Nauty by Brendan McKay and Adolfo Piperno
Nauty's website: http://pallini.di.uniroma1.it/
