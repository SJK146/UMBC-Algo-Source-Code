//Algos need to reduce a number to prime factors, then put the factors in a vector and hold them there 
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include <vector>
#include <gmpxx.h>
#include <iostream>
#include <fstream>
#include <sys/resource.h>
#include <chrono>
#include "PollardGMPv2Time.h"

const int MAX = 100000000;
const int LMT = 10000;
bool isprime[MAX];

void sieve()    //Sieve of Eratosthenes
{
    memset(isprime, true, sizeof(isprime));
    int i, k, j;
    isprime[1] = false;
    for (i = 4; i <= MAX; i+=2)
    {
        isprime[i] = false;
    }
    for (i = 3; i <= LMT; i+=2)
    {
        if(isprime[i])
            for (j = i*i, k = i<<1; j <= MAX; j+=k)
            {
                isprime[j] = false;
            }
    }
}

mpz_class abso(mpz_class a)     //fn to return absolute value
{
    return a>0?a:-a;
}
mpz_class gcd(mpz_class a, mpz_class b)    //Euclidean GCD recursive fn
{
    //mpz_class zero(0);
    if(b == 0)
        return a;
    else
        return gcd(b, a % b);
}

mpz_class pollard_rho(mpz_class n)  //pollard rho implementation
{
    if(n % 2 == 0)
        return 2;

    mpz_class x((rand()%n-2)+2);
    mpz_class c((rand()%n-1)+1);
    mpz_class y(x);
    mpz_class g(1);

    //fn is f(x) = x*x + c
    while(g==1)
    {
        x = ((x*x)%n + c)%n;    
        y = ((y*y)%n + c)%n;
        y = ((y*y)%n + c)%n;
        g = gcd(abso(x-y),n);


        if(g == n){
            return pollard_rho(n);//move to next x,c after failure 
        }
    }
    return g;
}

std::vector<mpz_class> factors;

void factorize(mpz_class n)   //fn to factorize the number
{
    if(n == 1) {
        return;
    }

    bool isprime = false;

    mpz_class divisor = pollard_rho(n);
    factors.push_back(divisor);
    factors.push_back(n/divisor);
    if(n%2 == 0){
        isprime = false;
    }
}

void pollardStart(mpz_class m)  //Driver Program
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  
    srand(time(NULL));
    long int space;
    if (factors.empty() == false) {
      factors.clear();
    }
    //sieve();
    mpz_class n = m;
    auto begin = std::chrono::high_resolution_clock::now();
    //mpz_class n = m;
    factorize(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin);

    space = usage.ru_maxrss;
    //file stuff
    std::ofstream outfile("TestOutput.txt", std::ios::app);
    outfile << "Prime factors of " << n <<" from Pollard's Rho: \n";
    for (mpz_class factor : factors) {
        outfile << factor << " ";
    }
    outfile << "\n";
    outfile << (elapsed.count() * 1e-9) << "\n";
    outfile <<  space << "\n\n";
    outfile.close();
    return;
}
