/*
 * Scene for state machine
 * Allan Legemaate
 * 30/12/2016
 * Compartmentalize program
 */

#ifndef ENGINE_SCENE_SCENE_H
#define ENGINE_SCENE_SCENE_H

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
  virtual void draw();

  // Update logic
  virtual void update();

  // Add game object to scene pool
  void add(std::unique_ptr<GameObject> obj);

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
};

#endif  // ENGINE_SCENE_SCENE_H
