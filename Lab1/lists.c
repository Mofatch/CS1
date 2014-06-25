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
  insertDList(numList, &randomNum);

  // generate {a,b,c} using insert()
  insertDList(charList, &tres);
  insertDList(charList, &dos);
  insertDList(charList, &uno);
  insertDList(charList, &randomChar);

  // print originals
  printDList(numList);
  printDList(charList);

  // print selected elements
  printElement(removeDList(numList, 9));

  return 0;
}