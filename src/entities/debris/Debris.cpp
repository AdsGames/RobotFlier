#include "Debris.h"

#include <afk/random/RandomGenerator.h>
#include <afk/scene/Scene.h>
#include "../../constants/globals.h"

// Constructor
Debris::Debris(Scene& scene,
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
void Debris::update() {
  // Update particles
  if (scene.getSettings().get<int>("particleType", 0) != 3) {
    for (unsigned int i = 0; i < parts.size(); i++) {
      parts.at(i).update();
      parts.at(i).scroll(motion, 0.0f);
    }
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
  if (scene.getSettings().get<int>("particleType", 0) != 3) {
    // Sample a pixel
    ALLEGRO_COLOR sample_color =
        texture.getPixel(texture.getWidth() / 2, texture.getHeight() / 2);

    // Make some particles
    int sampling_size = 5;

    for (int i = 0; i < (width - sampling_size); i += sampling_size) {
      for (int t = 0; t < (height - sampling_size); t += sampling_size) {
        Particle newParticle(i + x, t + y, sample_color,
                             RandomGenerator::randomInt(-8, 8),
                             RandomGenerator::randomInt(-8, 8), 1,
                             scene.getSettings().get<int>("particleType", 0));
        parts.push_back(newParticle);
      }
    }
  }
}