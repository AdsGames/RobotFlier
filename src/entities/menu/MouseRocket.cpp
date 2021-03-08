#include "MouseRocket.h"

#include <afk/color/Color.h>
#include <afk/random/RandomGenerator.h>
#include <afk/services/Services.h>

MouseRocket::MouseRocket(afk::Scene& scene) : Sprite(scene, "mouse", 0, 0, 20) {
  mouse_rocket_up = false;

  mouse_y = scene.input.mouseY();
}

void MouseRocket::update() {
  // Set position of sprite
  setPosition(scene.input.mouseX() - width / 2, scene.input.mouseY());

  // Add mouse particles
  if (scene.config.get<int>("particleType", 0) != 3 && mouse_rocket_up) {
    for (int i = 0; i < 50; i++) {
      afk::color::Color part_color =
          afk::color::rgb(255, afk::Random::randomInt(0, 255), 0);

      // Christmas colours
      if (scene.config.get<bool>("christmas", false)) {
        int red_or_green = afk::Random::randomInt(0, 1) * 255;
        part_color = afk::color::rgb(red_or_green, 255 - red_or_green, 0);
      }

      // Particle newParticle(x + width / 2, y + 16, part_color,
      //                      afk::Random::randomInt(-2, 2),
      //                      afk::Random::randomInt(8, 20), 1,
      //                      scene.config.get<int>("particleType", 0));
      // parts.push_back(newParticle);
    }
  }

  // Update particles
  // for (unsigned int i = 0; i < parts.size(); i++) {
  //   parts.at(i).update();
  //   if (afk::Random::randomInt(0, 10) == 0) {
  //     parts.erase(parts.begin() + i);
  //   }
  // }

  // Just went up, flip textures
  if (y < mouse_y && !mouse_rocket_up) {
    setTexture("mouse_rocket");
    mouse_rocket_up = true;
  } else if (y >= mouse_y && mouse_rocket_up) {
    setTexture("mouse");
    mouse_rocket_up = false;
  }

  // Set old y position
  mouse_y = y;
}
