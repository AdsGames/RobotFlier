#include "Magnet.h"

#include "../../constants/globals.h"
#include "../../engine/Core.h"
#include "../../helpers/tools.h"

// Constructor
Magnet::Magnet(const int x, const int y, const int type) : Powerup(x, y) {
  loadAssets(type);
  setTimer(type);
}

// Load assets from manager
void Magnet::loadAssets(const int type) {
  // Load sound
  magnet_sound = Engine::asset_manager.getAudio("magnet");

  // Load image
  switch (type) {
    case 0:
      setTexture(Engine::asset_manager.getImage("powerMagnet"));
      return;
    case 1:
      setTexture(Engine::asset_manager.getImage("powerMagnetTwo"));
      return;
    case 2:
      setTexture(Engine::asset_manager.getImage("powerMagnetThree"));
      return;
    case 3:
      setTexture(Engine::asset_manager.getImage("powerMagnetFour"));
      return;
    default:
      return;
  }
}

// Set timer length
void Magnet::setTimer(const int type) {
  switch (type) {
    case 0:
      setTimerLength(500);
      return;
    case 1:
      setTimerLength(750);
      return;
    case 2:
      setTimerLength(1000);
      return;
    case 3:
      setTimerLength(1500);
      return;
    default:
      return;
  }
}

// Logic loop!
void Magnet::logic(const int motion, Robot* robot) {
  x -= motion;

  if (!isDead && collision(x, x + width, robot->getX(),
                           robot->getX() + robot->getWidth(), y, y + height,
                           robot->getY(), robot->getY() + robot->getHeight())) {
    stats[STAT_POWERUPS] += 1;

    robot->setMagneticTimer(getTimerLength());

    magnet_sound.play();

    isDead = true;
  }
}
