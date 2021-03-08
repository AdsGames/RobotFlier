#include "PauseMenu.h"

#include <afk/common/str.h>
#include <afk/scene/Scene.h>
#include <afk/services/Services.h>

#include "../constants/globals.h"
#include "../helpers/tools.h"

PauseMenu::PauseMenu(afk::Scene& scene) : GameObject(scene), paused(false) {
  afk::AssetService& asset = afk::Services::getAssetService();
  background = asset.getImage("pauseMenu");
  orbitron_18 = asset.getFont("orbitron_18");
}

bool PauseMenu::getPaused() const {
  return paused;
}

void PauseMenu::update() {
  afk::InputService& input = afk::Services::getInputService();
  afk::SceneService& scene = afk::Services::getSceneService();
  afk::DisplayService& display = afk::Services::getDisplayService();

  // Pause loop code
  if (input.keyPressed(afk::Keys::KEY_ESCAPE) ||
      input.mouseDown(afk::MouseButtons::BUTTON_RIGHT) ||
      input.keyPressed(afk::Keys::KEY_SPACE) ||
      input.joyPressed(afk::JoystickButtons::JOY_XBOX_START)) {
    if (paused) {
      display.hideMouse();
    } else {
      display.showMouse();
    }
    paused = !paused;
  }

  // Pause Menu Scripts
  if (paused) {
    // Quit game
    if (input.mouseDown(afk::MouseButtons::BUTTON_LEFT) &&
        collision(220, 280, input.mouseX(), input.mouseX(), 435, 460,
                  input.mouseY(), input.mouseY())) {
      scene.setNextScene("exit");
    }

    // Menu
    if (input.mouseDown(afk::MouseButtons::BUTTON_LEFT) &&
        collision(300, 430, input.mouseX(), input.mouseX(), 435, 460,
                  input.mouseY(), input.mouseY())) {
      scene.setNextScene("menu");
    }

    // Resume
    if (input.mouseDown(afk::MouseButtons::BUTTON_LEFT) &&
        collision(470, 540, input.mouseX(), input.mouseX(), 435, 460,
                  input.mouseY(), input.mouseY())) {
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