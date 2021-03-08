#include "Bomb.h"

#include <afk/scene/Scene.h>
#include <afk/services/Services.h>

// Constructor
Bomb::Bomb(afk::Scene& scene, const float x, const float y)
    : Debris(scene, x, y, 10, 1.0f, 0.01f) {
  destroy_sound = scene.assets.getAudio("bomb");

  if (scene.config.get<bool>("christmas", false)) {
    setTexture("bomb_christmas");
  } else {
    setTexture("bomb");
  }
}

void Bomb::onDestroy() {
  // Play sound
  destroy_sound.play();
}