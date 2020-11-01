#include "Scene.h"

#include <algorithm>
#include <iostream>

#include "../entities/GameObject.h"

// Static
ProgramScene Scene::sceneId = SCENE_NULL;
ProgramScene Scene::nextScene = SCENE_NULL;

/**
 * Draw
 * @description Draw all objects hooked into scene
 */
void Scene::drawInternal() {
  // Draw
  for (auto& obj : update_pool) {
    obj->draw();
  }
}

/**
 * Update
 * @description Update all objects hooked into scene
 */
void Scene::updateInternal() {
  // Update all
  for (unsigned int i = 0; i < update_pool.size(); i++) {
    GameObject& obj = *update_pool.at(i);

    // Update
    obj.update();

    // Get id
    const int id = obj.getId();

    // Collisions
    if (collider_map.count(id) > 0) {
      // Go through each id
      for (const int otherId : collider_map[id]) {
        // Get other
        GameObject& other = *update_pool.at(lookup_map[otherId]);
        if (update_pool.at(i)->colliding(other)) {
          obj.onCollide(other);
          other.onCollide(obj);
        }
      }
    }
  }
}

/**
 * Remove
 * @description Remove gameobject from scene hook
 */
void Scene::remove(const unsigned int id) {
  const unsigned int index = lookup_map[id];
  update_pool.erase(update_pool.begin() + index);
  sortGameObjects();
}

/**
 * Add Collider
 * @description Add collider
 */
void Scene::addCollider(const unsigned int id1, const unsigned int id2) {
  // Add collider 1
  if (collider_map.count(id1) > 0) {
    collider_map[id1].push_back(id2);
  } else {
    collider_map[id1] = std::vector<unsigned>(id2);
  }

  // Add collider 2
  if (collider_map.count(id2) > 0) {
    collider_map[id2].push_back(id1);
  } else {
    collider_map[id2] = std::vector<unsigned int>(id1);
  }
}

/**
 * Sort
 * @description Sort gameobjects by z index
 */
void Scene::sortGameObjects() {
  // Z sort, use defined < operator
  std::sort(update_pool.begin(), update_pool.end(),
            [](auto& obj1, auto& obj2) -> bool { return *obj1 < *obj2; });

  // Erase map
  lookup_map.clear();

  // Update lookup map
  for (unsigned int i = 0; i < update_pool.size(); i++) {
    const int id = update_pool.at(i)->getId();
    lookup_map[id] = i;
  }
}

/**
 * SetNextScene
 * @description Sets up next scene
 */
void Scene::setNextScene(const ProgramScene sceneId) {
  // If the user doesn't want to exit
  if (Scene::nextScene != SCENE_EXIT) {
    // Set the next scene
    Scene::nextScene = sceneId;
  }
}