#include <stdio.h>
#include "PriorityQueue.c"
#include "Objects.c"
#include "DArray.c"
#include "DoubleLinkedList.c"

int main(int argc, char *argv[]) {
  int count;
  printf("This program was called with \"%s\".\n",argv[0]);

  if(argc > 1) {
    for(count = 1; count < argc; count++) {
      printf("argv[%d] = %s\n", count, argv[count]);
    }
      printf("Result: %d", postfix(argc, argv));
  }
  else {
    printf("The command had no arguments.\n");
  }
  
  return 0;
}

int postfix(int numArguments, char **argList) {
  // initialize a stack
  PQMode myMode = PQMODE_STACK;
  PQueue *myStack = allocPQueue(sizeof(int), myMode);
  int i;
  int result, higher, lower;

  // go through the list, collecting arguments
  for(i = 1; i < numArguments; ++i) {
    switch(*argList[i]) {
      case '+':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower + higher));      
        printf("Top: %d\n", *(int *)top(myStack));
        break;
      case '-':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower - higher));
        printf("Top: %d\n", *(int *)top(myStack));
        break;
      case '*':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower * higher));
        printf("Top: %d\n", *(int *)top(myStack));
        break;
      default:
        add(myStack, allocIntWith(atoi(argList[i])));
        printf("Top: %d\n", *(int *)top(myStack));
    }
  }
  // assign result a copy of top(), release the stack
  result = *(int *)top(myStack);
  releasePQueue(myStack);

  return result;
}