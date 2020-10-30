#include "PowerStar.h"

#include "../../constants/globals.h"
#include "../../engine/Core.h"
#include "../../helpers/tools.h"
#include "../Robot.h"

// Constructor
PowerStar::PowerStar(const Scene& scene, const int x, const int y)
    : Powerup(scene, x, y) {
  loadAssets();
  setTimerLength(500);
}

// Load assets from manager
void PowerStar::loadAssets() {
  // Load sound
  power_star_sound = Engine::asset_manager.getAudio("star");

  // Load image
  setTexture("powerStar");
}

void PowerStar::onCollide(const GameObject& other) {
  try {
    auto robot = dynamic_cast<const Robot&>(other);
    stats[STAT_POWERUPS] += 1;
    robot.setInvincibleTimer(getTimerLength());
    power_star_sound.play();
    isDead = true;
  } catch (...) {
    // Nope!
  }
}

// Logic loop!
void PowerStar::update() {
  x -= motion;
}
