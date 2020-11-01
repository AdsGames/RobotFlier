#include "PowerStar.h"

#include "../../constants/globals.h"
#include "../../engine/scene/Scene.h"
#include "../../helpers/tools.h"
#include "../Robot.h"

// Constructor
PowerStar::PowerStar(Scene& scene, const float x, const float y)
    : Powerup(scene, x, y) {
  loadAssets();
  setTimerLength(500);
}

// Load assets from manager
void PowerStar::loadAssets() {
  // Load sound
  power_star_sound = scene.getAsset().getAudio("star");

  // Load image
  setTexture("powerStar");
}

void PowerStar::onCollide(const GameObject& other) {
  try {
    auto robot = dynamic_cast<const Robot&>(other);
    stats[STAT_POWERUPS] += 1;
    robot.setInvincibleTimer(getTimerLength());
    power_star_sound.play();
    scene.remove(getId());
  } catch (...) {
    // Nope!
  }
}

// Logic loop!
void PowerStar::update() {
  x -= motion;

  if (x + width <= 0) {
    scene.remove(getId());
  }
}
