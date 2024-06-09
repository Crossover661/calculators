A repository for calculators in C++.

For the factorize.cpp calculator:
* Type `./factorize <numbers_to_factorize>` in a command prompt to find the prime factorization(s) of the given number(s).
  * Examples: If the executable is called factorize.exe:
  * `./factorize 5` prints `5 is prime.`.
  * `./factorize 2024` prints `2024 is composite. 2024 = 2^3 * 11 * 23`.
  * `./factorize 2 22 2024 11 23` prints the prime factorizations of 2, 22, 2024, 11, and 23, each on its own line.
  * This calculator handles integers between 2 and 2^64-1 = 18446744073709551615, inclusive. 0, 1, and negative numbers are neither prime nor composite.
* The worst-case time complexity of the calculator is O(√(n)) where n is the number to be factored, or O(10^(d/2)) where d is the number of digits in the number's decimal representation.
  * The numbers that take the longest time to factorize are prime numbers close to the 64-bit limit (such as `18446744073709551557`) and semiprimes with factors close to 2^32 (such as `18446743979220271189` = `4294967279 * 4294967291`, the product of the 2 largest 32-bit primes). Factorizing such numbers may take several seconds.

For the listPrimes.cpp calculator:
* Type `./listPrimes <lowerBound> <upperBound>` to list all prime numbers between lowerBound and upperBound, inclusive, along with the number of primes between said values.
* lowerBound and upperBound must be positive integers such that `0 <= lowerBound <= upperBound <= 4294967295` and `upperBound - lowerBound <= 100000`.
* Example output:
  * `./listPrimes 100 200` prints:
  ```
  Number of primes: 21
  101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199
  ```
* One can also add modular restrictions with the syntax `./listPrimes <lowerBound> <upperBound> <x> <y>`, which lists primes congruent to x modulo y. Example: `./listPrimes 1 1000 9 10` prints prime numbers between 1 and 1000 that end in 9 in base 10.
  * If modulus is set, then the number of values satisfying the modular congruence between the lower and upper bounds must be less than or equal to 100000. For example, `./listPrimes 1 700000 9 10` is accepted but `./listPrimes 1 1100000 9 10` is not.