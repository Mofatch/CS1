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
  Queue *actions; // stores booleans (false = nothing, true = attack)
  uint speed;     // value in [0,10] 10-speed = num of false before a true
  uint hp;        // life points. [50, 200] allies, 1000 enemies
  uint strength;  // healer: hp restored, fighter: dmg done
  uint accuracy;  // probability of a hit

} GameSprite;

bool actionProcess(GameSprite*, ArrayList*, ArrayList*);
void resetActionQueue(GameSprite*);
void runBattle(FILE*);
int checkOutcome(ArrayList*, ArrayList*);

#endif /* RPG_H_ */