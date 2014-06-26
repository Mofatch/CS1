#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"

int main(void) {
  // allocate a bigInt
  BigInt *firstBig = allocBigInt(2);
  BigInt *secondBig = allocBigInt(1);

  // print that shit
  puts("Big Integers:");
  printBigInt(firstBig);
  printBigInt(secondBig);

  puts("Sum:");
  printBigInt(addBigInt(firstBig, secondBig));

  puts("Shift Left First Big Integer:");
  printBigInt(shiftLeftBigInt(firstBig));

  return 0;
}