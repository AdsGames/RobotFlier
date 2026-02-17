/*
 * Energy
 * Gives the player health
 * A.D.S. Games
 */
#ifndef ENERGY_H
#define ENERGY_H

#include "GameObject.h"

class Energy : public GameObject {
 public:
  // Constructor
  Energy(asw::Texture sprite, asw::Sample sound, const int x, const int y);

  // Logic override
  void logic(const int motion, Robot* robot);

  // Move towards robot
  void move_towards(const float x, const float y, const float speed);

 private:
  // Sound effect
  asw::Sample sound;
};

#endif
