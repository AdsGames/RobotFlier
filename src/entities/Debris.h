/*
 * Debris
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef DEBRIE_H
#define DEBRIE_H

#include "./GameObject.h"

class Debris : public GameObject {
 public:
  // Constructor
  Debris(asw::Texture            sprite,
         asw::Sample             sound,
         const asw::Vec2<float>& position,
         const int               damage,
         const float             motionMultiplier = 1.0f,
         const float             acceleration     = 0.0f,
         const int               size             = -1);

  // Logic override
  void logic(const int motion, Robot* robot, float deltaTime);

 private:
  // Motion multiplier
  float motionMultiplier;
  float acceleration;

  // Sound
  asw::Sample sound;
};

#endif
