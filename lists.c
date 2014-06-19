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

  // generate {1,2,3} using insert()
  insertDList(numList, &third);
  insertDList(numList, &second);
  insertDList(numList, &first);

  // generate {a,b,c} using insert()
  insertDList(charList, &tres);
  insertDList(charList, &dos);
  insertDList(charList, &uno);

  // print originals
  printDList(numList);
  printDList(charList);

  // print updated lists
  printDList(reverseList(numList));
  printDList(reverseList(charList));

  return 0;
}