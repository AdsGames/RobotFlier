#include "Asteroid.h"

#include "../../engine/Core.h"
#include "../../helpers/tools.h"

// Constructor
Asteroid::Asteroid(const int x, const int y, const int theme)
    : Debris(x, y, 5, 1.0f, 0.0f, Engine::random.randomInt(4, 20)) {
  loadAssets(theme);
}

void Asteroid::loadAssets(const int theme) {
  setTexture(Engine::asset_manager.getImage("asteroid_dark"));

  if (Engine::settings.get<bool>("christmas", false)) {
    setTexture(Engine::asset_manager.getImage("asteroid_christmas"));
  } else {
    switch (theme) {
      case 0:
        setTexture(Engine::asset_manager.getImage("asteroid_moon"));
        break;
      case 1:
        setTexture(Engine::asset_manager.getImage("asteroid_mars"));
        break;
      case 2:
        setTexture(Engine::asset_manager.getImage("asteroid_sun"));
        break;
      case 3:
        setTexture(Engine::asset_manager.getImage("asteroid_dark"));
        break;
      default:
        break;
    }
  }

  destroy_sound = Engine::asset_manager.getAudio("asteroid");
}

void Asteroid::onDestroy(Robot* robot) {
  // Play sound
  destroy_sound.play();
}