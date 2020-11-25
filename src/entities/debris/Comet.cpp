#include "Comet.h"

#include <afk/scene/Scene.h>
#include "../Robot.h"

const int COMET_DAMAGE = -5;

// Constructor
Comet::Comet(Scene& scene, const float x, const float y)
    : Debris(scene, x, y, 5, 1.4f, 0.01f) {
  setTexture("comet");
  destroy_sound = scene.getAsset().getAudio("asteroid");
}

void Comet::onCollide(const GameObject& other) {
  try {
    auto robot = dynamic_cast<const Robot&>(other);
    robot.addHealth(COMET_DAMAGE);
    destroy();
  } catch (...) {
    // Nope!
  }
}

void Comet::onDestroy() {
  // Play sound
  destroy_sound.play();
}