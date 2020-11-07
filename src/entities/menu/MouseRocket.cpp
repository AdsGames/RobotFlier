#include "MouseRocket.h"

#include "../../engine/input/MouseListener.h"
#include "../../engine/random/RandomGenerator.h"

MouseRocket::MouseRocket(Scene& scene) : Sprite(scene, "mouse", 0, 0, 20) {
  mouse_rocket_up = false;
  mouse_y = MouseListener::mouse_y;
}

void MouseRocket::update() {
  // Set position of sprite
  x = MouseListener::mouse_x - width / 2;
  y = MouseListener::mouse_y;

  // Add mouse particles
  if (scene.getSettings().get<int>("particleType", 0) != 3 && mouse_rocket_up) {
    for (int i = 0; i < 50; i++) {
      ALLEGRO_COLOR part_color =
          al_map_rgb(255, RandomGenerator::randomInt(0, 255), 0);

      // Christmas colours
      if (scene.getSettings().get<bool>("christmas", false)) {
        int red_or_green = RandomGenerator::randomInt(0, 1) * 255;
        part_color = al_map_rgb(red_or_green, 255 - red_or_green, 0);
      }

      Particle newParticle(x + width / 2, y + 16, part_color,
                           RandomGenerator::randomInt(-2, 2),
                           RandomGenerator::randomInt(8, 20), 1,
                           scene.getSettings().get<int>("particleType", 0));
      parts.push_back(newParticle);
    }
  }

  // Update particles
  for (unsigned int i = 0; i < parts.size(); i++) {
    parts.at(i).update();
    if (RandomGenerator::randomInt(0, 10) == 0) {
      parts.erase(parts.begin() + i);
    }
  }

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
