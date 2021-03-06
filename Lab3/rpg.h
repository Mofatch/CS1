#ifndef RPG_H_
#define RPG_H_

#include "Objects.c"

typedef enum SpriteType {
  FIGHTER,
  HEALER,
  ENEMY
} SType;
typedef struct _GameSprite {
  SType type;
  uint id;        // unique identifier for character
  PQueue *actions;// stores booleans (false = nothing, true = attack)
  uint speed;     // value in [0,10] 10-speed = num of false before a true
  uint hp;        // life points. [50, 200] allies, 1000 enemies
  uint strength;  // healer: hp restored, fighter: dmg done
  uint accuracy;  // probability of a hit

} GameSprite;

bool actionProcess(GameSprite*, ArrayList*, ArrayList*);
void resetActionQueue(GameSprite*);
void runBattle(FILE*);
int checkOutcome(ArrayList*, ArrayList*);
GameSprite* allocGameSprite(uint);
void releaseGameSprite(GameSprite*);
void setType(GameSprite*, SType);
void setSpeed(GameSprite*, uint);
void setHP(GameSprite*, uint);
void setStrength(GameSprite*, uint);
void setAccuracy(GameSprite*, uint);
int countAlive(ArrayList*);

#endif /* RPG_H_ */