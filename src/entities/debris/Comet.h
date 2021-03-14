/*
 * Comet
 * Allan Legemaate
 * Collidable Comet
 * 11/08/2020
 */
#ifndef SRC_ENTITIES_DEBRIS_COMET_H_
#define SRC_ENTITIES_DEBRIS_COMET_H_

#include "Debris.h"

#include <afk/assets/Sound.h>

class Comet : public Debris {
 public:
  // Constructor
  Comet(afk::Scene& scene, const float x, const float y, const int z);

  // Logic override
  void onDestroy() override;

  void onCollide(GameObject& other) override;
};

#endif  // SRC_ENTITIES_DEBRIS_COMET_H_
