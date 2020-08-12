#include "Energy.h"

#include "../constants/globals.h"
#include "../engine/Core.h"
#include "../helpers/tools.h"

// Constructor
Energy::Energy(const int x, const int y) : GameObject(x, y) {
  loadAssets();
}

void Energy::loadAssets() {
  if (Engine::settings.get<bool>("christmas", false)) {
    setTexture(Engine::asset_manager.getImage("energy_christmas"));
  } else {
    setTexture(Engine::asset_manager.getImage("energy"));
  }

  sound_orb = Engine::asset_manager.getAudio("orb");
}

// Game logic
void Energy::logic(const int motion, Robot* robot) {
  x -= motion;

  if (!isDead && collision(x, x + width, robot->getX(),
                           robot->getX() + robot->getWidth(), y, y + height,
                           robot->getY(), robot->getY() + robot->getHeight())) {
    score += 5;
    stats[STAT_ENERGY] += 1;

    if (robot->getHealth() < 100) {
      robot->addHealth(1);
    }

    sound_orb.play();

    isDead = true;
  }
}

// Move towards robot
void Energy::moveTowards(const float x, const float y, const float speed) {
  this->x += (speed * (x - this->x)) / 20000;
  this->y += (speed * (y - this->y)) / 20000;
}
