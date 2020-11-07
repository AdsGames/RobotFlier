#include "Intro.h"

#include "../engine/entities/Sprite.h"

// Construct scene
Intro::Intro() : start_time(std::chrono::high_resolution_clock::now()) {
  // Load intro image
  this->add<Sprite>(*this, "intro");
}

// Update (goto menu!)
void Intro::update() {
  auto current_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = current_time - start_time;
  if (elapsed.count() > 3000 || this->getInput().keyboard().anyKeyPressed) {
    // Go to menu
    Scene::setNextScene(SCENE_MENU);
  }
}
