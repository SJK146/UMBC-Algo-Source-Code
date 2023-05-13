#include <iostream>
#include "trialDivisionv2.h"
#include "PollardGMPv2Time.h"
#include <gmpxx.h>
#include <vector>

int main() {
  int MAX = 20;

mpz_class prime_list1[MAX] = {9675775937, 6329214407, 55417226833, 30322159471, 656622559933, 297254308111, 4046472633449, 1256267284099, 18147937812749, 94686092450687, 735415040736707, 614058583355407, 7694237468484709, 8573606504485907, 5341253330986241, 45646074860602739, 84263766992705371, 373632476778425929, 306131103569152919, 8742753848046052819};
mpz_class prime_list2[MAX] = {5147907433, 1947952729, 2251254931, 96804017081, 99561627727, 629553065881, 494836335769, 3002895175697, 3876315619669, 76237329140407, 41645846321969, 402829460052361, 540801001791143, 6204869245382287, 1233033310402547, 30721861109924629, 91701014302617571, 4485115383992614217, 398332944485144843, 3196475299023707159};
  
  
  mpz_class prime_a;
  mpz_class prime_b;
  bool start = false;
  int calc = 0;
  mpz_class tester;
  //mpz_class var;


  int testLen = 10; 
  for (int j = 0; j < testLen; j++)
  {
    for (int i = 0; i < MAX; i++)
    {
      prime_a = prime_list1[i];
      prime_b = prime_list2[i];
      tester = prime_a * prime_b;
      std::cout << "Performing calculations on " << tester << "...\n";
      pollardStart(tester);
    }
  }
  std::cout << "Trial start" << std::endl;
  for (int j = 0; j < testLen; j++)
  {
    for (int i = 0; i < MAX; i++)
    {
      prime_a = prime_list1[i];
      prime_b = prime_list2[i];
      tester = prime_a * prime_b;
      std::cout << "Performing calculations on " << tester << "...\n";
      trialStart(tester);
    }   
  }
  return(0);
}


