#include "Debris.h"

#include <afk/random/RandomGenerator.h>
#include <afk/scene/Scene.h>
#include <afk/services/Services.h>

#include "../../constants/globals.h"

// Constructor
Debris::Debris(afk::Scene& scene,
               const float x,
               const float y,
               const int damage,
               const float motionMultiplier,
               const float acceleration,
               const int size)
    : Sprite(scene, x, y) {
  if (size != -1) {
    height = size * 8;
    width = size * 10;
  }

  this->motionMultiplier = motionMultiplier;
  this->damage = damage;
  this->acceleration = acceleration;
}

// Logic
void Debris::update(Uint32 delta) {
  // Update particles
  if (scene.config.get<int>("particleType", 0) != 3) {
    // for (unsigned int i = 0; i < parts.size(); i++) {
    //   parts.at(i).update(Uint32 delta);
    //   parts.at(i).scroll(motion, 0.0f);
    // }
  }

  // Move across screen
  x -= motion * motionMultiplier;
  motionMultiplier += acceleration;
}

void Debris::destroy() {
  // Shake it up
  screenshake += damage * 4;

  // Get hit
  scene.remove(getId());
  stats[STAT_DEBRIS] += 1;

  // Make particles
  if (scene.config.get<int>("particleType", 0) != 3) {
    // Sample a pixel
    // afk::color::Color sample_color =
    //     texture.getPixel(texture.getWidth() / 2, texture.getHeight() / 2);

    // // Make some particles
    // int sampling_size = 5;

    // for (int i = 0; i < (width - sampling_size); i += sampling_size) {
    //   for (int t = 0; t < (height - sampling_size); t += sampling_size) {
    //     afk::Particle newParticle(i + x, t + y, sample_color,
    //                               afk::Random::randomInt(-8, 8),
    //                               afk::Random::randomInt(-8, 8), 1,
    //                               config.get<int>("particleType", 0));
    //     parts.push_back(newParticle);
    //   }
    // }
  }
}
