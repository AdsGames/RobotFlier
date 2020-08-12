/*
 * Magnet
 * Allan Legemaate
 * Magnet type powerup
 * 11/08/2020
 */
#ifndef ENTITIES_POWER_STAR_H
#define ENTITIES_POWER_STAR_H

#include "Powerup.h"

class PowerStar : public Powerup {
 public:
  // Constructor
  PowerStar(const int x, const int y);

  // Logic override
  virtual void logic(const int motion, Robot* robot) override;

 private:
  // Load assets
  void loadAssets();

  // Sound
  Sound power_star_sound;
};

#endif  // ENTITIES_POWER_STAR_H
