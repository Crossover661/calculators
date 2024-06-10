#include <iostream>
#include <vector> // vector
#include <cstdint> // uint64_t
#include <cerrno> // errno
#include <utility> // pair
using namespace std;

typedef pair<uint64_t, unsigned int> uiPair;

/* Detects whether all characters in the string are numeric. Strings corresponding to negative
numbers, scientific notation, and integers written as decimals (such as "3.0") all return false. */
bool isPositiveInteger(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {if (!isdigit(str[i])) {return false;}}
    return true;
}

// Returns the square root of n, rounded down.
uint64_t intSqrt(uint64_t n) {
    if (n <= 1) {return n;}
    uint64_t x = n;
    uint64_t y = (x - 1)/2 + 1;
    while (x > y) {
        x = y;
        y = (x + n/x)/2;
    }
    return x;
}

// Returns the lowest prime factor of n.
uint64_t lowestFactor(uint64_t n) {
    if (n % 2 == 0) {return 2;}
    if (n % 3 == 0) {return 3;}
    if (n % 5 == 0) {return 5;}
    uint64_t squareRoot = intSqrt(n);
    for (uint64_t i = 7; i <= squareRoot; i += 30) {
        if (n % i == 0) {return i;}
        if (n % (i+4) == 0) {return i+4;}
        if (n % (i+6) == 0) {return i+6;}
        if (n % (i+10) == 0) {return i+10;}
        if (n % (i+12) == 0) {return i+12;}
        if (n % (i+16) == 0) {return i+16;}
        if (n % (i+22) == 0) {return i+22;}
        if (n % (i+24) == 0) {return i+24;}
    }
    return n;
}

// Returns the full prime factorization of n, in exponential form. Ex: 2024 -> {{2,3},{11,1},{23,1}} -> 2^3 * 11 * 23
vector<uiPair> factorization(uint64_t n) {
    vector<uiPair> factors;
    while (n > 1) {
        uint64_t curFactor = lowestFactor(n);
        if (factors.empty() || factors.back().first != curFactor) {factors.push_back({curFactor, 1});}
        else {(factors.back().second)++;}
        n /= curFactor;
    }
    return factors;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cout << "Please provide 1 or more positive integers to factorize." << endl;
        return 1;
    }
    for (int i=1; i<argc; i++) {
        char *end;
        errno = 0;
        uint64_t n = strtoull(argv[i], &end, 10);
        if (!isPositiveInteger(argv[i])) {cout << "Input must be a positive integer.";}
        else if (errno == ERANGE) {cout << "Input is too large. Maximum value allowed is 2^64-1 = 18446744073709551615.";}
        else if (n <= 1) {cout << n << " is neither prime nor composite.";}
        else {
            vector<uiPair> factors = factorization(n);
            if (factors[0].first == n) {cout << n << " is prime.";}
            else {
                cout << n << " is composite. " << n << " = ";
                if (factors[0].second == 1) {cout << factors[0].first;}
                else {cout << factors[0].first << "^" << factors[0].second;}
                for (unsigned int j=1; j<factors.size(); j++) {
                    if (factors[j].second == 1) {cout << " * " << factors[j].first;}
                    else {cout << " * " << factors[j].first << "^" << factors[j].second;}
                }
            }
        }
        cout << endl;
    }
    return 0;
}