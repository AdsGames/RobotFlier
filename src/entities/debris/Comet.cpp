#include "Comet.h"

#include <afk/scene/Scene.h>

#include "../Robot.h"

const int COMET_DAMAGE = -5;

// Constructor
Comet::Comet(afk::Scene& scene, const float x, const float y, const int z)
    : Debris(scene, x, y, z, 5, 1.4f, 0.01f) {
  setTexture("comet");
}

void Comet::onCollide(GameObject& other) {
  try {
    auto robot = dynamic_cast<Robot&>(other);
    robot.addHealth(COMET_DAMAGE);
    destroy();
  } catch (...) {
    // Nope!
  }
}

void Comet::onDestroy() {
  // Play sound
  scene.audio.playSound("asteroid");
}
