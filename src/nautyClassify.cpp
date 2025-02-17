#include "nautyClassify.h"
#include <nauty.h>
#include <cstring>
#include <iostream>
#include <mutex>
#include <memory>

static std::mutex cout_mutex;
static std::mutex nauty_mutex;

extern "C" {

int64_t nautyClassify(
    int64_t subgraph[], 
    int64_t subgraphSize, 
    int64_t results[], 
    int64_t performCheck, 
    int64_t verbose
) {
    auto print_verbose = [&](const std::string& msg) {
        if (verbose) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << msg << std::endl;
        }
    };

    print_verbose("\n==== Starting Nauty Classification ====");
    print_verbose("Parameters:");
    print_verbose("subgraphSize: " + std::to_string(subgraphSize));
    print_verbose("performCheck: " + std::to_string(performCheck));

    // Calculate array sizes
    int m = SETWORDSNEEDED(subgraphSize);
    if (subgraphSize > WORDSIZE * m) {
        std::cerr << "Error: Graph size too large for current word size" << std::endl;
        return -1;
    }

    // Allocate arrays with exact sizes needed
    std::unique_ptr<graph[]> g(new graph[m * subgraphSize]);
    std::unique_ptr<graph[]> canong(new graph[m * subgraphSize]);
    std::unique_ptr<int[]> lab(new int[subgraphSize]);
    std::unique_ptr<int[]> ptn(new int[subgraphSize]);
    std::unique_ptr<int[]> orbits(new int[subgraphSize]);
    std::unique_ptr<setword[]> workspace(new setword[100 * m]); // Increased workspace
    std::unique_ptr<bool[]> used(new bool[subgraphSize]);

    // Zero out the arrays
    std::memset(g.get(), 0, sizeof(graph) * m * subgraphSize);
    std::memset(canong.get(), 0, sizeof(graph) * m * subgraphSize);
    std::memset(lab.get(), 0, sizeof(int) * subgraphSize);
    std::memset(ptn.get(), 0, sizeof(int) * subgraphSize);
    std::memset(orbits.get(), 0, sizeof(int) * subgraphSize);
    std::memset(workspace.get(), 0, sizeof(setword) * 100 * m);
    std::memset(used.get(), 0, sizeof(bool) * subgraphSize);

    // Perform nauty check if requested
    if (performCheck) {
        print_verbose("Performing nauty_check...");
        std::lock_guard<std::mutex> lock(nauty_mutex);
        try {
            nauty_check(WORDSIZE, m, subgraphSize, NAUTYVERSIONID);
            print_verbose("nauty_check passed");
        } catch (...) {
            std::cerr << "Error: nauty_check failed" << std::endl;
            return -3;
        }
    }

    // Initialize lab, ptn arrays
    for (int i = 0; i < subgraphSize; i++) {
        lab[i] = i;
        ptn[i] = 1;
    }
    ptn[subgraphSize-1] = 0;

    // Convert input matrix to nauty graph format
    for (int i = 0; i < subgraphSize; i++) {
        set* gv = GRAPHROW(g.get(), i, m);
        EMPTYSET(gv, m);
        
        for (int j = 0; j < subgraphSize; j++) {
            if (i != j && subgraph[i * subgraphSize + j] == 1) {
                ADDELEMENT(gv, j);
                print_verbose("Added edge: " + std::to_string(i) + " -> " + std::to_string(j));
            }
        }
    }

    print_verbose("\nCalling nauty with m=" + std::to_string(m) + ", n=" + std::to_string(subgraphSize));

    // Create options (must be thread-local)
    DEFAULTOPTIONS_GRAPH(options);
    options.getcanon = TRUE;
    options.defaultptn = TRUE;
    options.digraph = TRUE;
    statsblk stats;

    {
        std::lock_guard<std::mutex> lock(nauty_mutex);
        nauty(g.get(), lab.get(), ptn.get(), nullptr, orbits.get(), &options, &stats, 
              workspace.get(), 100 * m, m, subgraphSize, canong.get());
    }

    print_verbose("Nauty completed. Validating results...");

    // Validate permutation
    bool validPermutation = true;
    for (int i = 0; i < subgraphSize; i++) {
        if (lab[i] < 0 || lab[i] >= subgraphSize || used[lab[i]]) {
            validPermutation = false;
            break;
        }
        used[lab[i]] = true;
    }

    if (!validPermutation) {
        std::cerr << "Error: Invalid permutation generated" << std::endl;
        return -4;
    }

    // Copy results
    for (int i = 0; i < subgraphSize; i++) {
        results[i] = lab[i];
        print_verbose("results[" + std::to_string(i) + "] = " + std::to_string(results[i]));
    }

    print_verbose("\n==== Nauty Classification Complete ====\n");
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