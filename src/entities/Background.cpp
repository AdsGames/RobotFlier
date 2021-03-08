#include "Background.h"

#include <afk/services/Services.h>

#include <string>

#include "../constants/globals.h"

Background::Background(afk::Scene& scene)
    : GameObject(scene, 0.0f, 0.0f, -1), scroll(0) {
  changeTheme(0);
}

void Background::update() {
  scroll -= motion;

  if (scroll / 6 + SCREEN_W <= 0) {
    scroll = 0;
  }
}

void Background::changeTheme(const int theme) {
  std::string themeName = "";

  // Select theme name
  switch (theme) {
    case 0:
      themeName = "moon";
      break;
    case 1:
      themeName = "mars";
      break;
    case 2:
      themeName = "sun";
      break;
    case 3:
      themeName = "dark";
      break;
  }

  // Choose theme images
  groundOverlay = scene.assets.getImage("groundOverlay_" + themeName);
  groundUnderlay = scene.assets.getImage("groundUnderlay_" + themeName);
  parallaxBack = scene.assets.getImage("paralax_" + themeName);
  space = scene.assets.getImage("space");
}

void Background::draw() {
  // Draw backgrounds and Ground Overlay
  space.draw(scroll / 6, 0);
  space.draw(scroll / 6 + SCREEN_W, 0);

  // Mountain Paralax
  parallaxBack.draw((scroll / 3) % SCREEN_W, 0);
  parallaxBack.draw((scroll / 3) % SCREEN_W + SCREEN_W, 0);

  // Ground
  groundUnderlay.draw(scroll % SCREEN_W, SCREEN_H - 40);
  groundUnderlay.draw(scroll % SCREEN_W + SCREEN_W, SCREEN_H - 40);

  // Ground underlay
  groundOverlay.draw(scroll % SCREEN_W, SCREEN_H - 20);
  groundOverlay.draw(scroll % SCREEN_W + SCREEN_W, SCREEN_H - 20);
}
