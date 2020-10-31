#include "Scene.h"

#include <algorithm>
#include <iostream>

#include "../entities/GameObject.h"

// Static
ProgramScene Scene::sceneId = SCENE_NULL;
ProgramScene Scene::nextScene = SCENE_NULL;

/**
 * Draw
 * Draw all objects hooked into scene
 */
void Scene::draw() {
  // Draw
  for (auto& obj : update_pool) {
    obj->draw();
  }
}

/**
 * Update
 * Update all objects hooked into scene
 */
void Scene::update() {
  // Erase dead objects
  update_pool.erase(
      std::remove_if(update_pool.begin(), update_pool.end(),
                     [](auto& obj) -> bool { return obj->dead(); }),
      update_pool.end());

  // Update all
  for (auto& obj : update_pool) {
    obj->update();
  }
}

/**
 * Add
 * Add gameobject to scene hook
 */
void Scene::add(std::unique_ptr<GameObject> obj) {
  update_pool.push_back(std::move(obj));
  sortGameObjects();
}

/**
 * Sort
 * Sort gameobjects by z index
 */
void Scene::sortGameObjects() {
  std::sort(update_pool.begin(), update_pool.end());
}

/**
 * SetNextScene
 * Sets up next scene
 */
void Scene::setNextScene(const ProgramScene sceneId) {
  // If the user doesn't want to exit
  if (Scene::nextScene != SCENE_EXIT) {
    // Set the next scene
    Scene::nextScene = sceneId;
  }
}