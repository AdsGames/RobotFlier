#include "Scene.h"
#include <algorithm>
#include <iostream>

// Resdiv
int resDiv;

// Scene variables
int sceneID;
int nextScene;

// Set next scene
void set_next_scene(int sceneId) {
  // If the user doesn't want to exit
  if (nextScene != SCENE_EXIT) {
    // Set the next scene
    nextScene = sceneId;
  }
}

// void Scene::draw() {
//   for (auto& obj : draw_pool) {
//     std::cout << "drawing" << std::endl;
//     if (!obj.dead()) {
//       obj.draw();
//     }
//   }
// }

// void Scene::update() {
//   for (auto& obj : update_pool) {
//     // obj.update();
//   }
// }

// void Scene::add(const GameObject& obj) {
//   draw_pool.push_back(obj);
//   update_pool.push_back(obj);

//   sortGameObjects();
// }

// void Scene::sortGameObjects() {
//   std::sort(
//       draw_pool.begin(), draw_pool.end(),
//       [](auto& obj1, auto& obj2) -> int { return obj1.getZ() - obj2.getZ();
//       });
// }