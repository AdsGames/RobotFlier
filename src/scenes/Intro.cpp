#include "Intro.h"

#include "../engine/entities/Sprite.h"
#include "../engine/input/KeyListener.h"

// Construct scene
Intro::Intro() {
  // Load intro image
  this->add<Sprite>(*this, "intro");

  // Set start time
  start_time = std::chrono::high_resolution_clock::now();
}

// Update (goto menu!)
void Intro::update() {
  auto current_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = current_time - start_time;
  if (elapsed.count() > 3000 || KeyListener::anyKeyPressed) {
    // Go to menu
    Scene::setNextScene(SCENE_MENU);
  }
}
