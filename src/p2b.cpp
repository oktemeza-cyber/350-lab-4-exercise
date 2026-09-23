#include <cstddef>  // size_t
#include <cstdint>
#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <random>
#include "timer.h"
#include "p2a.h"

size_t matrixBlockDim = 256/4;
//GOT IT its for the matrix visualization and blocks
size_t blockCount = 4;
size_t rowMajorIndexA(size_t x, size_t y, size_t z){
    return z * (static_cast<size_t>(256)*static_cast<size_t>(256)) + y * (static_cast<size_t>(256)) + x;
}

size_t rowMajorIndexK(size_t x, size_t y, size_t z){
    return z * (static_cast<size_t>(4)*(static_cast<size_t>(4))) + y * (static_cast<size_t>(4)) + x;
}

size_t rowMajorIndexConv(size_t x, size_t y, size_t z){
    return z * (matrixBlockDim*matrixBlockDim) + y * (matrixBlockDim) + x;
}
//helper functions specified in lab hints and to help with implementation


int main() { 
    std::vector<uint64_t> standardASize(static_cast<size_t>(16777216));
    std::vector<uint64_t> mortonBSize(static_cast<size_t>(16777216));

    std::vector<uint64_t> standardAKernel(matrixBlockDim);
    std::vector<uint64_t> mortonBKernel(matrixBlockDim);

    std::mt19937_64 rng(0); // initialize with seed of 0
    for(size_t index = 0; index < static_cast<size_t>(16777216); index++){
        standardASize[index] = rng();
    }//similar to how I did p1.cpp population
    
    for(size_t z = 0; z < static_cast<size_t>(256); z++){
        for(size_t y = 0; y < static_cast<size_t>(256); y++){
            for(size_t x = 0; x < static_cast<size_t>(256); x++){
                mortonBSize[morton3d(x, y, z)] = standardASize[rowMajorIndexA(x, y, z)];
            }
        }

    } //triple nested loop necessary for all dimensions -- for Morton

    for(size_t z = 0; z < blockCount; z++){
        for(size_t y = 0; y < blockCount; y++){
            for(size_t x = 0; x < blockCount; x++){
                uint64_t val = x + y + z;
                standardAKernel[rowMajorIndexK(x, y, z)] = val;
                mortonBKernel[morton3d(x, y, z)] = val;
            }
        }
    } //triple nested loop again necessary for all dimensions, this time for Norton and Kernel matrix dimensions

    Timer timer{};

    //start the insane 6 nested for loop mess
    for(size_t z = 0; z < matrixBlockDim; z++){
        for(size_t y = 0; y < matrixBlockDim; y++){
            for(size_t x = 0; x < matrixBlockDim; x++){
                uint64_t sum = 0;
                for(size_t k = 0; k < blockCount; k++){
                    for(size_t j = 0; j < blockCount; j++){
                        for(size_t i = 0; i < blockCount; i++){
                            size_t x1 = x * blockCount + i;
                            size_t y1 = y * blockCount + j;
                            size_t z1 = z * blockCount+ k;
                            sum += standardASize[rowMajorIndexA(x1, y1, z1)] * standardAKernel[rowMajorIndexK(i, j, k)];
                        }
                    }
                }
                sum = rowMajorIndexConv(x, y, z);
            }
        }
    }
    //A 6 nested loop is required due to the joint effort of morton3d function we created earlier, and the rowMajorIndex helper function we specified above--no same variable can be used as a parameter as it would heavily
    //impact the result

    uint64_t timerowMajorIndexConv = timer.click<std::chrono::microseconds>();

    std::cout << timerowMajorIndexConv;

    //ran out of time for Morton convolution unfortunately, but it would follow the hint given
    //in the lab as a doubled nested loop instead of the 6 nested monstrosity we did before due to how
    //information is stored in Morton-Order compared to a matrix Kernel style we followed in array A-- rowMajorIndexA is not necessary at all
    
    return 0; 

}
