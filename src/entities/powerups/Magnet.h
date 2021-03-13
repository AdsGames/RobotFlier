/*
 * Magnet
 * Allan Legemaate
 * Magnet type powerup
 * 11/08/2020
 */
#ifndef SRC_ENTITIES_POWERUPS_MAGNET_H_
#define SRC_ENTITIES_POWERUPS_MAGNET_H_

#include "Powerup.h"

#include <afk/assets/Sound.h>

class Magnet : public Powerup {
 public:
  // Constructor
  Magnet(afk::Scene& scene, const float x, const float y, const int type);

  // Logic override
  void update(Uint32 delta) override;

  void onCollide(const GameObject& other) override;

 private:
  // Load assets
  void loadAssets(const int type);

  // Set timer
  void setTimer(const int type);
};

#endif  // SRC_ENTITIES_POWERUPS_MAGNET_H_
