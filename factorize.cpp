#include <iostream>
#include <vector> // vector
#include <cstdint> // uint64_t
#include <utility> // pair
using namespace std;

typedef pair<uint64_t, unsigned int> uiPair;

bool isPositiveInteger(char *str) {
    /* Detects whether all characters in the string are numeric. Strings corresponding to negative
    numbers, scientific notation, and integers written as decimals (such as "3.0") all return false. */
    for (int i = 0; str[i] != '\0'; i++) {if (!isdigit(str[i])) {return false;}}
    return true;
}

uint64_t intSqrt(uint64_t num) {
    // Returns the square root of num, rounded down.
    if (num <= 1) {return num;}
    uint64_t x = num;
    uint64_t y = (x - 1)/2 + 1;
    while (x > y) {
        x = y;
        y = (x + num/x)/2;
    }
    return x;
}

uint64_t lowestFactor(uint64_t num) {
    // Calculates the lowest prime factor of num.
    if (num % 2 == 0) {return 2;}
    if (num % 3 == 0) {return 3;}
    if (num % 5 == 0) {return 5;}
    uint64_t squareRoot = intSqrt(num);
    for (uint64_t i = 7; i <= squareRoot; i += 30) {
        // eliminates multiples of 2, 3, and 5
        if (num % i == 0) {return i;}
        if (num % (i+4) == 0) {return i+4;}
        if (num % (i+6) == 0) {return i+6;}
        if (num % (i+10) == 0) {return i+10;}
        if (num % (i+12) == 0) {return i+12;}
        if (num % (i+16) == 0) {return i+16;}
        if (num % (i+22) == 0) {return i+22;}
        if (num % (i+24) == 0) {return i+24;}
    }
    return num;
}

vector<uiPair> factorization(uint64_t num) {
    // Returns the full prime factorization of num, in exponential form. Ex: 2024 -> {{2,3},{11,1},{23,1}} -> 2^3 * 11 * 23
    vector<uiPair> factors;
    while (num > 1) {
        uint64_t curFactor = lowestFactor(num);
        if (factors.empty() || factors.back().first != curFactor) {factors.push_back({curFactor, 1});}
        else {(factors.back().second)++;}
        num /= curFactor;
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
        uint64_t num = strtoull(argv[i], &end, 10);
        if (!isPositiveInteger(argv[i])) {cout << "Input must be a positive integer.";}
        else if (errno == ERANGE) {cout << "Input is too large. Maximum value allowed is 2^64-1 = 18446744073709551615.";}
        else if (num <= 1) {cout << num << " is neither prime nor composite.";}
        else if (lowestFactor(num) == num) {cout << num << " is prime.";}
        else {
            cout << num << " is composite. " << num << " = ";
            vector<uiPair> factors = factorization(num);
            if (factors[0].second == 1) {cout << factors[0].first;}
            else {cout << factors[0].first << "^" << factors[0].second;}
            for (unsigned int j=1; j<factors.size(); j++) {
                if (factors[j].second == 1) {cout << " * " << factors[j].first;}
                else {cout << " * " << factors[j].first << "^" << factors[j].second;}
            }
        }
        cout << endl;
    }
    return 0;
}