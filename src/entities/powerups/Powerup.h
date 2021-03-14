/*
 * Powerup
 * Various powerups do various things
 * A.D.S. Games
 */
#ifndef SRC_ENTITIES_POWERUPS_POWERUP_H_
#define SRC_ENTITIES_POWERUPS_POWERUP_H_

#include <afk/entities/Sprite.h>

class Powerup : public afk::Sprite {
 public:
  // Constructor
  Powerup(afk::Scene& scene, const float x, const float y, const int z);

  void setTimerLength(const int length);
  int getTimerLength();

 private:
  // Length to apply powerup
  int timer_length;
};

#endif  // SRC_ENTITIES_POWERUPS_POWERUP_H_
