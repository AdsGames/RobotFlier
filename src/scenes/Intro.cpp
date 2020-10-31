#include "Intro.h"

#include "../constants/globals.h"
#include "../engine/Core.h"

// Construct scene
intro::intro() {
  // Load intro image
  img_intro = Engine::asset_manager.getImage("intro");
}

// Update (goto menu!)
void intro::update() {
  // Intro screen
  img_intro.draw(0, 0);
  al_rest(1.0);

  // Go to menu
  Scene::setNextScene(SCENE_MENU);
}
