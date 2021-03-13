#include "EntitySpawner.h"

#include <afk/random/RandomGenerator.h>
#include "../constants/globals.h"
#include "../entities/Energy.h"
#include "../entities/PauseMenu.h"
#include "../entities/Robot.h"
#include "../entities/debris/Asteroid.h"
#include "../entities/debris/Bomb.h"
#include "../entities/debris/Comet.h"
#include "../entities/powerups/Magnet.h"
#include "../entities/powerups/PowerStar.h"

EntitySpawner::EntitySpawner(afk::Scene& scene) : GameObject(scene) {}

void EntitySpawner::update(Uint32 delta) {
  const int y = afk::Random::randomInt(30, 550);

  // Energy ball spawning
  if (afk::Random::randomInt(0, 50) == 0) {
    scene.add<Energy>(scene, SCREEN_W, y);
  }

  // Asteroids spawning
  if (score >= 100 && afk::Random::randomInt(0, 50) == 0) {
    scene.add<Asteroid>(scene, SCREEN_W, y, 0);
  }

  // Bomb spawning
  if (score >= 200 && afk::Random::randomInt(0, 80) == 0) {
    scene.add<Bomb>(scene, SCREEN_W, y);
  }

  // Comets spawning
  if (score >= 300 && afk::Random::randomInt(0, 200) == 0) {
    scene.add<Comet>(scene, SCREEN_W, y);
  }

  // Powerup spawning
  if (score >= 100 && afk::Random::randomInt(0, 3000) == 0) {
    scene.add<PowerStar>(scene, SCREEN_W, y);
  }

  if (score >= 100 && afk::Random::randomInt(0, 500) == 0) {
    scene.add<Magnet>(scene, SCREEN_W, y, 0);
  }

  if (score >= 200 && afk::Random::randomInt(0, 1000) == 0) {
    scene.add<Magnet>(scene, SCREEN_W, y, 1);
  }

  if (score >= 300 && afk::Random::randomInt(0, 2000) == 0) {
    scene.add<Magnet>(scene, SCREEN_W, y, 2);
  }

  if (score >= 500 && afk::Random::randomInt(0, 3000) == 0) {
    scene.add<Magnet>(scene, SCREEN_W, y, 3);
  }
}
