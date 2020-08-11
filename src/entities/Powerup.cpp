#include "Powerup.h"

#include <allegro5/allegro_audio.h>

#include "../constants/globals.h"
#include "../engine/Core.h"

// Constructor
Powerup::Powerup(ALLEGRO_BITMAP* sprite,
                 ALLEGRO_SAMPLE* sound,
                 const int x,
                 const int y,
                 int timerLength,
                 const int type)
    : GameObject(sprite, x, y) {
  this->timerLength = timerLength;
  this->type = type;
  this->sound = sound;
}

// Logic loop!
void Powerup::logic(const int motion, Robot* robot) {
  x -= motion;

  if (!isDead && collision(x, x + width, robot->getX(),
                           robot->getX() + robot->getWidth(), y, y + height,
                           robot->getY(), robot->getY() + robot->getHeight())) {
    stats[STAT_POWERUPS] += 1;

    if (type == 1)
      robot->setInvincibleTimer(timerLength);
    else
      robot->setMagneticTimer(timerLength);

    al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);

    isDead = true;
  }
}
