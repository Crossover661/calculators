#include <iostream>
#include <vector>
#include <string> // string, stoull
#include <cstdint> // uint64_t
#include <stdexcept>
#include "lib/modfuncs.h" // modAdd, modExp
using std::cout, std::endl, std::vector, std::string, std::uint64_t;

uint64_t toU64(string s) {
    if (s[0] == '-') {throw std::invalid_argument("Input must be a non-negative integer.");}
    try {
        uint64_t n = std::stoull(s);
        return n;
    }
    catch (const std::invalid_argument& e) {throw std::invalid_argument("Input must be a non-negative integer.");}
    catch (const std::out_of_range& e) {throw std::out_of_range("Input is too large. Maximum value allowed is 2^64-1 = 18446744073709551615.");}
}

// Performs the Miller-Rabin primality test on an odd number n in base b. Returns true if n is a possible prime, and false otherwise.
bool mr(uint64_t n, uint64_t b) {
    if (n <= b + 1) {return true;}
    uint64_t n2 = n - 1;
    int s = 0;
    while (n2 % 2 == 0) { 
        n2 >>= 1; // remove all factors of 2 from n2
        s++; // number of factors of 2 in n-1
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
        cout << "Syntax: ./listPrimes <lowerBound> <upperBound> [<remainder> <modulus>]" << endl;
        return 1;
    }
    try {
        // set values of lower and upper bounds, remainder, and modulus based on user input
        uint64_t lower, upper, remainder = 0, modulus = 1;
        lower = toU64(string(argv[1]));
        upper = toU64(string(argv[2]));
        if (argc == 5) {
            remainder = toU64(string(argv[3]));
            modulus = toU64(string(argv[4]));
        }
        if (modulus == 0) {modulus = 1;}
        if (lower > upper) {
            cout << "Upper bound must be greater than or equal to lower bound." << endl;
            return 1;
        }
        remainder %= modulus;
        lower += modAdd(remainder, modulus - lower, modulus);
        upper -= modAdd(upper, modulus - remainder, modulus);
        uint64_t numSteps = (upper - lower) / modulus;
        if (numSteps > 1000000) {
            cout << "Range of values cannot exceed " << (1000000 * modulus) << "." << endl;
            return 1;
        }

        // find primes and print them
        uint64_t n = lower;
        vector<uint64_t> primes;
        for (uint64_t i = 0; i <= numSteps; i++) {
            if (isPrime(n)) {primes.push_back(n);}
            n += modulus;
        }
        cout << "Number of primes: " << primes.size() << endl;
        if (primes.size() <= 10000) {
            string curString = "";
            for (uint64_t p : primes) {
                curString += std::to_string(p) + " ";
                if (curString.size() >= 100) { // limit line width to 100 to prevent numbers from being split across lines
                    cout << curString << endl;
                    curString = "";
                }
            }
            if (curString.size() != 0) {cout << curString << endl;}
        }
        else {
            cout << "5 smallest primes: ";
            for (unsigned int i = 0; i < 5; i++) {cout << primes[i] << " ";}
            cout << endl;
            cout << "5 largest primes: ";
            for (unsigned int i = primes.size() - 5; i < primes.size(); i++) {cout << primes[i] << " ";}
            cout << endl;
        }
        return 0;
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
        return 1;
    }
}