#include "Powerup.h"

// Constructor
Powerup::Powerup(asw::Texture sprite,
                 asw::Sample  sound,
                 const int    x,
                 const int    y,
                 int          timerLength,
                 const int    type)
    : GameObject(sprite, x, y) {
  this->timerLength = timerLength;
  this->type        = type;
  this->sound       = sound;
}

// Logic loop!
void Powerup::logic(const int motion, Robot* robot, float deltaTime) {
  x -= motion;

  if (!isDead && collision(x, x + width, robot->getX(),
                           robot->getX() + robot->getWidth(), y, y + height,
                           robot->getY(), robot->getY() + robot->getHeight())) {
    stats[STAT_POWERUPS] += 1;

    if (type == 1)
      robot->setInvincibleTimer(timerLength);
    else
      robot->setMagneticTimer(timerLength);

    if (settings[SETTING_SOUND]) {
      asw::sound::play(sound);
    }

    isDead = true;
  }
}
