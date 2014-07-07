// Independent main for testing RPG

#include <stdio.h>
#include <math.h>
#include "PriorityQueue.c"
#include "Objects.c"
#include "DArray.c"
#include "DoubleLinkedList.c"

int main(int argc, char **argv) {
  printf("Number of Arguments: %d\n", argc);
  printf("%s\n", argv[0]); 
  if(argc > 1) 
    srand(atoi(argv[1]));
    
}