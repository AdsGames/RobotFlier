#include "Debris.h"

#include <allegro5/allegro_audio.h>

#include "../constants/globals.h"
#include "../engine/Core.h"

// Constructor
Debris::Debris(ALLEGRO_BITMAP* sprite,
               ALLEGRO_SAMPLE* sound,
               const int x,
               const int y,
               const int damage,
               const float motionMultiplier,
               const float acceleration,
               const int size)
    : GameObject(sprite, x, y) {
  if (size != -1) {
    height = size * 8;
    width = size * 10;
  }

  this->sound = sound;
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
                robot->getY() + robot->getHeight() - collisionBuffer) &&
      !isDead) {
    // Hurt robot
    robot->addHealth(-damage);

    // Shake it up
    screenshake += damage * 4;

    // Play sound
    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);

    // Get hit
    isDead = true;
    stats[STAT_DEBRIS] += 1;

    // Make particles
    if (Engine::settings.get<int>("particleTypes", 0) != 3) {
      // Sample a pixel
      ALLEGRO_COLOR sample_color =
          al_get_pixel(sprite, al_get_bitmap_width(sprite) / 2,
                       al_get_bitmap_height(sprite) / 2);

      // Make some particles
      int sampling_size = 5;

      for (int i = 0; i < (width - sampling_size); i += sampling_size) {
        for (int t = 0; t < (height - sampling_size); t += sampling_size) {
          Particle newParticle(i + x, t + y, sample_color, random(-8, 8),
                               random(-8, 8), 1,
                               Engine::settings.get<int>("particleType", 0));
          parts.push_back(newParticle);
        }
      }
    }
  }

  // Parent logic
  GameObject::logic(motion);
}
