#include "PauseMenu.h"

#include "../constants/Globals.h"
#include "../engine/Core.h"
#include "../engine/Input/JoystickListener.h"
#include "../engine/Input/KeyListener.h"
#include "../engine/Input/MouseListener.h"
#include "../engine/Scene.h"
#include "../helpers/stringFns.h"
#include "../helpers/tools.h"

PauseMenu::PauseMenu() : paused(false) {
  loadAssets();
}

void PauseMenu::loadAssets() {
  background = Engine::asset_manager.getImage("pauseMenu");
  orbitron_18 = Engine::asset_manager.getFont("orbitron_18");
}

bool PauseMenu::getPaused() {
  return paused;
}

void PauseMenu::update() {
  // Pause loop code
  if (KeyListener::keyPressed[ALLEGRO_KEY_ESCAPE] ||
      MouseListener::mouse_pressed & 2 ||
      KeyListener::keyPressed[ALLEGRO_KEY_SPACE] ||
      JoystickListener::buttonPressed[JOY_XBOX_START]) {
    if (paused) {
      Engine::window.hideMouse();
    } else {
      Engine::window.showMouse();
    }
    paused = !paused;
  }

  // Pause Menu Scripts
  if (paused) {
    // Quit game
    if (MouseListener::mouse_pressed & 1 &&
        collision(220, 280, MouseListener::mouse_x, MouseListener::mouse_x, 435,
                  460, MouseListener::mouse_y, MouseListener::mouse_y)) {
      set_next_scene(SCENE_EXIT);
    }

    // Menu
    if (MouseListener::mouse_pressed & 1 &&
        collision(300, 430, MouseListener::mouse_x, MouseListener::mouse_x, 435,
                  460, MouseListener::mouse_y, MouseListener::mouse_y)) {
      set_next_scene(SCENE_MENU);
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