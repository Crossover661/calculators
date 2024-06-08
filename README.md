A repository for calculators in C++.

For the factorize.cpp calculator: 
* Type "make" in the root directory to generate the executable
* Type `./factorize <numbers_to_factorize>` in a command prompt to find the prime factorization(s) of the given number(s).
  * Examples: If the executable is called factorize.exe:
  * `./factorize 5` prints `5 is prime.`, because 5 is a prime number.
  * `./factorize 2024` prints the prime factorization of 2024: `2024 is composite. 2024 = 2^3 * 11 * 23`
  * `./factorize 2 22 2024 11 23` prints the prime factorizations of 2, 22, 2024, 11, and 23, each on its own line.
  * This calculator handles integers between 2 and 2^64-1 = 18446744073709551615, inclusive. 0, 1, and negative numbers are neither prime nor composite.
* The worst-case time complexity of the calculator is O(√(n)) where n is the number to be factored, or O(10^(d/2)) where d is the number of digits in the number's decimal representation. The exact time complexity is Θ(√(m)) where m is the largest prime factor of n, or Θ(√(n)) if n is prime.
  * The numbers that take the longest time to factorize are prime numbers close to the 64-bit limit (such as `18446744073709551557`) and semiprimes with factors close to 2^32 (such as `18446743979220271189` = `4294967279 * 4294967291`, the product of the 2 largest 32-bit primes). Factorizing such numbers may take several seconds.