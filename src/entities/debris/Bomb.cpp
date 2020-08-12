#include "Bomb.h"

#include "../../engine/Core.h"

// Constructor
Bomb::Bomb(const int x, const int y) : Debris(x, y, 10, 1.0f, 0.01f) {
  destroy_sound = Engine::asset_manager.getAudio("bomb");

  if (Engine::settings.get<bool>("christmas", false)) {
    setTexture(Engine::asset_manager.getImage("bomb_christmas"));
  } else {
    setTexture(Engine::asset_manager.getImage("bomb"));
  }
}

void Bomb::onDestroy(Robot* robot) {
  // Play sound
  destroy_sound.play();
}