/*
 * Bomb
 * Allan Legemaate
 * Collidable Bomb
 * 11/08/2020
 */
#ifndef SRC_ENTITIES_DEBRIS_BOMB_H_
#define SRC_ENTITIES_DEBRIS_BOMB_H_

#include "Debris.h"

#include <afk/assets/Sound.h>

class Bomb : public Debris {
 public:
  // Constructor
  Bomb(afk::Scene& scene, const float x, const float y, const int z);

  // Logic override
  void onDestroy() override;
};

#endif  // SRC_ENTITIES_DEBRIS_BOMB_H_
