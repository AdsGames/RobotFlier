#include "Asteroid.h"

#include "../../engine/Core.h"
#include "../../helpers/tools.h"

// Constructor
Asteroid::Asteroid(Scene* scene, const int x, const int y, const int theme)
    : Debris(scene, x, y, 5, 1.0f, 0.0f, Engine::random.randomInt(4, 20)) {
  loadAssets(theme);
}

void Asteroid::loadAssets(const int theme) {
  setTexture("asteroid_dark");

  if (Engine::settings.get<bool>("christmas", false)) {
    setTexture("asteroid_christmas");
  } else {
    switch (theme) {
      case 0:
        setTexture("asteroid_moon");
        break;
      case 1:
        setTexture("asteroid_mars");
        break;
      case 2:
        setTexture("asteroid_sun");
        break;
      case 3:
        setTexture("asteroid_dark");
        break;
      default:
        break;
    }
  }

  destroy_sound = Engine::asset_manager.getAudio("asteroid");
}

void Asteroid::onDestroy() {
  // Play sound
  destroy_sound.play();
}