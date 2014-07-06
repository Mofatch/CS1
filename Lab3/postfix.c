// TO DO: Check about negative-valued integers used in postfix
#include <math.h>
#include "postfix.h"
#include "PriorityQueue.c"
#include "Objects.c"
#include "DArray.c"
#include "DoubleLinkedList.c"

int postfix(int numArguments, char **argList) {
  // initialize a stack
  PQMode myMode = PQMODE_STACK;
  PQueue *myStack = allocPQueue(sizeof(int), myMode);
  int i;
  int result, higher, lower, element;

  // go through the list, collecting arguments
  for(i = 1; i < numArguments; ++i) {
    switch(*argList[i]) {
      // addition
      case '+':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower + higher));      
        break;
      // subtraction
      case '-':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower - higher));
        break;
      // multiplication
      case '*':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower * higher));
        break;
      // division
      case '/':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower / higher));
        break;
      // modulus
      case '%':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        push(myStack, allocIntWith(lower % higher));
        break;
      // power
      case '^':
        higher = *(int *)top(myStack);
        pop(myStack);
        lower = *(int *)top(myStack);
        pop(myStack);
        element = (higher < 1) ? 0 : pow(lower, higher);
        push(myStack, allocIntWith(element));
        break;
      // operands
      default:
        add(myStack, allocIntWith(atoi(argList[i])));
    }
  }
  // assign result a copy of top(), release the stack
  result = *(int *)top(myStack);
  releasePQueue(myStack);

  return result;
}