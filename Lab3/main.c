/*Authors: Trevor Minnix/Travis Bashor
  Class: COP3502C, Summer C 2014
  Postfix Function: This function is written to implement
  postfix notation for arithmetic operations. A stack is
  used to manage values and operators call for use of push()
  and pop() conventions.
*/

#include <stdio.h>
#include "postfix.c"

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