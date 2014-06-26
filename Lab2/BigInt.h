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

  if(smallNumber == 0) {
    appendDList(newBigInt->number, allocDigit(0));
  }
  else {
    // add digits
    while(smallNumber > 0) {
      // mod 10 to get next digit from right
      appendDList(newBigInt->number, allocDigit(smallNumber % 10));

      // div 10 to truncate
      smallNumber /= 10;
    }
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

BigInt* addBigInt(BigInt *first, BigInt *second) {
  BigInt *newBigInt = allocBigInt(0);
  DNode *firstNavigator = first->number->head;
  DNode *secondNavigator = second->number->head;
  uint carryOver = 0;
  uint digitSum = 0;

  // clear newBigInt
  removeDList(newBigInt->number, 0);
  
  do {
    // two digits to add
    if(firstNavigator && secondNavigator) {
      digitSum = *(uint *)(firstNavigator->data) + *(uint *)(secondNavigator->data) + carryOver;
      carryOver = digitSum / 10;

      // add digitSum % 10 to current digit slot
      appendDList(newBigInt->number, allocDigit(digitSum % 10));

      // move forward
      firstNavigator = firstNavigator->next;
      secondNavigator = secondNavigator->next;
    }
    // first digit only
    else if(firstNavigator) {
      digitSum = *(uint *)(firstNavigator->data) + carryOver;
      carryOver = digitSum / 10;

      // create new digit
      appendDList(newBigInt->number, allocDigit(digitSum % 10));

      // move first forward
      firstNavigator = firstNavigator->next;
    }
    // second digit only
    else if(secondNavigator) {
      digitSum = *(uint *)(secondNavigator->data) + carryOver;
      carryOver = digitSum / 10;

      // create new digit
      appendDList(newBigInt->number, allocDigit(digitSum % 10));

      // move first forward
      secondNavigator = secondNavigator->next;
    }
    // carryOver only
    else {
      appendDList(newBigInt->number, allocDigit(carryOver));
      carryOver = 0;
    }
  } while(firstNavigator || secondNavigator || carryOver);

  return newBigInt;
}

BigInt* shiftLeftBigInt(BigInt *bigNum) {
  // TO DO: refactor with toInt(bigNum) once written
  BigInt *newBigInt = addBigInt(allocBigInt(0), bigNum);
  insertDList(newBigInt->number, allocDigit(0));

  return newBigInt;
}

BigInt* shiftRightBigInt(BigInt *bigNum) {
  // TO DO: refactor with toInt(bigNum) once written  
  BigInt *newBigInt = addBigInt(allocBigInt(0), bigNum);
  free(removeDList(newBigInt->number, 0));

  // dividing any number in [0,9] by 10 should yield 0
  if(newBigInt->number->length == 0) {
    insertDList(newBigInt->number, allocDigit(0));
  }
  return newBigInt;
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