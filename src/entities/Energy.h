/*
 * Energy
 * Gives the player health
 * A.D.S. Games
 */
#ifndef ENTITIES_ENERGY_H
#define ENTITIES_ENERGY_H

#include "../engine/Audio/Sound.h"
#include "GameObject.h"

class Energy : public GameObject {
 public:
  // Constructor
  Energy(const int x, const int y);

  // Logic override
  void logic(const int motion, Robot* robot);

  // Move towards point
  void moveTowards(const float x, const float y, const float speed);

 private:
  // Load assets
  void loadAssets();

  // Sound effect
  Sound sound_orb;
};

#endif  // ENTITIES_ENERGY_H
