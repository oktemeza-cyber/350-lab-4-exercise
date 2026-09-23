#include <cstddef>  // size_t
#include <cstdint>
#include <iostream>
#include <list>
#include <vector>
#include <chrono>
#include <random>
#include "timer.h"

constexpr size_t SIZE = 16000000;

int main() { 
    std::vector<uint64_t> array1(SIZE);
    std::vector<uint64_t> array2(SIZE);
    uint64_t sum1 = 0;
    uint64_t sum2 = 0;
    uint64_t timeTakenSum1;
    uint64_t timeTakenSum2;
    size_t dimensions = 4000;


    Timer time{};
    std::mt19937_64 rng(0); // initialize with seed of 0

    for(size_t row = 0; row < dimensions; row++){
        for(size_t col = 0; col < dimensions; col++){
            size_t index = row * dimensions + col;
            array1[index] = rng();
        }
    }
    //timeTakenArray1 = time.click<std::chrono::microseconds>();

    rng.seed(0);
    for(size_t col = 0; col < dimensions; col++){
        for(size_t row = 0; row < dimensions; row++){
            size_t index = col * dimensions + row;
            array2[index] = rng();
        }
    }
    //timeTakenArray2 = time.click<std::chrono::microseconds>();

    for(size_t row = 0; row < dimensions; row++){
        for(size_t col = 0; col < dimensions; col++){
            size_t index = row * dimensions + col;
            sum1 += array1[index];
        }
    }
    timeTakenSum1 = time.click<std::chrono::microseconds>();


    for(size_t col = 0; col < dimensions; col++){
       for(size_t row = 0; row < dimensions; row++){
        size_t index = row * dimensions + col;
        sum2 += array2[index];
       }
    }
    timeTakenSum2 = time.click<std::chrono::microseconds>();



    std::cout << "List population row major time taken: " << timeTakenSum1 << "  " << sum1;
    std::cout << "\nList population 2 column major time taken: " << timeTakenSum2 << "  " << sum2 << "\n";
    
    
    return 0; 
}