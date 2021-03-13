/*
 * Asteroid
 * Allan Legemaate
 * Collidable Asteroid
 * 11/08/2020
 */
#ifndef SRC_ENTITIES_DEBRIS_ASTEROID_H_
#define SRC_ENTITIES_DEBRIS_ASTEROID_H_

#include "Debris.h"

#include <afk/assets/Sound.h>

class Asteroid : public Debris {
 public:
  // Constructor
  Asteroid(afk::Scene& scene, const float x, const float y, const int theme);

  // Logic override
  void onDestroy() override;

 private:
  // Load assets
  void loadAssets(const int theme);
};

#endif  // SRC_ENTITIES_DEBRIS_ASTEROID_H_
