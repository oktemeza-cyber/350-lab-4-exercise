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
    std::vector<uint64_t> array1;
    std::vector<uint64_t> array2;
    uint64_t sum1 = 0;
    uint64_t sum2 = 0;
    uint64_t timeTakenArray1;
    uint64_t timeTakenArray2;

    Timer time{};
    std::mt19937_64 rng(0); // initialize with seed of 0

    for(size_t i = 0; i < SIZE; i++){
       array1.push_back(rng());
    }

    for(size_t i = 0; i < SIZE; i++){
       sum1 += array1[i];
    }
    timeTakenArray1 = time.click<std::chrono::microseconds>();

    rng.seed(0);
    for(size_t col = 0; col < static_cast<size_t>(4000); col++){
        for(size_t row = 0; row < static_cast<size_t>(4000); row++){
            size_t index = col * static_cast<size_t>(4000) + row;
            array2[index] = rng();
        }
    }

    for(size_t i = 0; i < SIZE; i++){
       sum2 += array2[i];
    }
    timeTakenArray2 = time.click<std::chrono::microseconds>();



    std::cout << "List population row major time taken: " << timeTakenArray1 << "  " << sum1;
    std::cout << "\nList population 2 column major time taken: " << timeTakenArray2 << "  " << sum2 << "\n";
    
    
    return 0; 
}