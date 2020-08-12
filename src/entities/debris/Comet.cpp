#include "Comet.h"

#include "../../engine/Core.h"

// Constructor
Comet::Comet(const int x, const int y) : Debris(x, y, 5, 1.4f, 0.01f) {
  setTexture(Engine::asset_manager.getImage("comet"));
  destroy_sound = Engine::asset_manager.getAudio("asteroid");
}

void Comet::onDestroy(Robot* robot) {
  // Play sound
  destroy_sound.play();
}