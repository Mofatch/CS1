#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

int main(void) {
  int first = 1;
  int second = 2;
  int third = 3;
  int randomNum = 99;
  // char randomChar = 'Z';

  int *i = calloc(4, sizeof(int));
  // char *c = calloc(4, sizeof(char));
  DoubleLinkedList *numList = allocDList(sizeof(int));
  // DoubleLinkedList *charList = allocDList(sizeof(char));

  // generate {1,2,3} using append()
  appendDlist(numList, &first);
  appendDlist(numList, &second);
  appendDlist(numList, &third);

  
  printDList(numList);
  // printDList(charList);

  // insertDListElementAt(numList, &randomNum, 2);
  // insertDListElementAt(charList, &randomChar, 2);

  return 0;
}