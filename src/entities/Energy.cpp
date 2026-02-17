#include "Energy.h"

// Constructor
Energy::Energy(asw::Texture sprite, asw::Sample sound, const int x, const int y)
    : GameObject(sprite, x, y) {
  this->sound = sound;
}

// Game logic
void Energy::logic(const int motion, Robot* robot) {
  x -= motion;

  if (!isDead && collision(x, x + width, robot->getX(),
                           robot->getX() + robot->getWidth(), y, y + height,
                           robot->getY(), robot->getY() + robot->getHeight())) {
    score += 5;
    stats[STAT_ENERGY] += 1;

    if (robot->getHealth() < 100)
      robot->addHealth(1);

    if (settings[SETTING_SOUND]) {
      asw::sound::play(sound);
    }

    isDead = true;
  }
}

// Move towards robot
void Energy::move_towards(const float x, const float y, const float speed) {
  this->x += (speed * (x - this->x)) / 20000;
  this->y += (speed * (y - this->y)) / 20000;
}
