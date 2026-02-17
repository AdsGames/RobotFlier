#include "Init.h"

// Construct state
void InitScene::init() {
  // Title
  asw::display::setTitle("A.D.S. Games - Robot Flier");

  // Icon
  asw::display::setIcon("assets/images/objects/bomb.png");

  // Loads fonts
  orbitron_12 = asw::assets::loadFont("assets/fonts/orbitron_ttf.ttf", 12);
  orbitron_18 = asw::assets::loadFont("assets/fonts/orbitron_ttf.ttf", 18);
  orbitron_24 = asw::assets::loadFont("assets/fonts/orbitron_ttf.ttf", 24);
  orbitron_30 = asw::assets::loadFont("assets/fonts/orbitron_ttf.ttf", 30);
  orbitron_36 = asw::assets::loadFont("assets/fonts/orbitron_ttf.ttf", 36);
}
