#include "Intro.h"

// Construct state
void IntroScene::init() {
  // Load intro image
  img_intro = asw::assets::loadTexture("assets/images/backgrounds/intro.png");
  int a     = 0;
}

// Update (goto menu!)
void IntroScene::update(float deltaTime) {
  // Intro screen
  // fade_in( img_intro, 16);
  // al_rest(1.0);
  // fade_out( 16);

  // Go to menu
  sceneManager.setNextScene(Scenes::Menu);
}
