/*
 * Bomb
 * Allan Legemaate
 * Collidable Bomb
 * 11/08/2020
 */
#ifndef ENTITIES_BOMB_H
#define ENTITIES_BOMB_H

#include "Debris.h"

class Bomb : public Debris {
 public:
  // Constructor
  Bomb(const int x, const int y);

  // Logic override
  virtual void onDestroy(Robot* robot) override;

 private:
  // Sound
  Sound destroy_sound;
};

#endif  // ENTITIES_BOMB_H
