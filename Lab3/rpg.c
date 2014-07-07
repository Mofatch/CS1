#include "rpg.h"

bool actionProcess(GameSprite* gs, ArrayList* players, ArrayList* enemies) {
  int num = rand() % 101;
  GameSprite *target;

  if(num < gs->accuracy) {
    switch(gs->type) {
      case ENEMY:
        // get a random ally and reduce its hp
        if(players->length > 0) {
          target = (GameSprite *)getDArray(players, (rand() % players->length));
          target->hp -= gs->strength;
        }
        break;
      case FIGHTER:
        // get a random enemy and reduce its hp
        if(enemies->length > 0) {
          target = (GameSprite *)getDArray(enemies, (rand() % enemies->length));
          target->hp -= gs->strength;
        }
        break;
      case HEALER:
        // heal random ally
        if(players->length > 0) {
          target = (GameSprite *)getDArray(players, (rand() % players->length));
          target->hp += gs->strength;
        }
        break;
    }
    // hit
    return true;
  }
  // no hit
  return false;
}
