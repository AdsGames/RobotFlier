#include "Debris.h"

// Constructor
Debris::Debris(asw::Texture            sprite,
               asw::Sample             sound,
               const asw::Vec2<float>& position,
               const int               damage,
               const float             motionMultiplier,
               const float             acceleration,
               const int               size)
    : GameObject(sprite, position) {
  if (size != -1) {
    transform.size.y = size * 8;
    transform.size.x = size * 10;
  }

  this->sound            = sound;
  this->motionMultiplier = motionMultiplier;
  this->damage           = damage;
  this->acceleration     = acceleration;
}

// Logic
void Debris::logic(const float motion, Robot* robot, float deltaTime) {
  // Move across screen
  transform.position.x -= motion * motionMultiplier;
  motionMultiplier += acceleration;

  // Allow for some padding (since we use bounding box)
  const auto collisionBuffer = transform.size.y / 3.0F;

  // Collide with robot
  const auto offset =
      asw::Quad<float>(collisionBuffer, collisionBuffer,
                       -collisionBuffer * 2.0F, -collisionBuffer * 2.0F);

  if (!isDead && !robot->isInvincible() &&
      transform.collides(robot->getTransform() + offset) && !isDead) {
    // Hurt robot
    robot->addHealth(-damage);

    // Shake it up
    screenshake += damage * 4;

    // Play sound
    asw::sound::play(sound);

    // Get hit
    isDead = true;
    stats[STAT_DEBRIS] += 1;

    // Make particles
    if (settings.particlesEnabled()) {
      // Sample a pixel
      auto sample_color =
          asw::Color(0, 0, 0);  // al_get_pixel(sprite,
                                // al_get_bitmap_width(sprite) / 2,
                                //  al_get_bitmap_height(sprite) / 2);

      // Make some particles
      int sampling_size = 5;

      for (int i = 0; i < (transform.size.x - sampling_size);
           i += sampling_size) {
        for (int t = 0; t < (transform.size.y - sampling_size);
             t += sampling_size) {
          Particle newParticle(transform.position + asw::Vec2<float>(i, t),
                               sample_color,
                               asw::Vec2<float>(asw::random::between(-8, 8),
                                                asw::random::between(-8, 8)),
                               1, settings.particleType);

          parts.push_back(newParticle);
        }
      }
    }
  }

  // Parent logic
  GameObject::logic(motion, deltaTime);
}
