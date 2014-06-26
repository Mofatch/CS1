#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"

int main(void) {
  // allocate a bigInt
  BigInt *firstBig = allocBigInt(200000);
  BigInt *secondBig = allocBigInt(1);

  // print that shit
  printBigInt(firstBig);
  printBigInt(secondBig);
  printBigInt(addBigInt(firstBig, secondBig));

  return 0;
}