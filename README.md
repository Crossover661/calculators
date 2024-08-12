A repository for calculators in C++.

For the factorize.cpp calculator:
* Type `./factorize <numbers_to_factorize>` in a command prompt to find the prime factorization(s) of the given number(s).
  * `./factorize 5` prints `5 is prime.`
  * `./factorize 2024` prints `2024 is composite. 2024 = 2^3 * 11 * 23`
  * `./factorize 2 22 2024 11 23` prints the prime factorizations of 2, 22, 2024, 11, and 23, each on its own line.
  * This calculator handles integers between 2 and 2^64-1 = 18446744073709551615, inclusive. 0, 1, and negative numbers are neither prime nor composite.
* The worst-case time complexity of the calculator is O(√(n)) where n is the number to be factored, or O(10^(d/2)) where d is the number of digits in the number's decimal representation.
  * The numbers that take the longest time to factorize are prime numbers close to the 64-bit limit (such as `18446744073709551557`) and semiprimes with factors close to 2^32 (such as `18446743979220271189` = `4294967279 * 4294967291`, the product of the 2 largest 32-bit primes). Factorizing such numbers may take several seconds.

For the listPrimes.cpp calculator:
* Type `./listPrimes <lowerBound> <upperBound>` to list all prime numbers between lowerBound and upperBound, inclusive, along with the number of primes between said values.
* lowerBound and upperBound must be positive integers at most 2^64-1 = 18446744073709551615, and upperBound must be greater than or equal to lowerBound.
* Example: `./listPrimes 100 200` prints:
```
Number of primes: 21
101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199
```
* One can also restrict the list of primes to include only numbers that are congruent to m modulo n, for some positive integers m and n. For example, `./listPrimes 100 999 9 10` prints 3-digit prime numbers that end in 9 in base 10.
* If the modular restriction is not set, the range of values must be less than or equal to 1000000. If the modular restriction is set, the range of values satisfying the modular congruence must be less than or equal to 1000000.
* If the number of primes is greater than 10000, then the number of primes is listed, followed by the 5 smallest and largest primes.
  * Example: `./listPrimes 1 999999 1 8` prints
  ```
  Number of primes: 19552
  5 smallest primes: 17 41 73 89 97 
  5 largest primes: 999721 999769 999809 999953 999961 
  ```

For the modExp.cpp calculator:
* This calculator performs modular exponentiation. Given three positive integers a, b, c, it calculates the remainder when a^b is divided by c.
* Syntax is `./modExp <base> <exponent> <modulus>`.
* Example: `./modExp 3 11 17` returns `7`, indicating that `3^11 mod 17 = 7`. This is true because 3^11 = 177147 = 10420 * 17 + 7.
* Another example: `./modExp 2 10657 10000` returns `7872`.
  * This result shows that the last four digits of 2^10657 is 7872. Even though the value 2^10657 cannot be calculated directly in C++, as it is far greater than the unsigned 64-bit integer limit of 2^64-1, modular arithmetic can be used to compute the last few digits of the number.
* For modExp.cpp, the base and exponent must be between 0 and 2^64-1, and the modulus must be between 1 and 2^64-1, inclusive.