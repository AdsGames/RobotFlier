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
#include <stdexcept>
#include <string>
#include <vector>

#include "../Locator.h"
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
  ObjId add(Args&&... args) {
    std::unique_ptr<GameObject> obj =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    const int id = obj->getId();
    update_pool.push_back(std::move(obj));
    sortGameObjects();
    return id;
  }

  // Add game object to scene pool
  template <typename T, typename... Args>
  T& addObj(Args&&... args) {
    std::unique_ptr<GameObject> obj =
        std::make_unique<T>(T(std::forward<Args>(args)...));
    const int id = obj->getId();
    update_pool.push_back(std::move(obj));
    sortGameObjects();
    return get<T>(id);
  }

  // Remove game object
  void remove(const ObjId id);

  // Get game object
  template <class T>
  T& get(const ObjId id) {
    try {
      unsigned int index = lookup_map[id];
      return dynamic_cast<T&>(*update_pool.at(index));
    } catch (...) {
      throw std::runtime_error("Could not find entity by id " +
                               std::to_string(id));
    }
  }

  // Add collider
  void addCollider(const ObjId obj1, const ObjId obj2);

  // Set next scene
  static void setNextScene(const ProgramScene sceneId);

  // Current scene
  static ProgramScene sceneId;
  static ProgramScene nextScene;

  // Locator
  static AudioService& getAudio();
  static AssetManager& getAsset();
  static Window& getWindow();
  static SettingManager& getSettings();

 private:
  // Sort objects
  void sortGameObjects();

  // Holds game objects
  std::vector<std::unique_ptr<GameObject>> update_pool;

  // Quick gameobject lookup
  std::map<ObjId, unsigned int> lookup_map;

  // Quick collider lookup
  std::map<ObjId, std::vector<ObjId>> collider_map;
};

#endif  // ENGINE_SCENE_SCENE_H