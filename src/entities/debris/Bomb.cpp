#include "Bomb.h"

#include <afk/scene/Scene.h>
#include <afk/services/Services.h>

// Constructor
Bomb::Bomb(afk::Scene& scene, const float x, const float y)
    : Debris(scene, x, y, 10, 1.0f, 0.01f) {
  afk::AssetService& assets = afk::Services::getAssetService();
  destroy_sound = assets.getAudio("bomb");

  afk::ConfigService& config = afk::Services::getConfigService();
  if (config.get<bool>("christmas", false)) {
    setTexture("bomb_christmas");
  } else {
    setTexture("bomb");
  }
}

void Bomb::onDestroy() {
  // Play sound
  destroy_sound.play();
}