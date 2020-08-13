/*
 * Debris
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef ENTITIES_DEBRIS_DEBRIE_H
#define ENTITIES_DEBRIS_DEBRIE_H

#include "../GameObject.h"

class Debris : public GameObject {
 public:
  // Constructor
  Debris(const int x,
         const int y,
         const int damage,
         const float motionMultiplier,
         const float acceleration,
         const int size = -1);

  // On destroy
  virtual void onDestroy(Robot* robot) = 0;

  // Logic override
  void logic(const int motion, Robot* robot);

 private:
  // Motion multiplier
  float motionMultiplier;
  float acceleration;
};

#endif  // ENTITIES_DEBRIS_DEBRIE_H
