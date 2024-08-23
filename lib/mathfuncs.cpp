#include <cstdint>
#include "mathfuncs.hpp"
using std::uint64_t;

namespace math {

    uint64_t modAdd(uint64_t x, uint64_t y, uint64_t modulus) {
        if (x >= modulus || y >= modulus) {
            x %= modulus;
            y %= modulus;
        }
        if (y < modulus - x) {return x + y;}
        else {return y - (modulus - x);} // ex. (65 + 57) % 100 = 57 - (100 - 65) = 57 - 35 = 22
    }   

    uint64_t modMul(uint64_t x, uint64_t y, uint64_t modulus) {
        if (x >= modulus || y >= modulus) {
            x %= modulus;
            y %= modulus;
        }
        if (x <= 0xFFFFFFFF && y <= 0xFFFFFFFF) {return (x * y) % modulus;}
        uint64_t result = 0;
        while (y != 0) {
            if (y & 1) {result = modAdd(result, x, modulus);}
            x = modAdd(x, x, modulus);
            y >>= 1;
        }
        return result;
    }

    uint64_t modExp(uint64_t base, uint64_t exp, uint64_t modulus) {
        if (modulus <= 1) {return 0;}
        base %= modulus;
        uint64_t result = 1;
        while (exp != 0) {
            if (exp & 1) {result = modMul(result, base, modulus);}
            base = modMul(base, base, modulus);
            exp >>= 1;
        }
        return result;
    }

    uint64_t intSqrt(uint64_t n) {
        if (n <= 1) {return n;} // sqrt(0) = 0 and sqrt(1) = 1
        uint64_t x = n, y = (x - 1)/2 + 1;
        while (x > y) {
            x = y;
            y = (x + n/x)/2;
        }
        return x;
    }

    uint64_t pow(uint64_t x, uint64_t y) {
        if (x == 2) {return uint64_t(1) << y;}
        uint64_t result = 1;
        while (y != 0) {
            if (y % 2 != 0) {result *= x;}
            x *= x;
            y >>= 1;
        }
        return result;
    }
}