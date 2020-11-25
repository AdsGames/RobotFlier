#include "PauseMenu.h"

#include "../constants/globals.h"
#include "../engine/common/stringFns.h"
#include "../engine/scene/Scene.h"
#include "../helpers/tools.h"

PauseMenu::PauseMenu(Scene& scene) : GameObject(scene), paused(false) {
  background = scene.getAsset().getImage("pauseMenu");
  orbitron_18 = scene.getAsset().getFont("orbitron_18");
}

bool PauseMenu::getPaused() const {
  return paused;
}

void PauseMenu::update() {
  // Pause loop code
  if (scene.getInput().keyboard().keyPressed[ALLEGRO_KEY_ESCAPE] ||
      scene.getInput().mouse().down[2] ||
      scene.getInput().keyboard().keyPressed[ALLEGRO_KEY_SPACE] ||
      scene.getInput().joystick().buttonPressed[JOY_XBOX_START]) {
    if (paused) {
      scene.getWindow().hideMouse();
    } else {
      scene.getWindow().showMouse();
    }
    paused = !paused;
  }

  // Pause Menu Scripts
  if (paused) {
    // Quit game
    if (scene.getInput().mouse().down[1] &&
        collision(220, 280, scene.getInput().mouse().x,
                  scene.getInput().mouse().x, 435, 460,
                  scene.getInput().mouse().y, scene.getInput().mouse().y)) {
      Scene::setNextScene("exit");
    }

    // Menu
    if (scene.getInput().mouse().down[1] &&
        collision(300, 430, scene.getInput().mouse().x,
                  scene.getInput().mouse().x, 435, 460,
                  scene.getInput().mouse().y, scene.getInput().mouse().y)) {
      Scene::setNextScene("menu");
    }

    // Resume
    if (scene.getInput().mouse().down[1] &&
        collision(470, 540, scene.getInput().mouse().x,
                  scene.getInput().mouse().x, 435, 460,
                  scene.getInput().mouse().y, scene.getInput().mouse().y)) {
      paused = false;
    }
  }
}

void PauseMenu::draw() {
  // Dont draw unless paused
  if (!paused) {
    return;
  }

  // Menu
  background.draw(130, 140, 0);

  // Stats
  orbitron_18.draw(
      220, 250,
      stringFns::format("Distance Flown: %i ft", stats[STAT_DISTANCE] / 10),
      al_map_rgb(255, 255, 255));
  orbitron_18.draw(
      220, 280, stringFns::format("Energy Collected: %i", stats[STAT_ENERGY]),
      al_map_rgb(255, 255, 255));
  orbitron_18.draw(
      220, 310,
      stringFns::format("Powerups Received: %i", stats[STAT_POWERUPS]),
      al_map_rgb(255, 255, 255));
  orbitron_18.draw(220, 340,
                   stringFns::format("Debris Collided: %i", stats[STAT_DEBRIS]),
                   al_map_rgb(255, 255, 255));

  // Buttons
  orbitron_18.draw(220, 445, "Quit");
  orbitron_18.draw(300, 445, "Main Menu");
  orbitron_18.draw(470, 445, "Resume");
}