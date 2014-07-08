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
                                     target->id, target->hp);
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
    enqueue(gs->actions, allocBoolWith(false));
  }

  // last element is true
  if(i <= 10) {
    enqueue(gs->actions, allocBoolWith(true));
  }
}

// used for calculating total hp of ally or enemy team
int sumHealth(ArrayList *list) {
  GameSprite *currentGS;
  int i, totalHP;
  if(list) {
    for(i = 0; i < list->length; ++i) {
      currentGS = (GameSprite *)list->data[i];
      totalHP += currentGS->hp;
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
  GameSprite *thisSprite;
  GameSprite *thisAlly;
  GameSprite *thisEnemy;
  bool action;
  uint i, input, turnCounter;
  char type;

  // make a character with the input stats
  while(!feof(configuration)) {
    for(i = 0; i < 6; ++i) {
      switch(i) {
        // id
        case 1:
          fscanf(configuration, "%d", &input);
          thisSprite = allocGameSprite(input);
          break;
        // type
        case 2:
          fscanf(configuration, "%c", &type);
          if(type == 'E') {
            setType(thisSprite, ENEMY);
            appendDArray(enemies, thisSprite);
          }
          else if (type == 'H') {
            setType(thisSprite, HEALER);
            appendDArray(allies, thisSprite);
          }
          else if (type == 'F') {
            setType(thisSprite, FIGHTER);
            appendDArray(allies, thisSprite);
          }
          break;
        // speed
        case 3:
          fscanf(configuration, "%d", &input);
          setSpeed(thisSprite, input);
          resetActionQueue(thisSprite);
          break;
        // hp
        case 4:
          fscanf(configuration, "%d", &input);
          setHP(thisSprite, input);
          break;
        // strength
        case 5:
          fscanf(configuration, "%d", &input);
          setStrength(thisSprite, input);
          break;
        // accuracy
        case 6:
          fscanf(configuration, "%d", &input);
          setAccuracy(thisSprite, input);
          break;
      } // end switch
    } // end for
  } // end while
  fclose(configuration);
  
  // at the end of the game, report how many turns there were
  do {
    // next turn
    turnCounter++;

    // check for action on allies side
    for(i = 0; i < allies->length; ++i) {
      thisAlly = (GameSprite *)getDArray(allies, i);
      action = (bool *)front(thisAlly->actions);
      if(action == true) {
        actionProcess(getDArray(allies, i), allies, enemies);
        resetActionQueue(getDArray(allies, i));
      }
      else {
        dequeue(thisAlly->actions);
      }
    }

    // check for action on enemy side
    for(i = 0; i < enemies->length; ++i) {
      thisEnemy = (GameSprite *)getDArray(enemies, i);
      action = (bool *)front(thisEnemy->actions); 
      if(action == true) {
        actionProcess(getDArray(enemies, i), allies, enemies);
        resetActionQueue(getDArray(enemies, i));
      }
      else {
        dequeue(thisEnemy->actions);
      }
    }
      
  } while(checkOutcome(allies, enemies) == 0);
}