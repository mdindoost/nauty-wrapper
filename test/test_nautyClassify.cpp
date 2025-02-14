#include "nautyClassify.h"
#include <iostream>
#include <cassert>
#include <vector>

// Utility function to check if result is a valid permutation
bool isValidPermutation(const int64_t results[], int64_t size) {
    std::vector<bool> used(size, false);
    for (int i = 0; i < size; i++) {
        if (results[i] < 0 || results[i] >= size || used[results[i]]) {
            return false;
        }
        used[results[i]] = true;
    }
    return true;
}

// Test case 1: Simple directed path
void testSimpleDirectedPath() {
    std::cout << "\nTest 1: Simple directed path (0->1->2)" << std::endl;
    
    int64_t subgraph[] = {
        0, 1, 0,
        0, 0, 1,
        0, 0, 0
    };
    
    int64_t subgraphSize = 3;
    int64_t results[3];
    
    int64_t ret = nautyClassify(subgraph, subgraphSize, results, 1, 1);
    
    assert(ret == 0 && "Test 1 should not return error");
    assert(isValidPermutation(results, subgraphSize) && "Test 1 should return valid permutation");
}

// Test case 2: Symmetric path
void testSymmetricPath() {
    std::cout << "\nTest 2: Symmetric path (0<->1<->2)" << std::endl;
    
    int64_t subgraph[] = {
        0, 1, 0,
        1, 0, 1,
        0, 1, 0
    };
    
    int64_t subgraphSize = 3;
    int64_t results[3];
    
    int64_t ret = nautyClassify(subgraph, subgraphSize, results, 1, 1);
    
    assert(ret == 0 && "Test 2 should not return error");
    assert(isValidPermutation(results, subgraphSize) && "Test 2 should return valid permutation");
}

// Test case 3: Triangle
void testTriangle() {
    std::cout << "\nTest 3: Directed triangle (0->1->2->0)" << std::endl;
    
    int64_t subgraph[] = {
        0, 1, 0,
        0, 0, 1,
        1, 0, 0
    };
    
    int64_t subgraphSize = 3;
    int64_t results[3];
    
    int64_t ret = nautyClassify(subgraph, subgraphSize, results, 1, 1);
    
    assert(ret == 0 && "Test 3 should not return error");
    assert(isValidPermutation(results, subgraphSize) && "Test 3 should return valid permutation");
}

// Test case 4: Empty graph
void testEmptyGraph() {
    std::cout << "\nTest 4: Empty graph (no edges)" << std::endl;
    
    int64_t subgraph[] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    };
    
    int64_t subgraphSize = 3;
    int64_t results[3];
    
    int64_t ret = nautyClassify(subgraph, subgraphSize, results, 1, 1);
    
    assert(ret == 0 && "Test 4 should not return error");
    assert(isValidPermutation(results, subgraphSize) && "Test 4 should return valid permutation");
}

// Test case 5: Invalid size
void testInvalidSize() {
    std::cout << "\nTest 5: Invalid graph size" << std::endl;
    
    int64_t subgraph[] = {0};
    int64_t results[1];
    
    int64_t ret = nautyClassify(subgraph, 0, results, 1, 1);
    
    assert(ret < 0 && "Test 5 should return error for invalid size");
}

int main() {
    std::cout << "Starting Nauty Classification Tests" << std::endl;
    
    try {
        testSimpleDirectedPath();
        testSymmetricPath();
        testTriangle();
        testEmptyGraph();
        testInvalidSize();
        
        std::cout << "\nAll tests passed successfully!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        return 1;
    }
    
    return 0;
}