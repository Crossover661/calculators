A repository for calculators in C++.

For the factorize.cpp calculator: 
* Generate the executable using a C++ compiler.
* Type `./<name_of_executable> <numbers_to_factorize>` in a command prompt to find the prime factorization(s) of the given number(s).
  * Example: If the executable is called factorize.exe:
  * `./factorize 5` prints `5 is prime.`, because 5 is a prime number.
  * `./factorize 2024` prints the prime factorization of 2024: `2024 is composite. 2024 = 2^3 * 11 * 23`
  * `./factorize 2 22 2024 11 23` prints the prime factorizations of 2, 22, 2024, 11, and 23, each on its own line.
  * This calculator handles integers between 2 and 2^64-1 = 18446744073709551615, inclusive. 0, 1, and negative numbers are neither prime nor composite.
