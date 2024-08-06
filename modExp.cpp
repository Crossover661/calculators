#include <iostream>
#include <cstdint> // uint64_t
using std::cout, std::endl, std::uint64_t;

bool isPositiveInteger(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {if (!std::isdigit(str[i])) {return false;}}
    return true;
}

// Implements modular addition without overflow.
uint64_t modAdd(uint64_t x, uint64_t y, uint64_t modulus) {
    if (y < modulus - x) {return x + y;}
    else {return y - (modulus - x);} // ex. (65 + 57) % 100 = 57 - (100 - 65) = 57 - 35 = 22
}

// Implements modular multiplication by doubling to prevent overflow. Helper function for modExp().
uint64_t modMul(uint64_t x, uint64_t y, uint64_t modulus) {
    if (x <= 0xFFFFFFFF && y <= 0xFFFFFFFF) {return (x * y) % modulus;}
    uint64_t result = 0;
    for (int i = 63; i >= 0; i--) {
        uint64_t mask = uint64_t(1) << i;
        bool bit = (y & mask) != 0;
        if (bit) {result = modAdd(modAdd(result, result, modulus), x, modulus);}
        else {result = modAdd(result, result, modulus);}
    }
    return result;
}

// Performs modular exponentiation by squaring. Ex: modExp(2,91,1000) = 2^91 mod 1000 = 448
uint64_t modExp(uint64_t base, uint64_t exp, uint64_t modulus) {
    if (modulus <= 1) {return 0;}
    if (base == 1 || exp == 0) {return 1;}
    uint64_t result = 1;
    for (int i = 63; i >= 0; i--) {
        uint64_t mask = uint64_t(1) << i;
        bool bit = (exp & mask) != 0; // the binary digit at the ith position of the exponent
        if (bit) {result = modMul(modMul(result, result, modulus), base, modulus);}
        else {result = modMul(result, result, modulus);}
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Error: Incorrect input format." << endl;
        cout << "Input must be in the form: ./modExp <base> <exponent> <modulus>" << endl;
        return 1;
    }
    else if (!isPositiveInteger(argv[1]) || !isPositiveInteger(argv[2]) || !isPositiveInteger(argv[3])) {
        cout << "All inputs must be positive integers." << endl;
        return 1;
    }
    else {
        char* endBase;
        errno = 0;
        uint64_t base = std::strtoull(argv[1], &endBase, 10);
        char* endExp;
        uint64_t exponent = std::strtoull(argv[2], &endExp, 10);
        char* endModulus;
        uint64_t modulus = std::strtoull(argv[3], &endModulus, 10);
        if (errno == ERANGE) {
            cout << "Base, exponent, and modulus must be less than or equal to 2^64-1 = 18446744073709551615.";
            return 1;
        }
        cout << modExp(base, exponent, modulus) << endl;
        return 0;
    }
}