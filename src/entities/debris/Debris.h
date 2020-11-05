/*
 * Debris
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef ENTITIES_DEBRIS_DEBRIE_H
#define ENTITIES_DEBRIS_DEBRIE_H

#include "../../engine/entities/Sprite.h"

class Debris : public Sprite {
 public:
  // Constructor
  Debris(Scene& scene,
         const float x,
         const float y,
         const int damage,
         const float motionMultiplier,
         const float acceleration,
         const int size = -1);

  // On destroy
  virtual void onDestroy() = 0;

  // Logic override
  virtual void update() override;

  void destroy();

 private:
  // Motion multiplier
  float motionMultiplier;
  float acceleration;

  int damage;
};

#endif  // ENTITIES_DEBRIS_DEBRIE_H
