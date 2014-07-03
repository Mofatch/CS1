#include <stdio.h>
#include "PriorityQueue.h"
#include "Objects.h"
#include "DArray.h"
#include "DoubleLinkedList.h"

int main(int argc, char *argv[]) {
  int count;
  PQueue *myStack = allocPQueue()
  printf("This program was called with \"%s\".\n",argv[0]);

  if(argc > 1) {
    for(count = 1; count < argc; count++) {
      printf("argv[%d] = %d\n", count, atoi(argv[count]) + 3);
    }
  }
  else {
    printf("The command had no arguments.\n");
  }
  
  return 0;
}