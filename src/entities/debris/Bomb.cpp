#include "Bomb.h"

#include "../../engine/scene/Scene.h"

// Constructor
Bomb::Bomb(Scene& scene, const float x, const float y)
    : Debris(scene, x, y, 10, 1.0f, 0.01f) {
  destroy_sound = scene.getAsset().getAudio("bomb");

  if (scene.getSettings().get<bool>("christmas", false)) {
    setTexture("bomb_christmas");
  } else {
    setTexture("bomb");
  }
}

void Bomb::onDestroy() {
  // Play sound
  destroy_sound.play();
}