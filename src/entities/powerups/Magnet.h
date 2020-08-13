/*
 * Magnet
 * Allan Legemaate
 * Magnet type powerup
 * 11/08/2020
 */
#ifndef ENTITIES_POWERUPS_MAGNET_H
#define ENTITIES_POWERUPS_MAGNET_H

#include "Powerup.h"

class Magnet : public Powerup {
 public:
  // Constructor
  Magnet(const int x, const int y, const int type);

  // Logic override
  virtual void logic(const int motion, Robot* robot) override;

 private:
  // Load assets
  void loadAssets(const int type);

  // Set timer
  void setTimer(const int type);

  // Type of magnet
  int magnetType;

  // Sound
  Sound magnet_sound;
};

#endif  // ENTITIES_POWERUPS_MAGNET_H
