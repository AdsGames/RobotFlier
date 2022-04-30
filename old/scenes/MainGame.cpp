#include "MainGame.h"

#include <afk/common/str.h>
#include <afk/random/RandomGenerator.h>

#include <fstream>

#include "../constants/globals.h"
#include "../entities/Background.h"
#include "../entities/DieMenu.h"
#include "../entities/EntitySpawner.h"
#include "../entities/GameHud.h"
#include "../entities/PauseMenu.h"
#include "../entities/Robot.h"

// Constructor
void MainGame::start() {
  // From globals
  score = 0;
  screenshake = 0;

  // Game related
  motion = 0;
  themeNumber = 0;
  screenshake_x = 0;
  screenshake_y = 0;
  arrow_animation = 0.0f;
  hectarIsAlive = true;
  paused = false;

  // Reset stats
  for (int i = 0; i < 4; i++) {
    stats[i] = 0;
  }

  // Die menu
  DieMenu& die_menu = add<DieMenu>(*this);
  die_menu.setHooked(false);
  die_menu_id = die_menu.id;

  // Images
  // Gui
  afk::Sprite& ui_up = add<afk::Sprite>(*this, 0, 0, 10);
  ui_up_id = ui_up.id;
  if (input.joyEnabled()) {
    ui_up.setTexture("ui_a");
  } else {
    ui_up.setTexture("ui_up");
  }

  // Sets the level to 1
  themeNumber = 0;

  // Mouse
  display.hideMouse();

  // Init hectar
  hectar_id = add<Robot>(*this, 80, 300).id;

  // Create game hud
  add<GameHud>(*this, hectar_id);

  // Create game hud
  auto& pauseMenu = add<PauseMenu>(*this);
  pauseMenu.setHooked(false);
  pause_menu_id = pauseMenu.id;

  // Add entity spawner
  spawner_id = add<EntitySpawner>(*this, hectar_id).id;

  // Play music
  audio.playStream("in_game", true);

  // Scrolling background
  add<Background>(*this);
}

// Destructor
void MainGame::stop() {
  // Stop music
  audio.stopStream("death");
  audio.stopStream("in_game");
}

// Take screenshot
void MainGame::takeScreenshot() {
  // Count screenshots
  int screenshotNumber;

  // Get current number
  std::ifstream read("screenshots/screenshot.dat");
  read >> screenshotNumber;
  read.close();

  // State new number
  std::ofstream write("screenshots/screenshot.dat");
  write << screenshotNumber + 1;
  write.close();

  // Save to file
  // al_save_bitmap((std::string("screenshots/screenshot_") +
  //                 std::to_string(screenshotNumber).c_str() + ".png")
  //                    .c_str(),
  //                al_get_backbuffer(display));

  // Snap sound
  audio.playSound("snap");
}

// Update logic of game
void MainGame::update(Uint32 delta) {
  // Get hectar
  auto& hectar = get<Robot>(hectar_id);

  // Pause menu
  if (input.keyPressed(afk::Keys::ESCAPE) ||
      input.mouseDown(afk::MouseButtons::RIGHT) ||
      input.keyPressed(afk::Keys::SPACE) ||
      input.joyPressed(afk::JoystickButtons::START)) {
    auto& pauseMenu = get<PauseMenu>(pause_menu_id);
    auto& spawner = get<EntitySpawner>(spawner_id);

    paused = !paused;
    if (paused) {
      display.showMouse();
      pauseMenu.setHooked(true);
      spawner.setEnabled(false);
      hectar.setEnabled(false);
    } else {
      display.hideMouse();
      pauseMenu.setHooked(false);
      spawner.setEnabled(true);
      hectar.setEnabled(true);
    }
  }

  // Actual game stuff
  if (!paused) {
    // If its different he died play music
    if (hectarIsAlive != hectar.isAlive()) {
      audio.stopStream("in_game");
      DieMenu& die_menu = get<DieMenu>(die_menu_id);
      die_menu.setHooked(true);
      display.showMouse();

      if (config.get<bool>("music", true) == 1) {
        audio.playStream("death", true);
      }
    }

    // Add to distance travelled
    stats[STAT_DISTANCE] += motion;

    // Changes speed
    if (hectar.isAlive() && hectar.isKeyPressed()) {
      motion = (static_cast<float>(score) / 400.0f + 0.1f);
    } else {
      motion *= 0.95;
    }

    // Arrow animation
    if (!hectar.isKeyPressed()) {
      arrow_animation += 0.15;
    }

    // No negative scores
    if (score < 0) {
      score = 0;
    }

    // Change theme
    if (score > 199 && themeNumber == 0) {
      themeNumber = 1;
    } else if (score > 399 && themeNumber == 1) {
      themeNumber = 2;
    } else if (score > 600 && themeNumber == 2) {
      themeNumber = 3;
    }
  } else {
    motion = 0;
  }

  // Screenshot
  if (input.keyPressed(afk::Keys::F11) ||
      input.joyPressed(afk::JoystickButtons::Y)) {
    takeScreenshot();
  }

  // Screen shake
  if (screenshake > 0 && config.get<int>("screenshake", 0) != 0) {
    screenshake_x = screenshake_y = afk::Random::randomInt(
        -(screenshake * config.get<int>("screenshake", 0) +
          100 * config.get<bool>("supershake", false)),
        screenshake * config.get<int>("screenshake", 0) +
            100 * config.get<bool>("supershake", false));
    screenshake--;
  }

  if (screenshake <= 0 || !hectar.isAlive()) {
    screenshake_x = screenshake_y = 0;
  }

  // Random test stuff for devs
  if (config.get<bool>("debug", false)) {
    if (input.keyPressed(afk::Keys::R))
      score += 10;

    if (input.keyPressed(afk::Keys::E) ||
        input.joyDown(afk::JoystickButtons::X))
      hectar.addHealth(1);

    if (input.keyPressed(afk::Keys::T))
      hectar.addHealth(-100);
  }

  // Start arrow
  afk::Sprite& ui_up = get<afk::Sprite>(ui_up_id);
  if (!hectar.isKeyPressed()) {
    ui_up.setHooked(true);
    ui_up.setPosition(hectar.getX() + 15,
                      hectar.getY() - 70 - sin(arrow_animation) * 10);
  } else {
    ui_up.setHooked(false);
  }

  // Check if hectar has died between update(Uint32 delta);
  hectarIsAlive = hectar.isAlive();

  Scene::update(delta);
}
