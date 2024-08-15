#include "modfuncs.h"
#include <cstdint>
using std::uint64_t;

// Implements modular addition without overflow. Helper function for modMul().
uint64_t modAdd(uint64_t x, uint64_t y, uint64_t modulus) {
    if (x >= modulus || y >= modulus) {
        x %= modulus;
        y %= modulus;
    }
    if (y < modulus - x) {return x + y;}
    else {return y - (modulus - x);} // ex. (65 + 57) % 100 = 57 - (100 - 65) = 57 - 35 = 22
}

// Implements modular multiplication by doubling to prevent overflow. Helper function for modExp().
uint64_t modMul(uint64_t x, uint64_t y, uint64_t modulus) {
    if (x >= modulus || y >= modulus) {
        x %= modulus;
        y %= modulus;
    }
    if (x <= 0xFFFFFFFF && y <= 0xFFFFFFFF) {return (x * y) % modulus;}
    uint64_t result = 0;
    while (y != 0) {
        if (y % 2 != 0) {result = modAdd(result, x, modulus);}
        x = modAdd(x, x, modulus);
        y >>= 1;
    }
    return result;
}

// Performs modular exponentiation by squaring. Ex: modExp(2,91,1000) = 2^91 mod 1000 = 448
uint64_t modExp(uint64_t base, uint64_t exp, uint64_t modulus) {
    if (modulus <= 1) {return 0;}
    base %= modulus;
    uint64_t result = 1;
    while (exp != 0) {
        if (exp % 2 != 0) {result = modMul(result, base, modulus);}
        base = modMul(base, base, modulus);
        exp >>= 1;
    }
    return result;
}