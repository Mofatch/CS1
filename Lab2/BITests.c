#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"

int main(void) {
  // allocate a bigInt
  BigInt *firstBig = allocBigInt(441);
  BigInt *secondBig = allocBigInt(312);

  // print that shit
  printBigInt(firstBig);
  printBigInt(secondBig);

  shiftLeftBigInt(firstBig);
  shiftLeftBigInt(firstBig);
  shiftLeftBigInt(firstBig);

  printBigInt(firstBig);
  printf("Length: %d", firstBig->number->length);
  return 0;
}