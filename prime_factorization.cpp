#include <iostream>
#include <cmath> // sqrt
#include <vector> // vectors
#include <algorithm> // count
typedef unsigned long long ull; // defines "ull" as shorthand for "unsigned long long"
using namespace std;
bool isPositiveInteger(char str[])
{
    /* Detects whether all characters in the string are numeric. Strings corresponding to negative numbers, scientific notation, and integers written as decimals (such as "3.0") all return false. */
    for (int i=0; str[i]!='\0'; i++) {if (!isdigit(str[i])) {return false;}}
    return true;
}
ull lowestFactor(ull num)
{
    // returns lowest factor of a number
    if (num % 2 == 0) {return 2;}
    if (num % 3 == 0) {return 3;}
    if (num % 5 == 0) {return 5;}
    ull squareRoot = sqrt((long double)num);
    for (ull i=7; i<=squareRoot; i+=30)
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
void exponentialForm(vector<ull> factorization, vector<ull>* uniqueFactors, vector<int>* exponents)
{
    while(factorization.size() > 0)
    {
        // converts factorization to exponential form
        int exponent;
        (*uniqueFactors).push_back(factorization.front());
        exponent = count(factorization.begin(), factorization.end(), factorization.front());
        (*exponents).push_back(exponent);
        factorization.erase(factorization.begin(), factorization.begin() + exponent);
    }
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
int main(int argc, char *argv[])
{
    if (argc != 2 || !isPositiveInteger(argv[1])) 
    {
        cerr << "Input must be a positive integer." << endl;
        return 1;
    }
    char *end;
    errno = 0;
    ull num = strtoull(argv[1], &end, 10);
    if (errno == ERANGE)
    {
        // if number is larger than the maximum value of an ull, 2^64-1
        cerr << "Input is too large. Maximum input allowed is 2^64-1 = 18446744073709551615.";
        return 1;
    }
    if (num <= 1) {cout << num << " is neither prime nor composite." << endl;}
    else if (lowestFactor(num) == num) {cout << num << " is prime." << endl;}
    else
    {
        vector<ull> uniqueFactors; // unique prime factors of num
        vector<int> exponents; // exponents in the prime factorization of num
        cout << num << " is composite. ";
        exponentialForm(factors(num), &uniqueFactors, &exponents);
        cout << num << " = ";
        if (exponents.front() == 1) {cout << uniqueFactors.front();}
        else {cout << uniqueFactors.front() << "^" << exponents.front();}
        for (int i=1; i<uniqueFactors.size(); i++)
        {
            if (exponents.at(i) == 1) {cout << " * " << uniqueFactors.at(i);}
            else {cout << " * " << uniqueFactors.at(i) << "^" << exponents.at(i);}
        }
        cout << endl;
    }
    return 0;
}
