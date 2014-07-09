#include "rpg.h"

// using player/enemy info, run an action phase (attack or heal)
bool actionProcess(GameSprite* gs, ArrayList* players, ArrayList* enemies) {
  // target of action
  GameSprite *target;
  int roll, pos;

  // ENEMY
  if(gs->type == ENEMY) {
    // find a live target
    do {
      if(target) {
        // release previous memory if it contained a dead GameSprite
        if(target->hp == 0) {
          releaseGameSprite(target);
        }
      }
      pos = rand() % players->length;
      target = (GameSprite *)getDArray(players, pos);
    } while(target->hp == 0);
    printf("%d attacks %d!\n", gs->id, target->id);
  }
  // FIGHTER
  else if(gs->type == FIGHTER) {
    // find a live target
    do {
      if(target) {
        // release previous memory if it contained a dead GameSprite
        if(target->hp == 0) {
          releaseGameSprite(target);
        }
      }
      pos = rand() % enemies->length;
      target = (GameSprite *)getDArray(enemies, pos);
    } while(target->hp == 0);
    printf("%d attacks %d!\n", gs->id, target->id);
  }
  // HEALER
  else if(gs->type == HEALER) {
    // find a live target
    do {
      if(target) {
        // release previous memory if it contained a dead GameSprite
        if(target->hp == 0) {
          releaseGameSprite(target);
        }
      }
      pos = rand() % players->length;
      target = (GameSprite *)getDArray(players, pos);
    } while(target->hp == 0);
    printf("%d attempts to heal %d!\n", gs->id, target->id);
  }

  // random number in [0,100]
  roll = rand() % 101;
  if(roll < gs->accuracy) {
    switch(gs->type) {
      case ENEMY:
        // get a random player and reduce its hp
        if(gs->strength < target->hp) {
          target->hp -= gs->strength;
        }
        else {
          target->hp = 0;
        }
        // replace with injured player
        setDArray(players, pos, target);
        break;
      case FIGHTER:
        // get a random enemy and reduce its hp
        if(gs->strength < target->hp) {
          target->hp -= gs->strength;
        }
        else {
          target->hp = 0;
        }
        // replace with injured enemy
        setDArray(enemies, pos, target);
        break;
      case HEALER:
        // heal random ally
        if(target->hp == 0) {
          printf("Cannot revive %d...", target->id);
        }
        else {
          target->hp += gs->strength;
        }
        // replace with healed ally
        setDArray(players, pos, target);
        break;
    }
    printf("Hit! ");
    printf("%d has %d hp and %d has %d hp.\n", gs->id, gs->hp, 
                                     target->id, target->hp);

    releaseGameSprite(target);
    return true;
  }
  printf("Miss!\n\n");
  return false;
}

// using speed, ready this character for another battle
void resetActionQueue(GameSprite* gs) {
  int i, numFalse;
  // clear the list
  if(gs->actions) {
    while(!isEmptyPQueue(gs->actions)) {
      dequeue(gs->actions);
    }
  }

  // rebuild the list
  numFalse = 10 - gs->speed;
  
  for(i = 1; i <= numFalse; ++i) {
    // add falses first
    enqueue(gs->actions, allocBoolWith(false));
  }

  // lastly, add true
  if(i <= 10) {
    enqueue(gs->actions, allocBoolWith(true));
  }
}

// used for calculating total hp of ally or enemy team
int sumHealth(ArrayList *list) {
  GameSprite *currentGS;
  int i, totalHP;
  totalHP = 0;
  if(list) {
    for(i = 0; i < list->length; ++i) {
      currentGS = (GameSprite *)getDArray(list, i);
      totalHP += currentGS->hp;
    }
  }

  releaseGameSprite(currentGS);
  return totalHP;
}

