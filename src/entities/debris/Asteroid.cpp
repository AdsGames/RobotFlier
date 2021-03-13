#include "Asteroid.h"

#include <afk/random/RandomGenerator.h>
#include <afk/scene/Scene.h>

// Constructor
Asteroid::Asteroid(afk::Scene& scene,
                   const float x,
                   const float y,
                   const int theme)
    : Debris(scene, x, y, 5, 1.0f, 0.0f, afk::Random::randomInt(4, 20)) {
  loadAssets(theme);
}

void Asteroid::loadAssets(const int theme) {
  setTexture("asteroid_dark");

  if (scene.config.get<bool>("christmas", false)) {
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
}

void Asteroid::onDestroy() {
  // Play sound
  scene.audio.playSound("asteroid");
}
