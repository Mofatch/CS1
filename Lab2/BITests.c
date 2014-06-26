#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"

int main(void) {
  // allocate a bigInt
  BigInt *firstBig = allocBigInt(312);
  BigInt *secondBig = allocBigInt(312);

  // print that shit
  printBigInt(firstBig);
  printf("%u\n", firstBig->number->length);
  printBigInt(secondBig);
  printf("%u\n", secondBig->number->length);

  // compare
  if(compareBigInt(firstBig, secondBig) < 0) 
    puts("first < second");
  else if(compareBigInt(firstBig, secondBig) == 0)
    puts("they are the same");
  else
    puts("first > second");
  return 0;
}