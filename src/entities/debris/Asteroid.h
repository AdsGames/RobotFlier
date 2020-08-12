/*
 * Asteroid
 * Allan Legemaate
 * Collidable Asteroid
 * 11/08/2020
 */
#ifndef ENTITIES_ASTEROID_H
#define ENTITIES_ASTEROID_H

#include "Debris.h"

class Asteroid : public Debris {
 public:
  // Constructor
  Asteroid(const int x, const int y, const int theme);

  // Logic override
  virtual void onDestroy(Robot* robot) override;

 private:
  // Load assets
  void loadAssets(const int theme);

  // Sound
  Sound destroy_sound;
};

#endif  // ENTITIES_ASTEROID_H
