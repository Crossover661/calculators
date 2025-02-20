A repository for calculators in C++.

**factorize.cpp**:
* Type `./factorize <numbers_to_factorize>` in a command prompt to find the prime factorization(s) of the given number(s).
  * `./factorize 5` prints `5 is prime.`
  * `./factorize 2024` prints `2024 is composite. 2024 = 2^3 * 11 * 23`
  * `./factorize 2 22 2024 11 23` prints the prime factorizations of 2, 22, 2024, 11, and 23, each on its own line.
  * This calculator handles integers between 2 and 2^64-1 = 18446744073709551615, inclusive. 0, 1, and negative numbers are neither prime nor composite.
* This calculator uses trial division to factorize integers. Thus, its worst-case time complexity is O(√(n)) where n is the number to be factored, or O(2^(b/2)) where b is the size of the integer in bits.
  * The numbers that take the longest time to factorize are primes close to the 64-bit limit (such as `18446744073709551557`) and semiprimes with factors close to 2^32 (such as `18446743979220271189` = `4294967279 * 4294967291`). Factorizing such numbers may take several seconds.
* This is a standalone program and does not include any external files, such as those in the "lib" folder.

**listPrimes.cpp**:
* Type `./listPrimes <lowerBound> <upperBound>` to list all prime numbers between lowerBound and upperBound, inclusive, along with the number of primes between said values.
  * Type `./listPrimes <lowerBound> <upperBound> <remainder> <modulus>` to restrict the list of primes to those congruent to `remainder` modulo `modulus`.
* lowerBound and upperBound must be positive integers less than 2^64, and upperBound must be greater than or equal to lowerBound.
* Examples: 
  * `./listPrimes 100 199` prints all prime numbers between 100 and 199, inclusive.
  * `./listPrimes 1000 9999 7 10` prints all 4-digit primes that are congruent to 7 modulo 10 (i.e. primes whose decimal representation ends in 7).
  * If there are more than 10000 primes in the given range, only the 5 smallest and 5 largest primes are printed.
* This program uses the Miller-Rabin primality test, which uses modular exponentation to quickly determine the primality of an integer without factorizing it.


**modExp.cpp**:
* This calculator performs modular exponentiation. Given three positive integers a, b, c, it calculates the remainder when a^b is divided by c.
* Syntax is `./modExp <base> <exponent> <modulus>`.
* Example: `./modExp 3 11 17` returns `7`, indicating that `3^11 mod 17 = 7`. This is true because 3^11 = 177147 = 10420 * 17 + 7.
* Another example: `./modExp 2 10657 10000` returns `7872`.
  * This result shows that the last four digits of 2^10657 is 7872. Even though the value 2^10657 cannot be calculated directly in C++, as it is far greater than the unsigned 64-bit integer limit of 2^64-1, modular arithmetic can be used to compute its last digits.
* For modExp.cpp, the base and exponent must be between 0 and 2^64-1, and the modulus must be between 1 and 2^64-1, inclusive.

**quadraticResidue.cpp**:
* This calculator can determine the quadratic residues modulo a given positive integer n, and whether a non-negative integer m is a residue modulo n. An integer m is a quadratic residue modulo n if there is an integer a such that a^2 == m (mod n). For example, 9 is a quadratic residue modulo 10, because 3^2 == 7^2 == 9 (mod 10).
* Examples:
  * `./quadraticResidue 222`: Lists all quadratic residues modulo 222.
  * `./quadraticResidue 2 7` prints `2 is a quadratic residue modulo 7.`
  * `./quadraticResidue 3 7` prints `3 is NOT a quadratic residue modulo 7.`
* Both the remainder and modulus must be positive integers less than 2^64.