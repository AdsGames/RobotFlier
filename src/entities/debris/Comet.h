/*
 * Comet
 * Allan Legemaate
 * Collidable Comet
 * 11/08/2020
 */
#ifndef ENTITIES_DEBRIS_COMET_H
#define ENTITIES_DEBRIS_COMET_H

#include "Debris.h"

#include <afk/assets/Sound.h>

class Comet : public Debris {
 public:
  // Constructor
  Comet(afk::Scene& scene, const float x, const float y);

  // Logic override
  virtual void onDestroy() override;

  void onCollide(const GameObject& other) override;

 private:
  // Sound
  afk::Sound destroy_sound;
};

#endif  // ENTITIES_DEBRIS_COMET_H
