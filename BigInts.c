#include <stdio.h>
#include <stdlib.h>
#include "BigInt.h"

int main(void) {
  puts("allocating...");
  BigInt *bigInt = allocBigInt(312);

  puts("printing...");
  printBigInt(bigInt);
  return 0;
}