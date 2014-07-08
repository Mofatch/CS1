// Independent main for testing RPG

#include <stdio.h>
#include <math.h>
#include "PriorityQueue.c"
#include "DArray.c"
#include "DoubleLinkedList.c"
#include "rpg.c"

int main(int argc, char **argv) {
  // could be argv[1]
  FILE *ifp = fopen(argv[1],"r");
  printf("Number of Arguments: %d\n", argc);
  printf("%s\n", argv[1]); 

  // if there was a number entered, seed rand() with it
  if(argc > 2) 
    srand(atoi(argv[2]));

  runBattle(ifp);
}