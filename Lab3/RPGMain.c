// Independent main for testing RPG

#include <stdio.h>
#include <math.h>
#include "PriorityQueue.c"
#include "DArray.c"
#include "DoubleLinkedList.c"
#include "rpg.c"

int main(int argc, char **argv) {
  // open file with input from user
  FILE *ifp = fopen(argv[1],"r");

  // if there was a number entered, seed rand() with it
  if(argc > 2) {
    srand(atoi(argv[2]));
  }

  runBattle(ifp);
}