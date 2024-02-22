#include <iostream>
#include <cmath> // sqrt
#include <vector> // vectors
#include <cstdint> // uint64_t
using namespace std;

bool isPositiveInteger(char *str) {
    /* Detects whether all characters in the string are numeric. Strings corresponding to negative
    numbers, scientific notation, and integers written as decimals (such as "3.0") all return false. */
    for (int i = 0; str[i] != '\0'; i++) {if (!isdigit(str[i])) {return false;}}
    return true;
}

uint64_t lowestFactor(uint64_t num) {
    // returns lowest factor of a number
    if (num % 2 == 0) {return 2;}
    if (num % 3 == 0) {return 3;}
    if (num % 5 == 0) {return 5;}
    uint64_t squareRoot = sqrt((long double)num);
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

vector<uint64_t> factors(uint64_t num) {
    // Returns all prime factors of a number, as a vector. Ex: 2024 = 2*2*2*11*23 --> {2,2,2,11,23}
    vector<uint64_t> listFactors;
    uint64_t factor;
    while (num > 1) {
        factor = lowestFactor(num);
        listFactors.push_back(factor);
        num /= factor;
    }
    return listFactors;
}

void exponentialForm(vector<uint64_t>& factorization, vector<uint64_t>& uniqueFactors, vector<int>& exponents) {
    /* Converts the value returned in factors() to exponential form, with one vector representing the unique factors
    and another vector representing the exponents. The uniqueFactors and exponents variables are passed by reference
    and are filled with appropriate values. Ex: {2,2,2,11,23} --> uniqueFactors = {2,11,23}, exponents = {3,1,1} */
    int exponent = 0;
    uint64_t curFactor = factorization[0];
    for (int i=0; i<factorization.size(); i++) {
        if (factorization[i] == curFactor) {exponent++;}
        else {
            uniqueFactors.push_back(curFactor);
            exponents.push_back(exponent);
            curFactor = factorization[i];
            exponent = 1;
        }
    }
    uniqueFactors.push_back(curFactor);
    exponents.push_back(exponent);
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "Please provide 1 or more positive integers to factorize.";
        return 1;
    }
    for (int i=1; i<argc; i++) {
        char *end;
        errno = 0;
        uint64_t num = strtoull(argv[i], &end, 10);
        if (errno == ERANGE) {
            // Return error if number is larger than the maximum value of uint64_t, 2^64-1.
            cerr << "Input is too large. Maximum input allowed is 2^64-1 = 18446744073709551615.";
            return 1;
        }
        if (num <= 1) {cout << num << " is neither prime nor composite.";}
        else if (lowestFactor(num) == num) {cout << num << " is prime.";}
        else {
            cout << num << " is composite. ";

            // Print prime factorization of num.
            vector<uint64_t> factorization = factors(num);
            vector<uint64_t> uniqueFactors; // unique prime factors of num
            vector<int> exponents; // exponents in the prime factorization of num
            exponentialForm(factorization, uniqueFactors, exponents);
            cout << num << " = ";
            if (exponents[0] == 1) {cout << uniqueFactors[0];}
            else {cout << uniqueFactors[0] << "^" << exponents[0];}
            for (int i = 1; i < uniqueFactors.size(); i++) {
                if (exponents[i] == 1) {cout << " * " << uniqueFactors[i];}
                else {cout << " * " << uniqueFactors[i] << "^" << exponents[i];}
            }
        }
        cout << endl;
    }
    return 0;
}
