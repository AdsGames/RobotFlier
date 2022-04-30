/*
 * Debris
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef SRC_ENTITIES_DEBRIS_DEBRIS_H_
#define SRC_ENTITIES_DEBRIS_DEBRIS_H_

#include <afk/entities/Sprite.h>

class Debris : public afk::Sprite {
 public:
  // Constructor
  Debris(afk::Scene& scene,
         const float x,
         const float y,
         const int z,
         const int damage,
         const float motionMultiplier,
         const float acceleration,
         const int size = -1);

  // On destroy
  virtual void onDestroy() = 0;

  // Logic override
  void update(Uint32 delta) override;

  void destroy();

 private:
  // Motion multiplier
  float motionMultiplier;
  float acceleration;

  int damage;
};

#endif  // SRC_ENTITIES_DEBRIS_DEBRIS_H_
