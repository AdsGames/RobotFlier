/*
 * Magnet
 * Allan Legemaate
 * Magnet type powerup
 * 11/08/2020
 */
#ifndef SRC_ENTITIES_POWERUPS_POWERSTAR_H_
#define SRC_ENTITIES_POWERUPS_POWERSTAR_H_

#include "Powerup.h"

#include <afk/assets/Sound.h>

class PowerStar : public Powerup {
 public:
  // Constructor
  PowerStar(afk::Scene& scene, const float x, const float y);

  // Logic override
  void update(Uint32 delta) override;

  void onCollide(const GameObject& other) override;
};

#endif  // SRC_ENTITIES_POWERUPS_POWERSTAR_H_
