#include "Intro.h"

#include "../constants/globals.h"

// Construct scene
intro::intro() {
  // Load intro image
  img_intro = this->getAsset().getImage("intro");
}

// Update (goto menu!)
void intro::update() {
  // Intro screen
  img_intro.draw(0, 0);
  al_rest(1.0);

  // Go to menu
  Scene::setNextScene(SCENE_MENU);
}
