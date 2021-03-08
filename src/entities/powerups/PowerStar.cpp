#include "PowerStar.h"

#include <afk/scene/Scene.h>
#include <afk/services/Services.h>

#include "../../constants/globals.h"
#include "../Robot.h"

// Constructor
PowerStar::PowerStar(afk::Scene& scene, const float x, const float y)
    : Powerup(scene, x, y) {
  loadAssets();
  setTimerLength(500);
}

// Load assets from manager
void PowerStar::loadAssets() {
  // Load sound
  afk::AssetService& asset = afk::Services::getAssetService();
  power_star_sound = asset.getAudio("star");

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
