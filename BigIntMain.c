/*
 * main.c
 *
 *  Created on: Jun 17, 2014
 *      Author: lugoh008
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "DoubleLinkedList.h"
#include "BigInt.h"

typedef BigInt* BInt;

void printElement(Object data){
  char val = *((char*)data);
  printf("%c", val);
}

int main(int argc, char** argv){
  DoubleLinkedList* list = allocDList(sizeof(char));
  char test = 'A';
  printf("TESTING APPEND ...\n\n");
  appendDList(list, &test);
  debugDList(list);
  printf("\n");
  printDList(list);
  printf("\n");
  test += 1;
  appendDList(list, &test);
  debugDList(list);
  printf("\n");
  printDList(list);
  printf("\n");
  test += 1;
  appendDList(list, &test);
  debugDList(list);
  printf("\n");
  printDList(list);
  printf("\n");
  test += 1;
  printf("TESTING INSERT ...\n\n");
  insertDList(list, &test);
  debugDList(list);
  printf("\n");
  printDList(list);
  printf("\n");
  test += 1;
  printf("TESTING INSERT AT 2 then 1 ...\n\n");
  insertDListElementAt(list, &test, 2);
  test += 1;
  insertDListElementAt(list, &test, 1);
  debugDList(list);
  printf("\n");
  printDList(list);
  printf("\n");

  //half list
  printf("TESTING HALF ...\n\n");
  DoubleLinkedList* half = halfList(list);
  debugDList(half);
  printf("\n");
  printDList(half);
  printf("\n");

  //reverse list
  printf("TESTING REVERSE ...\n\n");
  DoubleLinkedList* reverse = reverseDList(list);
  debugDList(reverse);
  printf("\n");
  printDList(reverse);
  printf("\n");

  //testing remove
  printf("TESTING REMOVE ...\n\n");
  while(reverse->length){
    removeDList(reverse, 0);
    debugDList(reverse);
    printf("\n");
    printDList(reverse);
    printf("\n");
  }

  printf("TESTING RANDOM ELEMENT REMOVAL ...\n\n");
  Object data = removeDList(list, 1);
  printf("REMOVED ");
  printElement(data);
  printf("\n");
  debugDList(list);
  printf("\n");
  printDList(list);
  printf("\n");

  releaseDList(reverse);
  releaseDList(half);
  releaseDList(list);
  //Alloc two BigInts to test operation
  /*
  BInt first = allocBigInt(5);
  BInt second = allocBigInt(4);

  //add Test
  BInt addition = addBigInt(first, second);
  printBigInt(addition);
  assert(toInt(addition) ==  20);
  releaseBigInt(addition);
  //causing overflow
  //1) -1 would become the largest int because the int is unsigned
  unsigned int maxInt = -1;
  unsigned long maxLong = -1;
  //2) add 1 to such value to get 0 in a uint but correct value with BigInt (the same goes for long)
  unsigned int intOverflow = maxInt + 1;
  unsigned int longOverflow = maxLong + 1;
  BInt intLimit = allocBigInt(maxInt);
  BInt longLimit = allocBigInt(maxLong);
  BInt one = allocBigInt(1);
  BInt intAddOverflowTest = addBigInt(intLimit, one);
  BInt longAddOverflowTest = addBigInt(longLimit, one);
  printf("Int vs BigInt:\n");
  printf("%d\t", intOverflow);
  printBigInt(intAddOverflowTest);
  printf("Long vs BigInt:\n");
  printf("%ld\t", longOverflow);
  printBigInt(longAddOverflowTest);
  //write asserts for intAddOverflowTest and longAddOverflowTest
  releaseBigInt(intLimit);
  releaseBigInt(longLimit);
  releaseBigInt(one);
  releaseBigInt(intAddOverflowTest);
  releaseBigInt(longAddOverflowTest);


  //shift left and right
  //normal test
  uint testNum = 20;
  uint targetLeft = 200;
  uint targetRight = 2;
  BInt bigTest = allocBigInt(20);
  BInt bigLeft = shiftLeftBigInt(bigTest);
  BInt bigRight = shiftRightBigInt(bigTest);
  assert(toInt(bigLeft) == targetLeft);
  assert(toInt(bigRight) == targetRight);
  releaseBigInt(bigTest);
  releaseBigInt(bigLeft);
  releaseBigInt(bigRight);

  //multiply
  BInt mulTest = multiplyBigInt(first, second);
  assert(toInt(mulTest) == 20);
  //causing overflow
  BInt four = allocBigInt(4);
  uint previousInt = 20;
  unsigned long previousLong = 20;
  while(previousInt < (previousInt * 4)){
    BInt temp = multiplyBigInt(mulTest, four);
    releaseBigInt(mulTest);
    mulTest = temp;
    previousInt *= 4;
  }
  BInt mulTestLong = multiplyBigInt(first, second);
  while(previousLong < (previousLong * 4)){
    BInt temp = multiplyBigInt(mulTestLong, four);
    releaseBigInt(mulTestLong);
    mulTestLong = temp;
    previousLong *= 4;
  }
  //overflow generated
  previousInt *= 4;
  previousLong *= 4;

  BInt temp = multiplyBigInt(mulTest, four);
  releaseBigInt(mulTest);
  mulTest = temp;
  temp = multiplyBigInt(mulTestLong, four);
  releaseBigInt(mulTestLong);
  mulTestLong = temp;

  printf("Int vs BigInt:\n");
  printf("%d\t", previousInt);
  printBigInt(mulTest);
  printf("Long vs BigInt:\n");
  printf("%ld\t", previousLong);
  printBigInt(mulTestLong);

  releaseBigInt(mulTest);
  releaseBigInt(mulTestLong);

  //dividable tests
  BInt test = allocBigInt(240);
  assert(isBigIntDividableBy(test, 2));
  assert(isBigIntDividableBy(test, 3));
  assert(isBigIntDividableBy(test, 5));
  assert(isBigIntDividableBy(test, 6));
  assert(isBigIntDividableBy(test, 8));
  assert(!isBigIntDividableBy(test, 9));
  releaseBigInt(test);

  releaseBigInt(first);
  releaseBigInt(second);
   */
  return 0;
}