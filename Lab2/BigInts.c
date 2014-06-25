#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"

int main(void) {
  // allocate a bigInt
  BigInt *bigInt = allocBigInt(312);

  // print that shit
  printBigInt(bigInt);

  // release it into the wild
  releaseBigInt(bigInt);

  // try to print it, fail
  printBigInt(bigInt);

  return 0;
}