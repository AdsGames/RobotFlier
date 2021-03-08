#include "Energy.h"

#include <afk/scene/Scene.h>
#include <afk/services/Services.h>

#include "../constants/globals.h"
#include "Robot.h"

// Constructor
Energy::Energy(afk::Scene& scene, const float x, const float y)
    : Sprite(scene, x, y) {
  loadAssets();
}

void Energy::loadAssets() {
  afk::ConfigService& config = afk::Services::getConfigService();
  afk::AssetService& asset = afk::Services::getAssetService();

  if (config.get<bool>("christmas", false)) {
    setTexture("energy_christmas");
  } else {
    setTexture("energy");
  }

  sound_orb = asset.getAudio("orb");
}

void Energy::onCollide(const GameObject& other) {
  try {
    auto robot = dynamic_cast<const Robot&>(other);
    robot.addHealth(1);

    score += 5;
    stats[STAT_ENERGY] += 1;

    if (robot.getHealth() < 100) {
      robot.addHealth(1);
    }

    sound_orb.play();

    scene.remove(getId());
  } catch (...) {
    // Nope!
  }
}

// Game logic
void Energy::update() {
  x -= motion;

  if (x + width <= 0) {
    scene.remove(getId());
  }

  // if (hectar.isMagnetic()) {
  //       energy->moveTowards(hectar.getX() + hectar.getWidth() / 2,
  //                           hectar.getY() + hectar.getHeight() / 2,
  //                           (float)hectar.getMagneticTimer());
  //     }
}

// Move towards robot
void Energy::moveTowards(const float x, const float y, const float speed) {
  this->x += (speed * (x - this->x)) / 20000;
  this->y += (speed * (y - this->y)) / 20000;
}
