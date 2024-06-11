#include <iostream>
#include <vector>
#include <cstdint> // uint64_t
#include <cstdlib> // strtoull
using std::cout, std::endl, std::vector, std::uint64_t;

bool isPositiveInteger(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {if (!isdigit(str[i])) {return false;}}
    return true;
}

/* Modular "multiplication by doubling", in the same manner as "exponentiation by squaring".
This prevents overflow with inputs above 2^32, however may still overflow if one input
is greater than or equal to 2^63. */
uint64_t modMul(uint64_t x, uint64_t y, uint64_t modulus) {
    if (x <= uint64_t(0xFFFFFFFF) && y <= uint64_t(0xFFFFFFFF)) {return (x * y) % modulus;}
    uint64_t result = 0;
    x %= modulus;
    while (y > 0) {
        if (y % 2 != 0) {result = (result + x) % modulus;}
        x = (x * 2) % modulus;
        y /= 2;
    }
    return result;
}

// Modular multiplication of three integers.
uint64_t modMul(uint64_t x, uint64_t y, uint64_t z, uint64_t modulus) {
    return modMul(modMul(x, y, modulus), z, modulus);
}

// Performs modular exponentiation. Ex: modExp(2,91,1000) = 2^91 mod 1000 = 448
uint64_t modExp(uint64_t base, uint64_t exp, uint64_t modulus) {
    if (modulus <= 1) {return 0;}
    if (base == 1 || exp == 0) {return 1;}
    uint64_t result = 1;
    for (int i = 63; i >= 0; i--) {
        uint64_t mask = uint64_t(1) << i;
        bool bit = (exp & mask) != 0;
        if (bit) {result = modMul(result, result, base, modulus);}
        else {result = modMul(result, result, modulus);}
    }
    return result;
}

// Performs the Miller-Rabin primality test on n in base b. Returns true if n is a possible prime, and false otherwise.
bool mr(uint64_t n, uint64_t b) {
    if (n <= b + 1) {return true;}
    uint64_t n2 = n - 1;
    int s = 0;
    while (n2 % 2 == 0) {n2 /= 2; s++;}
    uint64_t x = modExp(b, n2, n);
    uint64_t y;
    for (int i=0; i<s; i++) {
        y = modExp(x, 2, n);
        if (y == 1 && x != 1 && x != (n-1)) {return false;}
        x = y;
    }
    return y == 1;
}

// Calculates whether n is prime, using the Miller-Rabin test on various prime bases
bool isPrime(uint64_t n) {
    if (n <= 3) {return n >= 2;}
    if (n % 2 == 0 || n % 3 == 0) {return false;}
    if (n < 2047) {return mr(n,2);}
    if (n < 1373653) {return mr(n,2) && mr(n,3);}
    if (n < 25326001) {return mr(n,2) && mr(n,3) && mr(n,5);}
    return (mr(n,2) && mr(n,3) && mr(n,5) && mr(n,7) && mr(n,11) && mr(n,13) && mr(n,17)
    && mr(n,19) && mr(n,23) && mr(n,29) && mr(n,31) && mr(n,37));
}

int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 5) {
        cout << "Input must be of one of the following formats:" << endl;
        cout << "./listPrimes <lowerBound> <upperBound>" << endl;
        cout << "./listPrimes <lowerBound> <upperBound> <remainder> <modulus>" << endl;
        return 1;
    }
    uint64_t lowerBound = 0, upperBound = 0, remainder = 0, modulus = 1;
    char* end;
    lowerBound = strtoull(argv[1], &end, 10);
    char* end1;
    upperBound = strtoull(argv[2], &end1, 10);
    if (argc == 5) {
        char* end2;
        remainder = strtoull(argv[3], &end2, 10);
        char* end3;
        modulus = strtoull(argv[4], &end3, 10);
        if (modulus == 0) {modulus = 1;}
        remainder %= modulus;
    }
    // TODO: Complete function
    cout << lowerBound << " " << upperBound << endl;
    return 0;
}