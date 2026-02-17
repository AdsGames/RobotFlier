#include "Powerup.h"

// Constructor
Powerup::Powerup(asw::Texture            sprite,
                 asw::Sample             sound,
                 const asw::Vec2<float>& position,
                 int                     timerLength,
                 const int               type)
    : GameObject(sprite, position) {
  this->timerLength = timerLength;
  this->type        = type;
  this->sound       = sound;
}

// Logic loop!
void Powerup::logic(const float motion, Robot* robot) {
  transform.position.x -= motion;

  if (!isDead && transform.collides(robot->getTransform())) {
    stats[STAT_POWERUPS] += 1;

    if (type == 1) {
      robot->setInvincibleTimer(timerLength);
    } else {
      robot->setMagneticTimer(timerLength);
    }

    asw::sound::play(sound);

    isDead = true;
  }
}
