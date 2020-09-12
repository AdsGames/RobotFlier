#include "Scene.h"

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
