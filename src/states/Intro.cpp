#include "Intro.h"

// Construct state
void IntroScene::init() {
  // Load intro image
  img_intro.setTexture(
      asw::assets::loadTexture("assets/images/backgrounds/intro.png"));
  timer = 0.0F;
}

// Update (goto menu!)
void IntroScene::update(float deltaTime) {
  timer += deltaTime;

  // Go to menu
  if (timer >= 3.0F || asw::input::keyboard.anyPressed) {
    sceneManager.setNextScene(Scenes::Menu);
  }
}

void IntroScene::draw() {
  img_intro.draw();
}
