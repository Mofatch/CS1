#ifndef BIGINT_H_
#define BIGINT_H_

#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

// prototypes
uint* allocDigit(uint number);

BigInt* allocBigInt(uint smallNumber) {
  // allocate new list
  BigInt *newBigInt = malloc(sizeof(BigInt));
  newBigInt->number = allocDList(sizeof(smallNumber));

  while(smallNumber > 0) {
    // mod 10 to get next digit from right
    appendDList(newBigInt->number, allocDigit(smallNumber % 10));

    // div 10 to truncate
    smallNumber /= 10;
  }

  return newBigInt;
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