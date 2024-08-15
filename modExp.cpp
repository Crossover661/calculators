#include <iostream>
#include <cstdint> // uint64_t
#include <string> // string, stoull
#include <stdexcept> // exceptions
#include "lib/modfuncs.h" // modExp
using std::cout, std::endl, std::string, std::uint64_t;

uint64_t toU64(string s) {
    if (s[0] == '-') {throw std::invalid_argument("Input must be a non-negative integer.");}
    try {
        uint64_t n = std::stoull(s);
        return n;
    }
    catch (const std::invalid_argument& e) {throw std::invalid_argument("Input must be a non-negative integer.");}
    catch (const std::out_of_range& e) {throw std::out_of_range("Input is too large. Maximum value allowed is 2^64-1 = 18446744073709551615.");}
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Error: Incorrect input format." << endl;
        cout << "Input must be in the form: ./modExp <base> <exponent> <modulus>" << endl;
        return 1;
    }
    try {
        string baseStr = argv[1], expStr = argv[2], modStr = argv[3];
        uint64_t base = toU64(baseStr), exponent = toU64(expStr), modulus = toU64(modStr);
        if (modulus == 0) {
            cout << "Modulus must be greater than or equal to 1." << endl;
            return 1;
        }
        cout << modExp(base, exponent, modulus) << endl;
        return 0;
    }
    catch (const std::exception& e) {
        cout << e.what() << endl;
        return 1;
    }
}