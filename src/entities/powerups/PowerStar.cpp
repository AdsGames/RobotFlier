#include "PowerStar.h"

#include "../../constants/globals.h"
#include "../../engine/Core.h"
#include "../../helpers/tools.h"

// Constructor
PowerStar::PowerStar(const int x, const int y) : Powerup(x, y) {
  loadAssets();
  setTimerLength(500);
}

// Load assets from manager
void PowerStar::loadAssets() {
  // Load sound
  power_star_sound = Engine::asset_manager.getAudio("star");

  // Load image
  setTexture(Engine::asset_manager.getImage("powerStar"));
}

// Logic loop!
void PowerStar::logic(const int motion, Robot* robot) {
  x -= motion;

  if (!isDead && collision(x, x + width, robot->getX(),
                           robot->getX() + robot->getWidth(), y, y + height,
                           robot->getY(), robot->getY() + robot->getHeight())) {
    stats[STAT_POWERUPS] += 1;

    robot->setInvincibleTimer(getTimerLength());

    power_star_sound.play();

    isDead = true;
  }
}
