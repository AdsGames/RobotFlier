/*
 * Powerup
 * Various powerups do various things
 * A.D.S. Games
 */
#ifndef ENTITIES_POWERUPS_POWERUP_H
#define ENTITIES_POWERUPS_POWERUP_H

#include <afk/entities/Sprite.h>

class Powerup : public afk::Sprite {
 public:
  // Constructor
  Powerup(afk::Scene& scene, const float x, const float y);

  void setTimerLength(const int length);
  int getTimerLength();

 private:
  // Length to apply powerup
  int timer_length;
};

#endif  // ENTITIES_POWERUPS_POWERUP_H
