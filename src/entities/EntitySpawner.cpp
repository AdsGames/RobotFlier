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

EntitySpawner::EntitySpawner(afk::Scene& scene, ObjId robot_id)
    : GameObject(scene), robot_id(robot_id) {}

void EntitySpawner::update(Uint32 delta) {
  // Random y
  int y = afk::Random::randomInt(0, SCREEN_H);

  // Energy ball spawning
  if (afk::Random::randomInt(0, 50) == 0) {
    auto& obj = scene.add<Energy>(scene, SCREEN_W, y, z + 1);
    obj.addCollider(robot_id);
  }

  // Asteroids spawning
  if (score >= 50 && afk::Random::randomInt(0, 50) == 0) {
    auto& obj = scene.add<Asteroid>(scene, SCREEN_W, y, z + 1, 0);
    obj.addCollider(robot_id);
  }

  // Bomb spawning
  if (score >= 100 && afk::Random::randomInt(0, 80) == 0) {
    auto& obj = scene.add<Bomb>(scene, SCREEN_W, y, z + 1);
    obj.addCollider(robot_id);
  }

  // Comets spawning
  if (score >= 200 && afk::Random::randomInt(0, 200) == 0) {
    auto& obj = scene.add<Comet>(scene, SCREEN_W, y, z + 1);
    obj.addCollider(robot_id);
  }

  // Powerup spawning
  if (score >= 100 && afk::Random::randomInt(0, 3000) == 0) {
    auto& obj = scene.add<PowerStar>(scene, SCREEN_W, y, z + 1);
    obj.addCollider(robot_id);
  }

  if (score >= 50 && afk::Random::randomInt(0, 500) == 0) {
    auto& obj = scene.add<Magnet>(scene, SCREEN_W, y, z + 1, 0);
    obj.addCollider(robot_id);
  }

  if (score >= 150 && afk::Random::randomInt(0, 1000) == 0) {
    auto& obj = scene.add<Magnet>(scene, SCREEN_W, y, z + 1, 1);
    obj.addCollider(robot_id);
  }

  if (score >= 200 && afk::Random::randomInt(0, 2000) == 0) {
    auto& obj = scene.add<Magnet>(scene, SCREEN_W, y, z + 1, 2);
    obj.addCollider(robot_id);
  }

  if (score >= 400 && afk::Random::randomInt(0, 3000) == 0) {
    auto& obj = scene.add<Magnet>(scene, SCREEN_W, y, z + 1, 3);
    obj.addCollider(robot_id);
  }
}
