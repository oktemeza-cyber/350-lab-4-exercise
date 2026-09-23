#ifndef P2A_H
#define P2A_H

#include <cassert>  // assert
#include <cstddef>  // size_t
#include <cstdint>  // uint64_t, uint32_t

// Expands the binary representation of input by a factor of scale.
// e.g., expand(0b1111ull, 3) == 0b001001001001
inline uint64_t expand(uint64_t input, uint32_t scale) {
    assert(scale < 64);
    uint64_t result = 0;
    for(uint32_t i = 0; i < 64; i++){
        uint64_t bit = (input >> i) & 1ull;
        result |= bit << (i * scale);
    }
    return result;  
}

inline uint64_t morton3d(uint64_t x, uint64_t y, uint64_t z){
    return expand(x, 3) + (expand(y, 3) << 1) + (expand(z, 3) << 2);
}

#endif