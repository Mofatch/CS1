#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"

int main(void) {
  puts("allocating...");
  BigInt *bigInt = allocBigInt(312);

  // if(bigInt->number->head) {
  //   printf("%u\n", *(uint *)bigInt->number->head->data);
  // }
  printBigInt(bigInt);

  puts("releasing...");
  releaseBigInt(bigInt);

  puts("printing...");
  printBigInt(bigInt);
  puts("done printing...");

  return 0;
}