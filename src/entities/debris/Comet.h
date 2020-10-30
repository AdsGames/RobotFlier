/*
 * Comet
 * Allan Legemaate
 * Collidable Comet
 * 11/08/2020
 */
#ifndef ENTITIES_DEBRIS_COMET_H
#define ENTITIES_DEBRIS_COMET_H

#include "Debris.h"

#include "../../engine/audio/Sound.h"

class Comet : public Debris {
 public:
  // Constructor
  Comet(const Scene& scene, const int x, const int y);

  // Logic override
  virtual void onDestroy() override;

  void onCollide(const GameObject& other) override;

 private:
  // Sound
  Sound destroy_sound;
};

#endif  // ENTITIES_DEBRIS_COMET_H
