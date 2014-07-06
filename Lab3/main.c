/*Authors: Trevor Minnix/Travis Bashor
  Class: COP3502C, Summer C 2014
  Postfix Function: This function is written to implement
  postfix notation for arithmetic operations. A stack is
  used to manage values and operators call for use of push()
  and pop() conventions.
*/

#include <stdio.h>
#include <math.h>
#include "PriorityQueue.c"
#include "Objects.c"
#include "DArray.c"
#include "DoubleLinkedList.c"

int main(int argc, char *argv[]) {
  int count;

  if(argc > 1) {
    puts("**Postfix Test**");
    printf("Result: %d\n", postfix(argc, argv));
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
  int result, higher, lower, element;

  // go through the list, collecting arguments
  for(i = 1; i < numArguments; ++i) {
    switch(*argList[i]) {
      case '+':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower + higher));      
        break;
      case '-':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower - higher));
        break;
      case '*':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower * higher));
        break;
      case '/':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower / higher));
        break;
      case '%':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower % higher));
        break;
      case '^':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        element = (higher < 1) ? 0 : pow(lower, higher);
        push(myStack, allocIntWith(element));
        break;
      default:
        add(myStack, allocIntWith(atoi(argList[i])));
    }
  }
  // assign result a copy of top(), release the stack
  result = *(int *)top(myStack);
  releasePQueue(myStack);

  return result;
}