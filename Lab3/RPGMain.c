/* Authors: Trevor Minnix/Travis Bashor
  Class: COP3502C, Summer C 2014
  Lab 3, Part 2, The Game: The purpose of this program is to simulate a turn-based
  battle that might occur in an RPG. A configuration file is used to generate a list
  of allies and enemies to do battle in the program. A queue is used to implement 
  character turns/attacks.*/

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

  // runs the battle and closes ifp at finish
  runBattle(ifp);
}