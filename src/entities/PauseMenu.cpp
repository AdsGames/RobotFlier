#include "PauseMenu.h"

#include <afk/common/str.h>
#include <afk/scene/Scene.h>
#include <afk/services/Services.h>

#include "../constants/globals.h"
#include "../helpers/tools.h"

PauseMenu::PauseMenu(afk::Scene& scene) : GameObject(scene), paused(false) {
  background = scene.assets.getImage("pauseMenu");
  orbitron_18 = scene.assets.getFont("orbitron_18");
}

bool PauseMenu::getPaused() const {
  return paused;
}

void PauseMenu::update() {
  // Pause loop code
  if (scene.input.keyPressed(afk::Keys::ESCAPE) ||
      scene.input.mouseDown(afk::MouseButtons::RIGHT) ||
      scene.input.keyPressed(afk::Keys::SPACE) ||
      scene.input.joyPressed(afk::JoystickButtons::START)) {
    if (paused) {
      scene.display.hideMouse();
    } else {
      scene.display.showMouse();
    }
    paused = !paused;
  }

  // Pause Menu Scripts
  if (paused) {
    // Quit game
    if (scene.input.mouseDown(afk::MouseButtons::LEFT) &&
        collision(220, 280, scene.input.mouseX(), scene.input.mouseX(), 435,
                  460, scene.input.mouseY(), scene.input.mouseY())) {
      scene.scene.setNextScene("exit");
    }

    // Menu
    if (scene.input.mouseDown(afk::MouseButtons::LEFT) &&
        collision(300, 430, scene.input.mouseX(), scene.input.mouseX(), 435,
                  460, scene.input.mouseY(), scene.input.mouseY())) {
      scene.scene.setNextScene("menu");
    }

    // Resume
    if (scene.input.mouseDown(afk::MouseButtons::LEFT) &&
        collision(470, 540, scene.input.mouseX(), scene.input.mouseX(), 435,
                  460, scene.input.mouseY(), scene.input.mouseY())) {
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
  background.draw(130, 140);

  // Stats
  orbitron_18.draw(
      220, 250,
      afk::str::format("Distance Flown: %i ft", stats[STAT_DISTANCE] / 10),
      afk::color::rgb(255, 255, 255));
  orbitron_18.draw(220, 280,
                   afk::str::format("Energy Collected: %i", stats[STAT_ENERGY]),
                   afk::color::rgb(255, 255, 255));
  orbitron_18.draw(
      220, 310, afk::str::format("Powerups Received: %i", stats[STAT_POWERUPS]),
      afk::color::rgb(255, 255, 255));
  orbitron_18.draw(220, 340,
                   afk::str::format("Debris Collided: %i", stats[STAT_DEBRIS]),
                   afk::color::rgb(255, 255, 255));

  // Buttons
  orbitron_18.draw(220, 445, "Quit");
  orbitron_18.draw(300, 445, "Main Menu");
  orbitron_18.draw(470, 445, "Resume");
}