// determine if the battle is over or not
int checkOutcome(ArrayList* players, ArrayList* enemies) {
  // player loss
  if(sumHealth(players) == 0) {
    return -1;
  }
  // enemy loss
  else if(sumHealth(enemies) == 0) {
    return 1;
  }
  // game not over
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

void releaseGameSprite(GameSprite* gs) {
  printf("Releasing %d\n", gs->id);
  if(gs->actions) {
    releasePQueue(gs->actions);
  }
  free(gs);
}

// set HEALER, FIGHTER, or ENEMY
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

// count number of living members is group
int countAlive(ArrayList *group) {
  GameSprite *thisSprite;
  int i, numAlive = 0;

  // go through the list, looking for live members
  for(i = 0; i < group->length; ++i) {
    thisSprite = (GameSprite *)getDArray(group, i);
    if(thisSprite->hp > 0) {
      numAlive++;
    }
  }


  return numAlive;
}

// run a battle sequence
void runBattle(FILE *configuration) {
  ArrayList *allies = allocDArray(10, sizeof(GameSprite));
  ArrayList *enemies = allocDArray(10, sizeof(GameSprite));
  GameSprite *thisSprite;
  GameSprite *thisAlly;
  GameSprite *thisEnemy;
  bool action;
  uint i, input, turnCounter = 0;
  char type;

  // make a character with the input stats
  while(!feof(configuration)) {
    for(i = 0; i < 6; ++i) {
      switch(i) {
        // id
        case 0:
          fscanf(configuration, "%d", &input);
          thisSprite = allocGameSprite(input);
          printf("%d ", input);
          thisSprite->actions = allocPQueue(sizeof(bool), PQMODE_QUEUE);
          setReleasePQueue(thisSprite->actions, releasePrimitive);
          break;
        // type
        case 1:
          // double scan for space
          fscanf(configuration, "%c", &type);
          fscanf(configuration, "%c", &type);
          printf("%c ", type);
          if(type == 'E') {
            setType(thisSprite, ENEMY);
          }
          else if (type == 'H') {
            setType(thisSprite, HEALER);
          }
          else if (type == 'F') {
            setType(thisSprite, FIGHTER);
          }
          break;
        // speed
        case 2:
          fscanf(configuration, "%d", &input);
          printf("%d ", input);
          setSpeed(thisSprite, input);
          resetActionQueue(thisSprite);
          break;
        // hp
        case 3:
          fscanf(configuration, "%d", &input);
          printf("%d ", input);
          setHP(thisSprite, input);
          break;
        // strength
        case 4:
          fscanf(configuration, "%d", &input);
          printf("%d ", input);
          setStrength(thisSprite, input);
          break;
        // accuracy
        case 5:
          fscanf(configuration, "%d", &input);
          printf("%d ", input);
          setAccuracy(thisSprite, input);
          break;
      } // end switch
    } // end for

    // add the GameSprites to their appropriate teams
    if(thisSprite->type == HEALER || thisSprite->type == FIGHTER) {
      appendDArray(allies, thisSprite);
    }
    else if(thisSprite->type == ENEMY) {
      appendDArray(enemies, thisSprite);
    }
  } // end while
  fclose(configuration);
  
  // at the end of the game, report how many turns there were
  do {
    // next turn
    turnCounter++;
    printf("\n**Turn %d**\n", turnCounter);
    printf("Live players: %d, Live enemies: %d\n\n", countAlive(allies), countAlive(enemies));
    // check for action on allies side
    for(i = 0; i < allies->length; ++i) {
      thisAlly = (GameSprite *)getDArray(allies, i);
      // only proceed if this ally is alive
      if(thisAlly->hp > 0) {
        action = (bool *)front(thisAlly->actions);
        if(action == true) {
          actionProcess(getDArray(allies, i), allies, enemies);
          resetActionQueue(getDArray(allies, i));
        }
        else {
          dequeue(thisAlly->actions);
        }
      }
    }

    // check for action on enemy side
    for(i = 0; i < enemies->length; ++i) {
      thisEnemy = (GameSprite *)getDArray(enemies, i);

      // only proceed if this ally is alive
      if(thisEnemy->hp > 0) {
        action = (bool *)front(thisEnemy->actions); 
        if(action == true) {
          actionProcess(getDArray(enemies, i), allies, enemies);
          resetActionQueue(getDArray(enemies, i));
        }
        else {
          dequeue(thisEnemy->actions);
        }
      }
    }

  } while(checkOutcome(allies, enemies) == 0);
  if(sumHealth(allies) == 0) {
    printf("\nBattle lost in %d turns!\n", turnCounter);
  }
  else {
    printf("\nBattle won in %d turns!\n", turnCounter);
  }
}