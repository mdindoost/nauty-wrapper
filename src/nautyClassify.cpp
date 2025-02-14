#include "nautyClassify.h"
#include <nauty.h>
#include <cstring>
#include <iostream>

#define LOCAL_MAXN 100
#define LOCAL_MAXM ((LOCAL_MAXN + WORDSIZE - 1) / WORDSIZE)
#define WORKSPACE_SIZE 50

extern "C" {

int64_t nautyClassify(
    int64_t subgraph[], 
    int64_t subgraphSize, 
    int64_t results[], 
    int64_t performCheck, 
    int64_t verbose
) {
    if (verbose) {
        std::cout << "\n==== Starting Nauty Classification ====" << std::endl;
        std::cout << "Parameters:" << std::endl;
        std::cout << "subgraphSize: " << subgraphSize << std::endl;
        std::cout << "performCheck: " << performCheck << std::endl;
    }

    // Check size constraints
    if (subgraphSize <= 0 || subgraphSize > LOCAL_MAXN) {
        std::cerr << "Error: Invalid subgraphSize: " << subgraphSize << " (max allowed: " << LOCAL_MAXN << ")" << std::endl;
        return -1;
    }

    // Calculate required words for sets
    int m = SETWORDSNEEDED(subgraphSize);
    if (m > LOCAL_MAXM) {
        std::cerr << "Error: Required words exceeds MAXM" << std::endl;
        return -2;
    }

    // Perform nauty check if requested
    if (performCheck) {
        if (verbose) {
            std::cout << "Performing nauty_check..." << std::endl;
        }
        try {
            nauty_check(WORDSIZE, m, subgraphSize, NAUTYVERSIONID);
            if (verbose) {
                std::cout << "nauty_check passed" << std::endl;
            }
        } catch (...) {
            std::cerr << "Error: nauty_check failed" << std::endl;
            return -3;
        }
    }

    // Allocate arrays
    graph g[LOCAL_MAXN * LOCAL_MAXM];
    graph canong[LOCAL_MAXN * LOCAL_MAXM];
    int lab[LOCAL_MAXN];
    int ptn[LOCAL_MAXN];
    int orbits[LOCAL_MAXN];
    setword workspace[WORKSPACE_SIZE * LOCAL_MAXM];

    // Zero out the arrays
    std::memset(g, 0, sizeof(g));
    std::memset(canong, 0, sizeof(canong));
    std::memset(lab, 0, sizeof(lab));
    std::memset(ptn, 0, sizeof(ptn));
    std::memset(orbits, 0, sizeof(orbits));
    std::memset(workspace, 0, sizeof(workspace));

    // Initialize options
    DEFAULTOPTIONS_GRAPH(options);
    options.getcanon = TRUE;
    options.defaultptn = TRUE;
    options.digraph = TRUE;
    statsblk stats;

    // Initialize lab, ptn arrays
    for (int i = 0; i < subgraphSize; i++) {
        lab[i] = i;
        ptn[i] = 1;
    }
    ptn[subgraphSize-1] = 0;

    // Convert input matrix to nauty graph format
    for (int i = 0; i < subgraphSize; i++) {
        set* gv = GRAPHROW(g, i, m);
        EMPTYSET(gv, m);
        
        for (int j = 0; j < subgraphSize; j++) {
            if (i != j && subgraph[i * subgraphSize + j] == 1) {
                ADDELEMENT(gv, j);
                if (verbose) {
                    std::cout << "Added edge: " << i << " -> " << j << std::endl;
                }
            }
        }
    }

    if (verbose) {
        std::cout << "\nCalling nauty..." << std::endl;
    }

    // Call nauty
    nauty(g, lab, ptn, nullptr, orbits, &options, &stats, 
          workspace, WORKSPACE_SIZE * m, m, subgraphSize, canong);

    if (verbose) {
        std::cout << "Nauty completed. Copying results..." << std::endl;
    }

    // Validate results
    bool validPermutation = true;
    bool* used = new bool[subgraphSize]();
    
    for (int i = 0; i < subgraphSize; i++) {
        if (lab[i] < 0 || lab[i] >= subgraphSize || used[lab[i]]) {
            validPermutation = false;
            break;
        }
        used[lab[i]] = true;
    }
    
    delete[] used;
    
    if (!validPermutation) {
        std::cerr << "Error: Invalid permutation generated" << std::endl;
        return -4;
    }

    // Copy results
    for (int i = 0; i < subgraphSize; i++) {
        results[i] = lab[i];
        if (verbose) {
            std::cout << "results[" << i << "] = " << results[i] << std::endl;
        }
    }

    if (verbose) {
        std::cout << "\n==== Nauty Classification Complete ====\n" << std::endl;
    }

    return 0;
}

int64_t c_nautyClassify(
    int64_t subgraph[], 
    int64_t subgraphSize, 
    int64_t results[], 
    int64_t performCheck, 
    int64_t verbose
) {
    return nautyClassify(subgraph, subgraphSize, results, performCheck, verbose);
}

} // extern "C"