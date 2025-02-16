#include "nautyClassify.h"
#include <iostream>

int main() {
    // Test case 1: Simple directed path
    std::cout << "\nTest 1: Simple directed path (0->1->2)" << std::endl;
    
    int64_t subgraph[] = {
        0, 1, 0,
        0, 0, 1,
        0, 0, 0
    };
    
    int64_t subgraphSize = 3;
    int64_t results[3];
    
    int64_t ret = nautyClassify(subgraph, subgraphSize, results, 1, 1);
    
    std::cout << "Return value: " << ret << std::endl;
    std::cout << "Results: ";
    for (int i = 0; i < subgraphSize; i++) {
        std::cout << results[i] << " ";
    }
    std::cout << std::endl;

    // Test case 2: Symmetric path
    std::cout << "\nTest 2: Symmetric path (0<->1<->2)" << std::endl;
    
    int64_t subgraph2[] = {
        0, 1, 0,
        1, 0, 1,
        0, 1, 0
    };
    
    ret = nautyClassify(subgraph2, subgraphSize, results, 1, 1);
    
    std::cout << "Return value: " << ret << std::endl;
    std::cout << "Results: ";
    for (int i = 0; i < subgraphSize; i++) {
        std::cout << results[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}