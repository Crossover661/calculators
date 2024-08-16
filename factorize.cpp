#include <iostream>
#include <vector>
#include <utility> // pair
#include <cstdint> // uint64_t
#include <string> // string, stoull
#include <stdexcept> // exceptions
using std::cout, std::endl, std::vector, std::uint64_t;
typedef std::pair<uint64_t, unsigned int> uiPair;

// Returns the lowest prime factor of n.
uint64_t lowestFactor(uint64_t n) {
    if (n % 2 == 0) {return 2;}
    if (n % 3 == 0) {return 3;}
    if (n % 5 == 0) {return 5;}
    uint64_t x = n, y = (x - 1)/2 + 1;
    while (x > y) { // at end of loop, x = floor(sqrt(n))
        x = y;
        y = (x + n/x)/2;
    }
    for (uint64_t i = 7; i <= x; i += 30) {
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
        cout << "Syntax: ./factorize <numbers to factorize>" << endl;
        return 1;
    }
    for (int i=1; i<argc; i++) {
        std::string str = argv[i];
        try {
            uint64_t n = std::stoull(str);
            if (str[0] == '-') {cout << "Input must be a positive integer.";}
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
        }
        catch (const std::invalid_argument& e) {cout << "Input must be a positive integer.";}
        catch (const std::out_of_range& e) {cout << "Input is too large. Maximum input allowed is 2^64-1 = 18446744073709551615.";}
        cout << endl;
    }
    return 0;
}