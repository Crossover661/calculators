A repository for calculators in C++.

For the factorize.cpp calculator:
* Type `./factorize <numbers_to_factorize>` in a command prompt to find the prime factorization(s) of the given number(s).
  * `./factorize 5` prints `5 is prime.`
  * `./factorize 2024` prints `2024 is composite. 2024 = 2^3 * 11 * 23`
  * `./factorize 2 22 2024 11 23` prints the prime factorizations of 2, 22, 2024, 11, and 23, each on its own line.
  * This calculator handles integers between 2 and 2^64-1 = 18446744073709551615, inclusive. 0, 1, and negative numbers are neither prime nor composite.
* The worst-case time complexity of the calculator is O(√(n)) where n is the number to be factored, or O(10^(d/2)) where d is the number of digits in the number's decimal representation.
  * The numbers that take the longest time to factorize are primes close to the 64-bit limit (such as `18446744073709551557`) and semiprimes with factors close to 2^32 (such as `18446743979220271189` = `4294967279 * 4294967291`). Factorizing such numbers may take several seconds.

For the listPrimes.cpp calculator:
* Type `./listPrimes <lowerBound> <upperBound>` to list all prime numbers between lowerBound and upperBound, inclusive, along with the number of primes between said values.
  * Type `./listPrimes <lowerBound> <upperBound> <remainder> <modulus>` to restrict the list of primes to those congruent to `remainder` modulo `modulus`.
* lowerBound and upperBound must be positive integers at most 2^64-1 = 18446744073709551615, and upperBound must be greater than or equal to lowerBound.
* Examples: 
  * `./listPrimes 100 199` prints all prime numbers between 100 and 199, inclusive.
  * `./listPrimes 1000 9999 7 10` prints all 4-digit primes that are congruent to 7 modulo 10 (i.e. primes whose decimal representation ends in 7).
  * If there are more than 10000 primes in the given range, only the 5 smallest and 5 largest primes are printed.


For the modExp.cpp calculator:
* This calculator performs modular exponentiation. Given three positive integers a, b, c, it calculates the remainder when a^b is divided by c.
* Syntax is `./modExp <base> <exponent> <modulus>`.
* Example: `./modExp 3 11 17` returns `7`, indicating that `3^11 mod 17 = 7`. This is true because 3^11 = 177147 = 10420 * 17 + 7.
* Another example: `./modExp 2 10657 10000` returns `7872`.
  * This result shows that the last four digits of 2^10657 is 7872. Even though the value 2^10657 cannot be calculated directly in C++, as it is far greater than the unsigned 64-bit integer limit of 2^64-1, modular arithmetic can be used to compute the last few digits of the number.
* For modExp.cpp, the base and exponent must be between 0 and 2^64-1, and the modulus must be between 1 and 2^64-1, inclusive.

For quadraticResidue.cpp:
* This calculator can determine the quadratic residues modulo a given positive integer n, and whether a non-negative integer m is a residue modulo n. An integer m is a quadratic residue modulo n if there is an integer a such that a^2 == m (mod n). For example, 89 is a quadratic residue modulo 100, because 17^2 == 89 (mod 100).
* Examples:
  * `./quadraticResidue 222`: Lists all quadratic residues modulo 222.
  * `./quadraticResidue 2 7` prints `2 is a quadratic residue modulo 7.`
  * `./quadraticResidue 3 7` prints `3 is NOT a quadratic residue modulo 7.`
* Both the remainder and modulus must be positive integers less than or equal to 2^64-1.