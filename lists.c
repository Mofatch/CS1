#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

int main(void) {
  int i;
  int first = 1;
  int second = 2;
  int third = 3;
  int randomNum = 99;
  char uno = 'a';
  char dos = 'b';
  char tres = 'c';
  char randomChar = 'Z';

  DoubleLinkedList *numList = allocDList(sizeof(int));
  DoubleLinkedList *charList = allocDList(sizeof(char));

  // generate {1,2,3} using append()
  appendDList(numList, &first);
  appendDList(numList, &second);
  appendDList(numList, &third);

  // generate {a,b,c} using append()
  appendDList(charList, &uno);
  appendDList(charList, &dos);
  appendDList(charList, &tres);

  // print originals
  printDList(numList);
  printDList(charList);

  for(i = 0; i <= numList->length; ++i) {
    printf("Inserting at %d\n", i);
    // insert at new spot
    insertDListElementAt(numList, &randomNum, i);
    insertDListElementAt(charList, &randomChar, i);

    // print updated lists
    printDList(numList);
    printDList(charList);
  }

  return 0;
}