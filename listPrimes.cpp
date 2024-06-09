#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

bool isPositiveInteger(char *str) {
    /* Detects whether all characters in the string are numeric. Strings corresponding to negative
    numbers, scientific notation, and integers written as decimals (such as "3.0") all return false. */
    for (int i = 0; str[i] != '\0'; i++) {if (!isdigit(str[i])) {return false;}}
    return true;
}

bool isPrime(unsigned int num) {
    // Returns "true" is num is prime and "false" if it is not.
    if (num <= 1) {return false;}
    if (num == 2 || num == 3) {return true;}
    if (num % 2 == 0 || num % 3 == 0) {return false;}
    unsigned int squareRoot = sqrt(num);
    for (unsigned int i = 5; i <= squareRoot; i+=6) {
        if ((num % i == 0) || (num % (i+2) == 0)) {return false;}
    }
    return true;
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
    errno = 0;
    unsigned int lowerBound = stoul(argv[1]);
    unsigned int upperBound = stoul(argv[2]);
    unsigned int remainder = 0, modulus = 1;
    if (argc == 5) {
        if (!isPositiveInteger(argv[3]) || !isPositiveInteger(argv[4])) {
            cout << "Remainder and modulus must be positive integers." << endl;
            return 1;
        }
        modulus = stoul(argv[4]);
        if (modulus == 0) {modulus = 1;}
        remainder = stoul(argv[3]);
    }
    if (lowerBound > upperBound) {
        cout << "Upper bound must be greater than or equal to lower bound." << endl;
        return 1;
    }
    if ((upperBound - lowerBound)/modulus > 100000) {
        if (argc == 3) {cout << "Range must be less than or equal to 100000" << endl;}
        else {cout << "Range must be less than or equal to 100000*modulus" << endl;}
        return 1;
    }
    vector<unsigned int> primes;
    if (upperBound == 4294967295) {upperBound = 4294967294;} // Upper bound of 4294967295 = 2^32-1 causes the program to freeze
    if (modulus != 1) {
        unsigned int adjustment = (remainder + modulus - (lowerBound % modulus)) % modulus;
        lowerBound += adjustment;
    }
    for (unsigned int i = lowerBound; i <= upperBound; i+=modulus) {
        if (isPrime(i)) {primes.push_back(i);}
    }
    cout << "Number of primes: " << primes.size() << endl;
    string curLine = "";
    vector<string> lines;
    for (unsigned int i : primes) {
        curLine += (to_string(i) + " ");
        if (curLine.size() >= 100) {
            lines.push_back(curLine);
            curLine = "";
        }
    }
    lines.push_back(curLine);
    for (string line : lines) {cout << line << endl;}
    return 0;
}