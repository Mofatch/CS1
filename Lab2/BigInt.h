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

  // add digits
  while(smallNumber > 0) {
    // mod 10 to get next digit from right
    appendDList(newBigInt->number, allocDigit(smallNumber % 10));

    // div 10 to truncate
    smallNumber /= 10;
  }

  return newBigInt;
}

void releaseBigInt(BigInt *bigNum) {
  if(bigNum) {
    if(bigNum->number) {
      releaseDList(bigNum->number);
      bigNum->number = NULL;
    }
    free(bigNum);
  }
}

// TO DO: write this
BigInt* addBigInt(BigInt *first, BigInt *second) {
  BigInt *newBigInt = allocBigInt(0);
  /*code*/
  return newBigInt;
}

BigInt* shiftLeftBigInt(BigInt *bigNum) {
  uint *zero = malloc(sizeof(uint));
  *zero = 0;
  insertDList(bigNum->number, zero);
}

int compareBigInt(BigInt *first, BigInt *second) {
  int theOneTrueDigit = 0; // same until proven different

  // more digits in second number
  if(first->number->length < second->number->length) {
    theOneTrueDigit = -1;
  }// more digits in first number
  else if(first->number->length > second->number->length) {
    theOneTrueDigit = 1;
  }
  // same number of digits
  else {
    DNode *firstElement = first->number->tail;
    DNode *secondElement = second->number->tail;
    while(firstElement) {
      if(*(uint *)firstElement->data > *(uint *)secondElement->data) {
        theOneTrueDigit = 1;
        break;
      }
      else if(*(uint *)firstElement->data < *(uint *)secondElement->data) {
        theOneTrueDigit = -1;
        break;
      }
      // down an order of 10
      firstElement = firstElement->prev;
      secondElement = secondElement->prev;
    }      

  }
  return theOneTrueDigit;
}

void printBigInt(BigInt *bigNum) {
  if(bigNum) {
    if(bigNum->number->length > 0) {
      DNode *navigator = bigNum->number->tail;

      while(navigator) {
        printf("%u", *(uint *)navigator->data);
        navigator = navigator->prev;
      }
      printf("\n");
    }
    else
      puts("Nothing to print.");
  }
}

// create memory for a given uint
uint* allocDigit(uint number) {
  uint *myNum = malloc(sizeof(number));
  *myNum = number;

  return myNum;
}
#endif