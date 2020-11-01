#include "EntitySpawner.h"

#include "../constants/globals.h"
#include "../engine/Core.h"
#include "../entities/Energy.h"
#include "../entities/PauseMenu.h"
#include "../entities/Robot.h"
#include "../entities/debris/Asteroid.h"
#include "../entities/debris/Bomb.h"
#include "../entities/debris/Comet.h"
#include "../entities/powerups/Magnet.h"
#include "../entities/powerups/PowerStar.h"

#include <iostream>

EntitySpawner::EntitySpawner(Scene& scene,
                             const unsigned int robotId,
                             const unsigned int pauseMenuId)
    : GameObject(scene), robot_id(robotId), pause_menu_id(pauseMenuId) {}

void EntitySpawner::update() {
  // Get hectar
  Robot hectar = scene.get<Robot>(robot_id);

  // Get pause menu
  PauseMenu pauseMenu = scene.get<PauseMenu>(pause_menu_id);

  const int y = Engine::random.randomInt(30, 550);

  if (pauseMenu.getPaused() || !hectar.isAlive() || hectar.isOnGround()) {
    return;
  }

  // Energy ball spawning
  if (Engine::random.randomInt(0, 50) == 0) {
    scene.add(std::make_unique<Energy>(Energy(scene, SCREEN_W, y)));
  }

  // Asteroids spawning
  if (score >= 100 && Engine::random.randomInt(0, 50) == 0) {
    scene.add(std::make_unique<Asteroid>(Asteroid(scene, SCREEN_W, y, 0)));
  }

  // Bomb spawning
  if (score >= 200 && Engine::random.randomInt(0, 80) == 0) {
    scene.add(std::make_unique<Bomb>(Bomb(scene, SCREEN_W, y)));
  }

  // Comets spawning
  if (score >= 300 && Engine::random.randomInt(0, 200) == 0) {
    scene.add(std::make_unique<Comet>(Comet(scene, SCREEN_W, y)));
  }

  // Powerup spawning
  if (score >= 100 && Engine::random.randomInt(0, 3000) == 0) {
    scene.add(std::make_unique<PowerStar>(PowerStar(scene, SCREEN_W, y)));
  }

  if (score >= 100 && Engine::random.randomInt(0, 500) == 0) {
    scene.add(std::make_unique<Magnet>(Magnet(scene, SCREEN_W, y, 0)));
  }

  if (score >= 200 && Engine::random.randomInt(0, 1000) == 0) {
    scene.add(std::make_unique<Magnet>(Magnet(scene, SCREEN_W, y, 1)));
  }

  if (score >= 300 && Engine::random.randomInt(0, 2000) == 0) {
    scene.add(std::make_unique<Magnet>(Magnet(scene, SCREEN_W, y, 2)));
  }

  if (score >= 500 && Engine::random.randomInt(0, 3000) == 0) {
    scene.add(std::make_unique<Magnet>(Magnet(scene, SCREEN_W, y, 3)));
  }
}
