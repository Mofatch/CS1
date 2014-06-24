#ifndef BIGINT_H_
#define BIGINT_H_

#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

BigInt* allocBigInt(uint smallNumber) {
  // allocate new list
  BigInt *newBigInt = malloc(sizeof(BigInt));
  newBigInt->number = allocDList(sizeof(smallNumber));

  // here, use a pointer to allocDigit to create an address for
  // each digit in smallNumber, which can now be modified, since its
  // digits will remain known via their respective pointers. 
  while(smallNumber > 0) {
    // mod 10 to get next digit from right
    // append **Need to pass a pointer, not a uint**
    // div 10 to truncate
  }
}

void printBigInt(BigInt *bigNum) {
  DNode *navigator = bigNum->number->tail;
  while(navigator) {
    printf("%u", *(uint *)navigator->data);
    navigator = navigator->prev;
  }
}

uint* allocDigit(uint number) {
  uint *myNum = malloc(sizeof(number));
  *myNum = number;

  return myNum;
}
#endif