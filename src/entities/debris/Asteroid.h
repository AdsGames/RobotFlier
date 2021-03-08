/*
 * Asteroid
 * Allan Legemaate
 * Collidable Asteroid
 * 11/08/2020
 */
#ifndef ENTITIES_DEBRIS_ASTEROID_H
#define ENTITIES_DEBRIS_ASTEROID_H

#include "Debris.h"

#include <afk/assets/Sound.h>

class Asteroid : public Debris {
 public:
  // Constructor
  Asteroid(afk::Scene& scene, const float x, const float y, const int theme);

  // Logic override
  virtual void onDestroy() override;

 private:
  // Load assets
  void loadAssets(const int theme);

  // Sound
  afk::Sound destroy_sound;
};

#endif  // ENTITIES_DEBRIS_ASTEROID_H
