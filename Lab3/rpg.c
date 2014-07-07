#include "rpg.h"

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
        target->hp -= gs->strength;
        break;
      case FIGHTER:
        // get a random enemy and reduce its hp
        target->hp -= gs->strength;
        break;
      case HEALER:
        // heal random ally
        target->hp += gs->strength;
        break;
    }
    // hit
    printf("Hit!\n");
    return true;
  }
  // miss
  printf("Miss!\n");
  return false;
}
