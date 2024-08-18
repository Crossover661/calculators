#ifndef MATHFUNCS_H
#define MATHFUNCS_H

#include <cstdint>
using std::uint64_t;

namespace math {
// Implements modular addition without overflow.
uint64_t modAdd(uint64_t x, uint64_t y, uint64_t modulus);

// Implements modular multiplication by doubling to prevent overflow.
uint64_t modMul(uint64_t x, uint64_t y, uint64_t modulus);

// Performs modular exponentiation. Ex: modExp(2,91,1000) = 2^91 mod 1000 = 448
uint64_t modExp(uint64_t base, uint64_t exp, uint64_t modulus);

// Finds the integer square root of a given non-negative value.
uint64_t intSqrt(uint64_t n);

// Raises x to the power of y.
uint64_t pow(uint64_t x, uint64_t y);
}

#endif