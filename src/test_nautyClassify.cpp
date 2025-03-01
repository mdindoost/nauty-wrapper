#include "nautyClassify.h"
#include <iostream>
#include <iomanip>
#include <vector>

void printMatrix(int64_t* matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << std::setw(2) << matrix[i * size + j] << " ";
        }
        std::cout << std::endl;
    }
}

void printResults(int64_t* results, int size) {
    std::cout << "Results: ";
    for (int i = 0; i < size; i++) {
        std::cout << results[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Test parameters
    const int k = 3;  // Motif size
    const int batchSize = 3;  // Number of matrices to process
    
    // Create test matrices
    std::vector<std::vector<int64_t>> testMatrices = {
        // Matrix 1: Simple directed path (0->1->2)
        {
            0, 1, 0,
            0, 0, 1,
            0, 0, 0
        },
        
        // Matrix 2: Symmetric path (0<->1<->2)
        {
            0, 1, 0,
            1, 0, 1,
            0, 1, 0
        },
        
        // Matrix 3: Directed cycle (0->1->2->0)
        {
            0, 1, 0,
            0, 0, 1,
            1, 0, 0
        }
    };
    
    // Allocate memory for batch processing
    const int matrixSize = k * k;
    int64_t* batchedMatrices = new int64_t[matrixSize * batchSize];
    int64_t* batchedResults = new int64_t[k * batchSize];
    
    // Fill batched matrices array
    for (int i = 0; i < batchSize && i < testMatrices.size(); i++) {
        for (int j = 0; j < matrixSize; j++) {
            batchedMatrices[i * matrixSize + j] = testMatrices[i][j];
        }
    }
    
    // Test single matrix processing first
    std::cout << "\n===== Testing Single Matrix Processing =====\n";
    for (int i = 0; i < testMatrices.size(); i++) {
        std::cout << "\nTest Matrix " << (i+1) << ":\n";
        printMatrix(testMatrices[i].data(), k);
        
        int64_t results[k];
        int64_t ret = c_nautyClassify(testMatrices[i].data(), k, results, 1, 0, 1);
        
        std::cout << "Return value: " << ret << std::endl;
        printResults(results, k);
    }
    
    // Test batch processing
    std::cout << "\n===== Testing Batch Processing (" << batchSize << " matrices) =====\n";
    
    // Print input matrices
    for (int i = 0; i < batchSize; i++) {
        std::cout << "\nInput Matrix " << (i+1) << ":\n";
        printMatrix(&batchedMatrices[i * matrixSize], k);
    }
    
    // Process batch
    int64_t ret = c_nautyClassify(batchedMatrices, k, batchedResults, 1, 0, batchSize);
    
    std::cout << "\nBatch processing return value: " << ret << std::endl;
    
    // Print results for each matrix
    for (int i = 0; i < batchSize; i++) {
        std::cout << "Results for Matrix " << (i+1) << ": ";
        printResults(&batchedResults[i * k], k);
    }
    
    // Clean up
    delete[] batchedMatrices;
    delete[] batchedResults;
    
    return 0;
}