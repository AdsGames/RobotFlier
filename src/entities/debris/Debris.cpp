#include "Debris.h"

#include "../../constants/globals.h"
#include "../../engine/Core.h"
#include "../../helpers/tools.h"

// Constructor
Debris::Debris(const int x,
               const int y,
               const int damage,
               const float motionMultiplier,
               const float acceleration,
               const int size)
    : GameObject(x, y) {
  if (size != -1) {
    height = size * 8;
    width = size * 10;
  }

  this->motionMultiplier = motionMultiplier;
  this->damage = damage;
  this->acceleration = acceleration;
}

// Logic
void Debris::logic(const int motion, Robot* robot) {
  // Move across screen
  x -= motion * motionMultiplier;
  motionMultiplier += acceleration;

  // Allow for some padding (since we use bounding box)
  const int collisionBuffer = height / 3;

  // Collide with robot
  if (!isDead && !robot->isInvincible() &&
      collision(x, x + width, robot->getX() + collisionBuffer,
                robot->getX() + robot->getWidth() - collisionBuffer, y,
                y + height, robot->getY() + collisionBuffer,
                robot->getY() + robot->getHeight() - collisionBuffer)) {
    // Hurt robot
    robot->addHealth(-damage);

    // Shake it up
    screenshake += damage * 4;

    // Get hit
    isDead = true;
    stats[STAT_DEBRIS] += 1;

    // Make particles
    if (Engine::settings.get<int>("particleTypes", 0) != 3) {
      // Sample a pixel
      ALLEGRO_COLOR sample_color =
          texture.getPixel(texture.getWidth() / 2, texture.getHeight() / 2);

      // Make some particles
      int sampling_size = 5;

      for (int i = 0; i < (width - sampling_size); i += sampling_size) {
        for (int t = 0; t < (height - sampling_size); t += sampling_size) {
          Particle newParticle(i + x, t + y, sample_color,
                               Engine::random.randomInt(-8, 8),
                               Engine::random.randomInt(-8, 8), 1,
                               Engine::settings.get<int>("particleType", 0));
          parts.push_back(newParticle);
        }
      }
    }
  }

  // Parent logic
  GameObject::logic(motion);
}
