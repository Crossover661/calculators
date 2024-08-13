#include <iostream>
#include <vector>
#include <string>
#include <cstdint> // uint64_t
#include <cstdlib> // strtoull
#include <cerrno> // errno
#include <cctype> // isdigit
using std::cout, std::endl, std::vector, std::string, std::uint64_t, std::strtoull;

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

// Performs the Miller-Rabin primality test on n in base b. Returns true if n is a possible prime, and false otherwise.
bool mr(uint64_t n, uint64_t b) {
    if (n <= b + 1) {return true;}
    uint64_t n2 = n - 1;
    int s = 0;
    while (n2 % 2 == 0) {
        n2 >>= 1; 
        s++;
    }
    uint64_t x = modExp(b, n2, n);
    uint64_t y;
    for (int i=0; i<s; i++) {
        y = modExp(x, 2, n);
        if (y == 1 && x != 1 && x != (n-1)) {return false;}
        x = y;
    }
    return y == 1;
}

/* Calculates whether n is prime, using the Miller-Rabin test on various prime bases. For positive integers
less than 2^64, the test is deterministic when combining all prime bases from 2 through 37. */
bool isPrime(uint64_t n) {
    if (n % 2 == 0) {return n == 2;} // 2 is the only even prime number
    if (n < 2047) {return n != 1 && mr(n,2);}
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
    if (!isPositiveInteger(argv[1]) || !isPositiveInteger(argv[2])) {
        cout << "Lower and upper bounds must be positive integers." << endl;
        return 1;
    }

    uint64_t lower = 1, upper = 1, remainder = 0, modulus = 1;
    char* end;
    errno = 0;
    lower = strtoull(argv[1], &end, 10);
    char* end1;
    upper = strtoull(argv[2], &end1, 10);
    if (argc == 5) {
        char* end2;
        remainder = strtoull(argv[3], &end2, 10);
        char* end3;
        modulus = strtoull(argv[4], &end3, 10);
    }
    if (lower == 0) {lower = 1;}
    if (upper == 0) {upper = 1;}
    if (modulus == 0) {modulus = 1;}
    if (lower > upper) {
        cout << "Upper bound must be greater than or equal to lower bound." << endl;
        return 1;
    }
    if (errno == ERANGE) {
        cout << "All input values must be less than or equal to 2^64-1 = 18446744073709551615." << endl;
        return 1;
    }

    remainder %= modulus;
    lower += modAdd(remainder, (modulus - lower) % modulus, modulus);
    upper -= modAdd(upper % modulus, (modulus - remainder) % modulus, modulus);
    uint64_t numSteps = (upper - lower) / modulus;
    if (numSteps > 1000000) {
        cout << "Range of values cannot exceed 1000000." << endl;
        return 1;
    }
    uint64_t n = lower;
    vector<uint64_t> primes;
    for (uint64_t i = 0; i <= numSteps; i++) {
        if (isPrime(n)) {primes.push_back(n);}
        n += modulus;
    }

    cout << "Number of primes: " << primes.size() << endl;
    if (primes.size() <= 10000) {
        string curString = "";
        vector<string> primeStrings;
        for (uint64_t p : primes) {
            curString += std::to_string(p) + " ";
            if (curString.size() >= 100) {
                primeStrings.push_back(curString);
                curString = "";
            }
        }
        if (curString.size() != 0) {primeStrings.push_back(curString);}
        for (string line : primeStrings) {cout << line << endl;}
    }
    else {
        cout << "5 smallest primes: ";
        for (unsigned int i = 0; i < 5; i++) {cout << primes[i] << " ";}
        cout << endl;
        cout << "5 largest primes: ";
        for (unsigned int i = primes.size() - 1; i >= primes.size() - 5; i--) {cout << primes[i] << " ";}
        cout << endl;
    }
    return 0;
}