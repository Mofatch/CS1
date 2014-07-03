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
      printf("Result: %d", postfix(argc, argv));
    }
  }
  else {
    printf("The command had no arguments.\n");
  }
  
  return 0;
}

int postfix(int numArguments, char **argList) {
  // initialize a stack
  PQMode myMode = PQMODE_STACK;
  PQueue *myStack = allocPQueue(sizeof(int), myMode);int i;
  int result, first, second;

  // go through the list, collecting arguments
  for(i = 1; i < numArguments; ++i) {
    puts("whee!");
    switch(*argList[i]) {
      case '+':
        puts("+ case");
        puts("assigning first");
        first = *(int *)top(myStack);
        puts("popping first");
        pop(myStack);
        puts("assigning second");
        second = *(int *)top(myStack);
        puts("popping second");
        pop(myStack);
        puts("pushing sum to stack");
        push(myStack, allocIntWith(first + second));      
        puts("breaking");
        break;
      default:
        puts("adding...");
        add(myStack, allocIntWith(atoi(argList[i])));
        printf("%d\n", *(int *)top(myStack));
        puts("done adding...");
    }
  }
  // assign result a copy of top(), release the stack
  puts("assigning...");
  result = *(int *)top(myStack);
  printf("%d\n", result);
  puts("releasing...");
  releasePQueue(myStack);

  puts("returning...");
  return result;
}