#include "Intro.h"

#include <afk/entities/Sprite.h>

// Construct scene
void Intro::start() {
  start_time = std::chrono::high_resolution_clock::now();
  // Load intro image
  this->add<afk::Sprite>(*this, "intro");
}

// Update (goto menu!)
void Intro::update(Uint32 delta) {
  auto current_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = current_time - start_time;
  if (elapsed.count() > 3000 || input.anyKeyDown()) {
    // Go to menu
    scene.setNextScene("menu");
  }

  Scene::update(delta);
}
