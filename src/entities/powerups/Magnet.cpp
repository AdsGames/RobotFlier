#include "Magnet.h"

#include <afk/scene/Scene.h>

#include "../../constants/globals.h"
#include "../Robot.h"

// Constructor
Magnet::Magnet(afk::Scene& scene, const float x, const float y, const int z, const int type)
    : Powerup(scene, x, y, z) {
  loadAssets(type);
  setTimer(type);
}

// Load assets from manager
void Magnet::loadAssets(const int type) {
  // Load image
  switch (type) {
    case 0:
      setTexture("powerMagnet");
      return;
    case 1:
      setTexture("powerMagnetTwo");
      return;
    case 2:
      setTexture("powerMagnetThree");
      return;
    case 3:
      setTexture("powerMagnetFour");
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

void Magnet::onCollide(GameObject& other) {
  try {
    auto robot = dynamic_cast<Robot&>(other);
    robot.setMagneticTimer(getTimerLength());
    stats[STAT_POWERUPS] += 1;
    scene.audio.playSound("magnet");
    scene.remove(id);
  } catch (...) {
    // Nope!
  }
}

// Logic loop!
void Magnet::update(Uint32 delta) {
  x -= motion * delta;

  if (x + width <= 0) {
    scene.remove(id);
  }
}
