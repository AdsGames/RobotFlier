#include "Energy.h"

#include <afk/scene/Scene.h>

#include "../constants/globals.h"
#include "Robot.h"

// Constructor
Energy::Energy(afk::Scene& scene, const float x, const float y, const int z)
    : Sprite(scene, x, y, z) {
  loadAssets();
}

void Energy::loadAssets() {
  if (scene.config.get<bool>("christmas", false)) {
    setTexture("energy_christmas");
  } else {
    setTexture("energy");
  }
}

void Energy::onCollide(GameObject& other) {
  try {
    dynamic_cast<Robot&>(other);
    scene.audio.playSound("orb");
    scene.remove(id);
  } catch (...) {
    // Nope!
  }
}

// Game logic
void Energy::update(Uint32 delta) {
  x -= motion * delta;

  if (x + width <= 0) {
    scene.remove(id);
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
