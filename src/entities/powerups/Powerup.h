/*
 * Powerup
 * Various powerups do various things
 * A.D.S. Games
 */
#ifndef ENTITIES_POWERUPS_POWERUP_H
#define ENTITIES_POWERUPS_POWERUP_H

#include "../GameObject.h"

class Powerup : public GameObject {
 public:
  // Constructor
  Powerup(Scene* scene, const int x, const int y);

  void setTimerLength(const int length);
  int getTimerLength();

 private:
  // Length to apply powerup
  int timer_length;
};

#endif  // ENTITIES_POWERUPS_POWERUP_H
