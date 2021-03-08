/*
 * Bomb
 * Allan Legemaate
 * Collidable Bomb
 * 11/08/2020
 */
#ifndef ENTITIES_DEBRIS_BOMB_H
#define ENTITIES_DEBRIS_BOMB_H

#include "Debris.h"

#include <afk/assets/Sound.h>

class Bomb : public Debris {
 public:
  // Constructor
  Bomb(afk::Scene& scene, const float x, const float y);

  // Logic override
  virtual void onDestroy() override;

 private:
  // Sound
  afk::Sound destroy_sound;
};

#endif  // ENTITIES_DEBRIS_BOMB_H
