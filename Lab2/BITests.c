#include <stdio.h>
#include <stdlib.h>
#include "TrevorBigInt.h"

int main(void) {
  // allocate a bigInt
  puts("allocating...");
  BigInt *firstBig = allocBigInt(30);
  BigInt *secondBig = allocBigInt(1);
  puts("shifting...");
  BigInt *leftShift = shiftLeftBigInt(firstBig);
  puts("shifted left...");
  BigInt *rightShift = shiftRightBigInt(firstBig);
  puts("shifted right...");

  // print that shit
  puts("Big Integers:");
  printBigInt(firstBig);
  printBigInt(secondBig);

  // untampered lengths
  printf("Length: %d\n", firstBig->number->length);

  puts("Shift Left First Big Integer:");
  printBigInt(leftShift);

  puts("New Length:");
  printf("%d\n", leftShift->number->length);

  puts("Shift Right First Big Integer:");
  printBigInt(rightShift);

  puts("New New Length:");
  printf("%d\n", rightShift->number->length);

  puts("Testing to int:");
  printf("%u", toInt(firstBig));
  return 0;
}