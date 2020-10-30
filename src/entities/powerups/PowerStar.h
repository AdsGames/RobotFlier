/*
 * Magnet
 * Allan Legemaate
 * Magnet type powerup
 * 11/08/2020
 */
#ifndef ENTITIES_POWERUPS_POWER_STAR_H
#define ENTITIES_POWERUPS_POWER_STAR_H

#include "Powerup.h"

class PowerStar : public Powerup {
 public:
  // Constructor
  PowerStar(Scene* scene, const int x, const int y);

  // Logic override
  virtual void update() override;

  void onCollide(const GameObject& other) override;

 private:
  // Load assets
  void loadAssets();

  // Sound
  Sound power_star_sound;
};

#endif  // ENTITIES_POWERUPS_POWER_STAR_H
