#ifndef NAUTY_CLASSIFY_H
#define NAUTY_CLASSIFY_H

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

// Main classification function
int64_t nautyClassify(
    int64_t subgraph[],    // Input adjacency matrix
    int64_t subgraphSize,  // Size of the matrix
    int64_t results[],     // Output array for vertex mappings
    int64_t performCheck,  // Validation flag
    int64_t verbose        // Debug output flag
);

// C wrapper for Chapel interoperability
int64_t c_nautyClassify(
    int64_t subgraph[],
    int64_t subgraphSize,
    int64_t results[],
    int64_t performCheck,
    int64_t verbose
);

#ifdef __cplusplus
}
#endif

#endif // NAUTY_CLASSIFY_H