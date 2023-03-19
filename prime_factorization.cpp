#include <iostream>
#include <cmath> // sqrt
#include <vector> // vectors
#include <algorithm> // count
typedef unsigned long long ull; // defines "ull" as shorthand for "unsigned long long"
using namespace std;
bool isPositiveInteger(char str[])
{
    /* Detects whether all characters in the string are numeric. Strings corresponding to negative
    numbers, scientific notation, and integers written as decimals (such as "3.0") all return false. */
    for (int i = 0; str[i] != '\0'; i++) {if (!isdigit(str[i])) {return false;}}
    return true;
}
ull lowestFactor(ull num)
{
    // returns lowest factor of a number
    if (num % 2 == 0) {return 2;}
    if (num % 3 == 0) {return 3;}
    if (num % 5 == 0) {return 5;}
    ull squareRoot = sqrt((long double)num);
    for (ull i = 7; i <= squareRoot; i += 30)
    {
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
vector<ull> factors(ull num)
{
    // returns all prime factors of a number, as a vector
    vector<ull> listFactors;
    ull factor;
    while (num > 1)
    {
        factor = lowestFactor(num);
        listFactors.push_back(factor);
        num /= factor;
    }
    return listFactors;
}
void exponentialForm(vector<ull>& factorization, vector<ull>& uniqueFactors, vector<int>& exponents)
{
    // Converts factorization into an exponential form with two vectors, representing the unique factors and the exponents.
    // Note: factorization vector is already sorted least-to-greatest.
    int exponent = 0;
    ull curFactor = factorization[0];
    for (int i=0; i<factorization.size(); i++)
    {
        if (factorization[i] == curFactor)
        {
            exponent++;
        }
        else
        {
            uniqueFactors.push_back(curFactor);
            exponents.push_back(exponent);
            curFactor = factorization[i];
            exponent = 1;
        }
    }
    uniqueFactors.push_back(curFactor);
    exponents.push_back(exponent);
}
int main(int argc, char *argv[])
{
    if (argc != 2 || !isPositiveInteger(argv[1])) 
    {
        cerr << "Input must be a positive integer.";
        return 1;
    }
    char *end;
    errno = 0;
    ull num = strtoull(argv[1], &end, 10);
    if (errno == ERANGE)
    {
        // if number is larger than the maximum value of an unsigned long long, 2^64-1
        cerr << "Input is too large. Maximum input allowed is 2^64-1 = 18446744073709551615.";
        return 1;
    }
    if (num <= 1) {cout << num << " is neither prime nor composite.";}
    else if (lowestFactor(num) == num) {cout << num << " is prime.";}
    else
    {
        vector<ull> factorization = factors(num);
        vector<ull> uniqueFactors; // unique prime factors of num
        vector<int> exponents; // exponents in the prime factorization of num
        cout << num << " is composite. ";
        exponentialForm(factorization, uniqueFactors, exponents);
        cout << num << " = ";
        if (exponents[0] == 1) {cout << uniqueFactors[0];}
        else {cout << uniqueFactors[0] << "^" << exponents[0];}
        for (int i = 1; i < uniqueFactors.size(); i++)
        {
            if (exponents[i] == 1) {cout << " * " << uniqueFactors[i];}
            else {cout << " * " << uniqueFactors[i] << "^" << exponents[i];}
        }
    }
    cout << endl;
    return 0;
}