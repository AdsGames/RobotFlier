#include "PauseMenu.h"

#include "../constants/globals.h"
#include "../engine/helpers/stringFns.h"
#include "../engine/input/JoystickListener.h"
#include "../engine/input/KeyListener.h"
#include "../engine/input/MouseListener.h"
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
  if (KeyListener::keyPressed[ALLEGRO_KEY_ESCAPE] ||
      MouseListener::mouse_pressed & 2 ||
      KeyListener::keyPressed[ALLEGRO_KEY_SPACE] ||
      JoystickListener::buttonPressed[JOY_XBOX_START]) {
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
    if (MouseListener::mouse_pressed & 1 &&
        collision(220, 280, MouseListener::mouse_x, MouseListener::mouse_x, 435,
                  460, MouseListener::mouse_y, MouseListener::mouse_y)) {
      Scene::setNextScene(SCENE_EXIT);
    }

    // Menu
    if (MouseListener::mouse_pressed & 1 &&
        collision(300, 430, MouseListener::mouse_x, MouseListener::mouse_x, 435,
                  460, MouseListener::mouse_y, MouseListener::mouse_y)) {
      Scene::setNextScene(SCENE_MENU);
    }

    // Resume
    if (MouseListener::mouse_pressed & 1 &&
        collision(470, 540, MouseListener::mouse_x, MouseListener::mouse_x, 435,
                  460, MouseListener::mouse_y, MouseListener::mouse_y)) {
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