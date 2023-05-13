#include <gmpxx.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sys/resource.h>
#include <chrono>
#include "trialDivisionv2.h"

// Finds the prime factors of a number using trial division and returns them as a vector
std::vector<mpz_class> prime_factors(const mpz_class& n) {
  std::vector<mpz_class> factors;
  mpz_class factor(3);
  mpz_class remaining(n);
  while((remaining%2)==0){//evens
    factors.push_back(2);
    remaining /= 2;
  }
  while (factor * factor <= n) {//odds 
    if (remaining % factor == 0) {
      factors.push_back(factor);
      remaining /= factor;
    } else {
      factor+=2;
    }
  }

  if (remaining != 1) {
    factors.push_back(remaining);
  }

  return factors;
}

void trialStart(mpz_class m) {
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  srand(time(NULL));
  long int  space;
  mpz_class n = m;

  auto begin = std::chrono::high_resolution_clock::now();
  std::vector<mpz_class> factors = prime_factors(n);
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
  space = usage.ru_maxrss;
  std::ofstream outfile("TestOutput.txt", std::ios::app);
  outfile << "Prime factors of " << n << " from Trial Division: \n";
  for (mpz_class factor : factors) {
    outfile << factor << " ";
  }
  outfile << "\n";
  outfile <<  (elapsed.count() * 1e-9) << "\n";
  outfile <<  space <<"\n\n";
  outfile.close();

  return;
}
