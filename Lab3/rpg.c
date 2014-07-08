#include "rpg.h"

// using player/enemy info, run an action phase (attack or heal)
bool actionProcess(GameSprite* gs, ArrayList* players, ArrayList* enemies) {
  // target of action
  GameSprite *target;
  int roll;

  if(gs->type == ENEMY) {
    target = (GameSprite *)getDArray(players, (rand() % players->length));
    printf("%d attacks %d!", gs->id, target->id);
  }
  else if(gs->type == FIGHTER) {
    target = (GameSprite *)getDArray(enemies, (rand() % enemies->length));
    printf("%d attacks %d!", gs->id, target->id);
  }
  else if(gs->type == HEALER) {
    target = (GameSprite *)getDArray(players, (rand() % players->length));
    printf("%d attempts to heal %d!", gs->id, target->id);
  }
  // random number in [0,100]
  roll = rand() % 101;

  if(roll < gs->accuracy) {
    switch(gs->type) {
      case ENEMY:
        // get a random ally and reduce its hp
        if(gs->strength > target->hp) {
          target->hp -= gs->strength;
        }
        else {
          target->hp = 0;
        }
        break;
      case FIGHTER:
        // get a random enemy and reduce its hp
        if(gs->strength > target->hp) {
          target->hp -= gs->strength;
        }
        else {
          target->hp = 0;
        }
        break;
      case HEALER:
        // heal random ally
        target->hp += gs->strength;
        break;
    }
    // hit
    printf("Hit! ");
    printf("%d has %d hp and %d has %d hp.", gs->id, gs->hp, 
                                     target->id, target->hp)
    return true;
  }
  // miss
  printf("Miss!\n");
  return false;
}

// using speed, ready this character for another battle
void resetActionQueue(GameSprite* gs) {
  int i, numFalse;
  // clear the list
  while(!isEmptyPQueue(gs->actions)) {
    dequeue(gs->actions);
  }

  // rebuild the list
  numFalse = 10 - gs->speed;
  
  for(i = 1; i <= numFalse; ++i) {
    // add falses first
    enqueue(allocBoolWith(false));
  }

  // last element is true
  if(i <= 10) {
    enqueue(allocBoolWith(true));
  }
}

// determine if the battle is over or not
int checkOutcome(ArrayList* players, ArrayList* enemies) {

}

// used for calculating total hp of ally or enemy team
int sumHealth(ArrayList *list) {
  int i, totalHP;
  if(list) {
    for(i = 0; i < list->length; ++i) {
      totalHP += list->data[i]->hp;
    }
  }

  return totalHP;
}