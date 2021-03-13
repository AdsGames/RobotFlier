#include "PowerStar.h"

#include <afk/scene/Scene.h>

#include "../../constants/globals.h"
#include "../Robot.h"

// Constructor
PowerStar::PowerStar(afk::Scene& scene, const float x, const float y)
    : Powerup(scene, x, y) {
  setTexture("powerStar");
  setTimerLength(500);
}

void PowerStar::onCollide(const GameObject& other) {
  try {
    auto robot = dynamic_cast<const Robot&>(other);
    stats[STAT_POWERUPS] += 1;
    robot.setInvincibleTimer(getTimerLength());
    scene.audio.playSound("star");
    scene.remove(id);
  } catch (...) {
    // Nope!
  }
}

// Logic loop!
void PowerStar::update(Uint32 delta) {
  x -= motion;

  if (x + width <= 0) {
    scene.remove(id);
  }
}
