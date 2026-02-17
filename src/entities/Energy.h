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
  Energy(asw::Texture            sprite,
         asw::Sample             sound,
         const asw::Vec2<float>& position);

  // Logic override
  void logic(const int motion, Robot* robot);

  // Move towards robot
  void move_towards(const asw::Vec2<float>& target, const float speed);

 private:
  // Sound effect
  asw::Sample sound;
};

#endif
