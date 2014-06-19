#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

int main(void) {
  int j, k; 
  int randomNum = 99;
  char randomChar = 'Z';

  int *i = calloc(4, sizeof(int));
  char *c = calloc(4, sizeof(char));
  DoubleLinkedList *numList = allocDList(sizeof(int));
  DoubleLinkedList *charList = allocDList(sizeof(char));

  for(j = 0; j < 4; ++j) {
    i[j] = j;
    insertDListElementAt(numList, i+j, j);
  }

  for(k = 0; k < 4; ++k) {
    c[k] = 'A' + k;
    insertDListElementAt(charList, c+k, k);
  }

  printDList(numList);
  printDList(charList);

  insertDListElementAt(numList, &randomNum, 2);
  insertDListElementAt(charList, &randomChar, 2);

  printDList(numList);
  printDList(charList);
  return 0;
}