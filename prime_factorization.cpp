#include <iostream>
#include <cmath> // sqrt
#include <vector> // vectors
#include <cstdint> // uint64_t
#include <string> // string, stoull
using namespace std;

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
    // returns all prime factors of a number, as a vector
    vector<uint64_t> listFactors;
    uint64_t factor;
    while (num > 1) {
        factor = lowestFactor(num);
        listFactors.push_back(factor);
        num /= factor;
    }
    return listFactors;
}
vector<vector<uint64_t>> exponentialForm(vector<uint64_t>& factorization) {
    // Converts factorization into an exponential form with two vectors, representing the unique factors and the exponents.
    // Note: factorization vector is already sorted least-to-greatest.
    int exponent = 0;
    vector<uint64_t> uniqueFactors;
    vector<uint64_t> exponents;
    uint64_t curFactor = factorization[0];
    for (int i=0; i<factorization.size(); i++) {
        if (factorization[i] == curFactor) {
            exponent++;
        }
        else {
            uniqueFactors.push_back(curFactor);
            exponents.push_back(exponent);
            curFactor = factorization[i];
            exponent = 1;
        }
    }
    uniqueFactors.push_back(curFactor);
    exponents.push_back(exponent);

    return {uniqueFactors, exponents};
}
int main() {
    string number;
    cin >> number;
    uint64_t num;
    bool rangeError = false;

    // handle range errors
    try {num = stoull(number, nullptr, 10);}
    catch (...) {rangeError = true;}
    if (number[0] == '-') {rangeError = true;}
    if (rangeError) {
        cout << "Input must be an number between 0 and 18446744073709551615, inclusive." << endl;
        return 1;
    }
    
    // If there are no range errors, calculate the prime factorization of the given integer.
    if (num <= 1) {cout << num << " is neither prime nor composite.";}
    else if (lowestFactor(num) == num) {cout << num << " is a prime number.";}
    else {
        cout << num << " is a composite number." << endl;
        cout << num << " = ";
        vector<uint64_t> primeFactors = factors(num);
        vector<vector<uint64_t>> factorized = exponentialForm(primeFactors);
        vector<uint64_t> uniqueFactors = factorized[0];
        vector<uint64_t> exponents = factorized[1];
        for (int i=0; i<uniqueFactors.size()-1; i++) {
            // print exponential form of prime factorization, up until last factor-exponent pair
            if (exponents[i] == 1) {cout << uniqueFactors[i];}
            else {cout << uniqueFactors[i] << "^" << exponents[i];}
            cout << " * ";
        }
        // print last factor-exponent pair
        if (exponents.back() == 1) {cout << uniqueFactors.back();}
        else {cout << uniqueFactors.back() << "^" << exponents.back();}
    }

    cout << endl;
    return 0;
}
