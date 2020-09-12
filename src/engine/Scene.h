/*
 * Scene for state machine
 * Allan Legemaate
 * 30/12/2016
 * Compartmentalize program
 */
#ifndef ENGINE_SCENE_H
#define ENGINE_SCENE_H

// Scene variables
extern int sceneID;
extern int nextScene;

// Set next scene
extern void set_next_scene(int sceneId);

// Game scenes
enum programScenes {
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
};

#endif  // ENGINE_SCENE_H
