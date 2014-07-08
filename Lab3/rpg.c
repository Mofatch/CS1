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

// determine if the battle is over or not
int checkOutcome(ArrayList* players, ArrayList* enemies) {
  if(sumHealth(players) == 0) {
    return 1;
  }
  else if(sumHealth(enemies) == 0) {
    return -1;
  }
  else {
    return 0;
  }
}

// allocate memory for a new character
GameSprite* allocGameSprite(uint idNum) {
  GameSprite *newGameSprite = malloc(sizeof(GameSprite));
  newGameSprite->id = idNum;

  return newGameSprite;
}

// set healer, fighter, or enemy
void setType(GameSprite* gs, SType t) {
  gs->type = t;
}

// set character speed
void setSpeed(GameSprite* gs, uint spd) {
  gs->speed = spd;
}

// set character hp
void setHP(GameSprite* gs, uint health) {
  gs->hp = health;
}

// set charcter strength
void setStrength(GameSprite* gs, uint str) {
  gs->strength = str;
}

// set character accuracy
void setAccuracy(GameSprite* gs, uint ac) {
  gs->accuracy = ac;
}

// run a battle sequence
void runBattle(FILE *configuration) {
  ArrayList *allies = allocDArray(10, sizeof(GameSprite));
  ArrayList *enemies = allocDArray(10, sizeof(GameSprite));
  uint i, idNum, turnCounter;

  // make a character with the input stats
  while(configuration) {
    for(i = 0; i < 6; ++i) {
      switch(i) {
        case 1:
          fscanf(configuration, "%d", &idNum);
          GameSprite *thisSprite = allocGameSprite(idNum);
          break;
        case 2:
          // type
          break;
        case 3:
          // speed
          break;
        case 4:
          // hp
          break;
        case 5:
          // strength
          break;
        case 6:
          // accuracy
          break;
      }
    }
    // append the allies or enemies array, depending on the type
  }
  fclose(configuration);
  
  /* once the lists are built, run the game as long as
   checkOutcome() returns 0 */
  // at the end of the game, report how many turns there were
  do {
    // check the action queues for 'true'
    // if an action occurs, reset that characters action queue
  } while(checkOutcome(allies, enemies) == 0);
}