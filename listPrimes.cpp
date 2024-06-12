#include <iostream>
#include <vector>
#include <string>
#include <cstdint> // uint64_t
#include <cstdlib> // strtoull
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
    for (int i = 63; i >= 0; i--) {
        uint64_t mask = uint64_t(1) << i;
        bool bit = (y & mask) != 0;
        if (bit) {result = modAdd(modAdd(result, result, modulus), x, modulus);}
        else {result = modAdd(result, result, modulus);}
    }
    return result;
}

// Performs modular exponentiation. Ex: modExp(2,91,1000) = 2^91 mod 1000 = 448
uint64_t modExp(uint64_t base, uint64_t exp, uint64_t modulus) {
    if (modulus <= 1) {return 0;}
    if (base == 1 || exp == 0) {return 1;}
    uint64_t result = 1;
    for (int i = 63; i >= 0; i--) {
        uint64_t mask = uint64_t(1) << i;
        bool bit = (exp & mask) != 0;
        if (bit) {result = modMul(modMul(result, result, modulus), base, modulus);}
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

/* Calculates whether n is prime, using the Miller-Rabin test on various prime bases. For positive integers
less than 2^64, the test is deterministic when combining all prime bases from 2 through 37. */
bool isPrime(uint64_t n) {
    if (n <= 5) {return (n == 2 || n == 3 || n == 5);}
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) {return false;}
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
    if (!isPositiveInteger(argv[1]) || !isPositiveInteger(argv[2])) {
        cout << "Lower and upper bounds must be positive integers." << endl;
        return 1;
    }

    uint64_t lowerBound = 0, upperBound = 0, remainder = 0, modulus = 1;
    char* end;
    errno = 0;
    lowerBound = strtoull(argv[1], &end, 10);
    char* end1;
    upperBound = strtoull(argv[2], &end1, 10);
    if (errno == ERANGE) {
        cout << "Lower and upper bounds must be at most 2^64-1 = 18446744073709551615." << endl;
        return 1;
    }
    if (upperBound < lowerBound) {
        cout << "Upper bound must be greater than or equal to lower bound." << endl;
        return 1;
    }
    if (argc == 5) {
        if (!isPositiveInteger(argv[1]) || !isPositiveInteger(argv[2])) {
            cout << "Remainder and modulus must be non-negative integers." << endl;
            return 1;
        }
        char* end2;
        remainder = strtoull(argv[3], &end2, 10);
        char* end3;
        modulus = strtoull(argv[4], &end3, 10);
        if (modulus == 0) {
            cout << "Modulus must be greater than or equal to 1." << endl;
            return 1;
        }
        remainder %= modulus;
    }

    if ((upperBound - lowerBound) / modulus > 1000000) {
        if (argc == 3) {cout << "Range of numbers must be at most 1000000." << endl;}
        else {cout << "Range of numbers satisfying modular congruence must be at most 1000000." << endl;}
        return 1;
    }

    /* If the upper bound is exactly equal to 2^64-1, the for loop that calculates the primes enters an infinite loop. 
    Thus, the upper bound is capped at 2^64-2. This does not affect the program's output as 2^64-1 is a composite number. */  
    if (upperBound == uint64_t(0xFFFFFFFFFFFFFFFF)) {upperBound = 0xFFFFFFFFFFFFFFFE;}
    vector<uint64_t> primes;
    for (uint64_t i = lowerBound; i <= upperBound; i++) {
        if (i % modulus == remainder && isPrime(i)) {primes.push_back(i);}
    }
    cout << "Number of primes: " << primes.size() << endl;
    if (primes.size() <= 10000) {
        string curLine = "";
        for (uint64_t n : primes) {
            curLine += (std::to_string(n) + " ");
            if (curLine.size() >= 100) {
                cout << curLine << endl;
                curLine = "";
            }
        }
        if (curLine.size() >= 1) {cout << curLine << endl;}
    }
    else {
        cout << "5 smallest primes: ";
        for (unsigned int i=0; i<5; i++) {cout << primes[i] << " ";}
        cout << endl;
        cout << "5 largest primes: ";
        for (unsigned int i=primes.size()-5; i<primes.size(); i++) {cout << primes[i] << " ";}
        cout << endl;
    }
    return 0;
}