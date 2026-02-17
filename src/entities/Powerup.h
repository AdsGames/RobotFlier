/*
 * Powerup
 * Various powerups do various things
 * A.D.S. Games
 */
#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

#include <asw/asw.h>

class Powerup : public GameObject {
 public:
  // Constructor
  Powerup(asw::Texture sprite,
          asw::Sample  sound,
          const int    x,
          const int    y,
          const int    timerLength,
          const int    type);

  // Logic override
  void logic(const int motion, Robot* robot, float deltaTime);

  // Vars
  int timerLength;
  int type;

 private:
  asw::Sample sound;
};

#endif
