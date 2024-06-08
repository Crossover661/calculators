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
    if (argc != 3) {
        cout << "Please provide a lower bound and an upper bound." << endl;
        return 1;
    }
    if (!isPositiveInteger(argv[1]) || !isPositiveInteger(argv[2])) {
        cout << "Lower and upper bounds must be positive integers." << endl;
        return 1;
    }
    errno = 0;
    unsigned int lowerBound = stoul(argv[1]);
    unsigned int upperBound = stoul(argv[2]);
    if (lowerBound > upperBound) {
        cout << "Upper bound must be greater than or equal to lower bound" << endl;
        return 1;
    }
    if (upperBound - lowerBound > 100000) {
        cout << "Range must be less than or equal to 100000" << endl;
    }
    vector<unsigned int> primes;
    if (lowerBound <= 2) {primes.push_back(2);}
    if (lowerBound % 2 == 0) {lowerBound++;}
    if (upperBound == 4294967295) {upperBound = 4294967294;} // Upper bound of 4294967295 = 2^32-1 causes the program to freeze
    for (unsigned int i = lowerBound; i <= upperBound; i+=2) {
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