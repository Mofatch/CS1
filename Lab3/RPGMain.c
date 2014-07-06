// Independent main for testing RPG

#include <stdio.h>
#include <math.h>
#include "PriorityQueue.c"
#include "Objects.c"
#include "DArray.c"
#include "DoubleLinkedList.c"

int main(int argc, char **argv) {
  // create a file pointer
  FILE *ifp;
  int numEntries, score, i;

  // open input.txt
  ifp = fopen("input.txt","r");

  // find the number of entries in the file
  fscanf(ifp, "%d", &numEntries);

  for(i = 1; i <= numEntries; ++i) {
    fscanf(ifp, "%d", &score);
    printf("Score %d: %d\n", i, score);
  }

  // close input.txt
  fclose(ifp);
}