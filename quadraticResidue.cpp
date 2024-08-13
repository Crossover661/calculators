#include <iostream>
#include <cstdint> // uint64_t
#include <cstdlib> // strtoull
#include <cerrno> // errno
#include <cctype> // isdigit
#include <utility> // pair
#include <vector> // vector
#include <string> // string
using std::cout, std::endl, std::vector, std::uint64_t;
typedef std::pair<uint64_t, uint64_t> uuPair;

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

// Raises base to the power of exp.
uint64_t pow(uint64_t base, uint64_t exp) {
    if (base == 2) {return uint64_t(1) << exp;}
    uint64_t result = 1;
    while (exp != 0) {
        if (exp % 2 != 0) {result *= base;}
        base *= base;
        exp >>= 1;
    }
    return result;
}

// Calculates the Legendre symbol of n modulo a given odd prime modulus p. If this is equal to 0 or 1, n is a quadratic residue modulo p. If it is -1, n is a quadratic nonresidue modulo p.
int legendre(uint64_t n, uint64_t p) {
    uint64_t legendreSymbol = modExp(n, (p-1)/2, p);
    if (legendreSymbol <= 1) {return (int)legendreSymbol;}
    else {return -1;}
}

// Calculates whether a non-negative integer n is a quadratic residue modulo a prime power p^e. Returns true if n is a residue and false otherwise.
bool isResidueP(uint64_t n, uint64_t p, uint64_t e) {
    n %= pow(p, e); // clamp n to be in the range [0, p^e)
    while (n % (p * p) == 0 && e >= 2) { // factor out squares, ex: 50 mod 125 --> 2 mod 5
        n /= (p * p);
        e -= 2;
    }
    if (n == 0 || n == 1 || p == 1 || e == 0) {return true;} // if n == 1 or p^e == 1
    if (p == 2) {
        if (e == 1) {return true;}
        if (e == 2) {return n % 4 <= 1;}
        return n == 0 || n % 8 == 1; // of the form 4^k*(8*n+1) for integers k and n
    }
    if (n % p == 0) {return false;} // if n divisible by p and e == 1, or e == 2 and n divisible by p but not p^2
    return legendre(n, p) != -1; // if n is coprime to p and p is odd, n is a residue mod p iff legendre(n, p) != -1
}

// Returns the lowest prime factor of n. Helper function for factorization.
uint64_t lowestFactor(uint64_t n) {
    if (n % 2 == 0) {return 2;}
    if (n % 3 == 0) {return 3;}
    uint64_t x = n, y = (x - 1)/2 + 1;
    while (x > y) {
        x = y;
        y = (x + n/x)/2; // at the end of the loop, x = floor(sqrt(n))
    }
    for (uint64_t i = 5; i <= x; i += 6) {
        if (n % i == 0) {return i;}
        if (n % (i+2) == 0) {return i+2;}
    }
    return n;
}

// Returns the full prime factorization of n, in exponential form. Ex: 2024 -> {{2,3},{11,1},{23,1}} -> 2^3 * 11 * 23. 
// This step is necessary to find quadratic residues - a is a residue mod b iff a is a residue mod every prime power that divides b. 
vector<uuPair> factorization(uint64_t n) {
    vector<uuPair> factors;
    while (n > 1) {
        uint64_t curFactor = lowestFactor(n);
        if (factors.empty() || factors.back().first != curFactor) {factors.push_back({curFactor, 1});}
        else {(factors.back().second)++;}
        n /= curFactor;
    }
    return factors;
}

// Calculates whether n is a quadratic residue modulo a number given the modulus's factorization.
bool isResidue(uint64_t n, vector<uuPair>& factors) {
    for (uuPair f : factors) {if (!isResidueP(n, f.first, f.second)) {return false;}}
    return true;
}

// Returns a vector showing all quadratic residues modulo m (given m's prime factorization).
vector<uint64_t> residues(uint64_t m, vector<uuPair>& factors) {
    vector<uint64_t> residues;
    for (uint64_t i = 0; i < m; i++) {
        if (isResidue(i, factors)) {residues.push_back(i);}
    }
    return residues;
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        if (!isPositiveInteger(argv[1])) {
            cout << "Modulus must be a positive integer." << endl;
            return 1;
        }
        char* end;
        errno = 0;
        uint64_t modulus = std::strtoull(argv[1], &end, 10);
        if (errno == ERANGE || modulus <= 1 || modulus >= 100000) {
            cout << "Modulus must be between 2 and 99999" << endl;
            return 1;
        }
        vector<uuPair> factors = factorization(modulus);
        vector<uint64_t> res = residues(modulus, factors);
        cout << "Number of residues: " << res.size() << endl;
        std::string curString = "";
        for (uint64_t r : res) {
            curString += std::to_string(r) + " ";
            if (curString.size() >= 100) {
                cout << curString << endl;
                curString = "";
            }
        }
        if (curString.size() != 0) {cout << curString << endl;}
        return 0;
    }
    else if (argc == 3) {
        if (!isPositiveInteger(argv[1]) || !isPositiveInteger(argv[2])) {
            cout << "Remainder and modulus must be positive integers." << endl;
            return 1;
        }
        char* end;
        errno = 0;
        uint64_t remainder = std::strtoull(argv[1], &end, 10);
        char* end1;
        uint64_t modulus = std::strtoull(argv[2], &end1, 10);
        if (modulus == 1) {
            cout << "Modulus must be greater than 1." << endl;
            return 1;
        }
        vector<uuPair> factors = factorization(modulus);
        if (isResidue(remainder, factors)) {cout << remainder << " is a quadratic residue modulo " << modulus << "." << endl;}
        else {cout << remainder << " is NOT a quadratic residue modulo " << modulus << "." << endl;}
        return 0;
    }
    else {
        cout << "Input must be of one of the following formats:" << endl;
        cout << "./quadraticResidue <modulus>" << endl;
        cout << "./quadraticResidue <remainder> <modulus>" << endl;
        return 1;
    }
}