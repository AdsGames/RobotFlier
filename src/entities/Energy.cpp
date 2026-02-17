#include "Energy.h"

// Constructor
Energy::Energy(asw::Texture            sprite,
               asw::Sample             sound,
               const asw::Vec2<float>& position)
    : GameObject(sprite, position) {
  this->sound = sound;
}

// Game logic
void Energy::logic(const float motion, Robot* robot) {
  transform.position.x -= motion;

  if (!isDead && transform.collides(robot->getTransform())) {
    score += 5;
    stats[STAT_ENERGY] += 1;

    if (robot->getHealth() < 100) {
      robot->addHealth(1);
    }

    asw::sound::play(sound);

    isDead = true;
  }
}

// Move towards robot
void Energy::move_towards(const asw::Vec2<float>& target, const float speed) {
  transform.position.x += (speed * (target.x - transform.position.x)) / 20000;
  transform.position.y += (speed * (target.y - transform.position.y)) / 20000;
}
