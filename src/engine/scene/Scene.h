/*
 * Scene for state machine
 * Allan Legemaate
 * 30/12/2016
 * Compartmentalize program
 */

#ifndef ENGINE_SCENE_SCENE_H
#define ENGINE_SCENE_SCENE_H

#include <map>
#include <memory>
#include <vector>

#include "../entities/GameObject.h"

// Game scenes
enum ProgramScene {
  SCENE_NULL,
  SCENE_INIT,
  SCENE_INTRO,
  SCENE_MENU,
  SCENE_GAME,
  SCENE_EXIT,
};

// Scene
class Scene {
 public:
  // Deconstructor
  virtual ~Scene(){};

  // Draw to screen
  virtual void draw() = 0;

  // Update logic
  virtual void update() = 0;

  // System draw
  void drawInternal();

  // System update
  void updateInternal();

  // Add game object to scene pool
  template <typename T, typename... Args>
  unsigned int add(Args&&... args) {
    std::unique_ptr<GameObject> obj =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    const int id = obj->getId();
    update_pool.push_back(std::move(obj));
    sortGameObjects();
    return id;
  }

  // Remove game object
  void remove(const unsigned int id);

  // Get game object
  template <class T>
  T& get(const unsigned int id) {
    unsigned int index = lookup_map[id];
    return dynamic_cast<T&>(*update_pool.at(index));
  }

  // Add collider
  void addCollider(const unsigned int obj1, const unsigned int obj2);

  // Set next scene
  static void setNextScene(const ProgramScene sceneId);

  // Current scene
  static ProgramScene sceneId;
  static ProgramScene nextScene;

 private:
  // Sort objects
  void sortGameObjects();

  // Holds game objects
  std::vector<std::unique_ptr<GameObject>> update_pool;

  // Quick gameobject lookup
  std::map<unsigned int, unsigned int> lookup_map;

  // Quick collider lookup
  std::map<unsigned int, std::vector<unsigned int>> collider_map;
};

#endif  // ENGINE_SCENE_SCENE_H
