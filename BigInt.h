#ifndef BIGINT_H_
#define BIGINT_H_

#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

BigInt* allocBigInt(uint smallNumber) {
  BigInt *newBigInt = malloc(sizeof(BigInt));
  newBigInt->number = allocDList(sizeof(smallNumber));

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

#endif