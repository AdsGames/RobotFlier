#include "Debris.h"

#include <afk/random/RandomGenerator.h>
#include <afk/scene/Scene.h>

#include "../../constants/globals.h"

// Constructor
Debris::Debris(afk::Scene& scene,
               const float x,
               const float y,
               const int z,
               const int damage,
               const float motionMultiplier,
               const float acceleration,
               const int size)
    : Sprite(scene, x, y, z),
      motionMultiplier(motionMultiplier),
      acceleration(acceleration),
      damage(damage) {
  if (size != -1) {
    height = size * 8;
    width = size * 10;
  }
}

// Logic
void Debris::update(Uint32 delta) {
  // Move across screen
  x -= motion * delta * motionMultiplier;
  motionMultiplier += acceleration;
}

void Debris::destroy() {
  // Shake it up
  screenshake += damage * 4;

  // Get hit
  scene.remove(id);
  stats[STAT_DEBRIS] += 1;
}
