#include "MainGame.h"

#include <algorithm>
#include <fstream>

#include <afk/common/str.h>
#include <afk/random/RandomGenerator.h>
#include <afk/services/Services.h>

#include "../constants/globals.h"
#include "../entities/Background.h"
#include "../entities/EntitySpawner.h"
#include "../entities/GameHud.h"
#include "../entities/PauseMenu.h"
#include "../entities/Robot.h"

// Constructor
void MainGame::start() {
  // Set edittext
  edittext = "Player";

  // From globals
  score = 0;
  screenshake = 0;

  // Game related
  motion = 5;
  themeNumber = 0;
  screenshake_x = 0;
  screenshake_y = 0;
  arrow_animation = 0.0f;

  // End game menu
  iter = edittext.end();

  // Reset stats
  for (int i = 0; i < 4; i++) {
    stats[i] = 0;
  }

  // Images
  // Gui
  ui_game_end = assets.getImage("ui_game_end");
  ui_a = assets.getImage("ui_a");
  ui_b = assets.getImage("ui_b");
  ui_up = assets.getImage("ui_up");
  debug = assets.getImage("debug");

  // Fonts
  orbitron_18 = assets.getFont("orbitron_18");
  orbitron_24 = assets.getFont("orbitron_24");

  // Objects
  powerStar = assets.getImage("powerStar");
  powerMagnet = assets.getImage("powerMagnet");

  // Sets the level to 1
  themeNumber = 0;

  // Mouse
  display.hideMouse();

  // Init hectar
  hectar_id = this->add<Robot>(*this, 80, 300);

  // Load scores
  highscores = ScoreTable("data/scores.dat");

  // Create game hud
  this->add<GameHud>(*this, hectar_id);

  // Create game hud
  pause_menu_id = this->add<PauseMenu>(*this);

  // Add entity spawner
  this->add<EntitySpawner>(*this, hectar_id, pause_menu_id);

  // Play music
  audio.playStream("in_game", true);

  // Scrolling background
  this->add<Background>(*this);
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
  Robot& hectar = this->get<Robot>(hectar_id);

  // Get pause menu
  const PauseMenu& pauseMenu = this->get<PauseMenu>(pause_menu_id);

  // Actual game stuff
  if (!pauseMenu.getPaused()) {
    // Check if hectar has died between update(Uint32 delta);
    bool hectarHasDied = hectar.isAlive();

    // Update robot
    hectar.update(delta);

    // If its different he died play music
    if (hectarHasDied != hectar.isAlive()) {
      audio.stopStream("in_game");

      if (config.get<bool>("music", true) == 1) {
        audio.playStream("death", true);
      }
    }

    // Add to distance travelled
    stats[STAT_DISTANCE] += motion;

    // Changes speed
    if (hectar.isAlive() && hectar.isKeyPressed())
      motion = ((score / 36) + 6);
    else
      motion *= 0.95;

    // Arrow animation
    if (!hectar.isKeyPressed())
      arrow_animation += 0.15;

    // No negative scores
    if (score < 0)
      score = 0;

    // Change theme
    if (score > 199 && themeNumber == 0) {
      themeNumber = 1;
    } else if (score > 399 && themeNumber == 1) {
      themeNumber = 2;
    } else if (score > 600 && themeNumber == 2) {
      themeNumber = 3;
    }

    // Lose scripts
    if (hectar.isOnGround()) {
      // Name input
      if (score > highscores.getScore(9) &&
          input.lastKeyPressed() != static_cast<int>(afk::Keys::UNKNOWN)) {
        // Last key pressed
        int newkey = input.lastKeyPressed();

        // Letters
        if (newkey >= static_cast<int>(afk::Keys::A) &&
            newkey <= static_cast<int>(afk::Keys::Z) &&
            edittext.length() < 14) {
          iter = edittext.insert(
              iter, newkey + 96 - (input.keyDown(afk::Keys::LSHIFT) * 32));
          ++iter;
        }
        // Numbers
        else if (newkey >= static_cast<int>(afk::Keys::ZERO) &&
                 newkey <= static_cast<int>(afk::Keys::NINE) &&
                 edittext.length() < 14) {
          iter = edittext.insert(iter, newkey + 21);
          ++iter;
        }
        // Some other, "special" key was pressed, handle it here
        else if (newkey == static_cast<int>(afk::Keys::BACKSPACE) &&
                 iter != edittext.begin()) {
          --iter;
          iter = edittext.erase(iter);
        } else if (newkey == static_cast<int>(afk::Keys::RIGHT) &&
                   iter != edittext.end()) {
          ++iter;
        } else if (newkey == static_cast<int>(afk::Keys::LEFT) &&
                   iter != edittext.begin()) {
          --iter;
        }
      }

      if (input.keyDown(afk::Keys::RETURN) ||
          input.joyPressed(afk::JoystickButtons::START) ||
          input.joyPressed(afk::JoystickButtons::A)) {
        highscores.add(edittext, score);
        scene.setNextScene("menu");
      }
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
}

// Draw to screen
void MainGame::draw() {
  // Get hectar
  const Robot& hectar = this->get<Robot>(hectar_id);

  // Start arrow
  if (!hectar.isKeyPressed()) {
    if (input.joyEnabled()) {
      ui_a.draw(hectar.getX() + 15,
                hectar.getY() - 60 - sin(arrow_animation) * 10);
    } else {
      ui_up.draw(hectar.getX() + 15,
                 hectar.getY() - 70 - sin(arrow_animation) * 10);
    }
  }

  // Lose scripts
  if (hectar.isOnGround()) {
    ui_game_end.draw(0, 0);
    orbitron_18.draw(130, 125, afk::str::format("Final Score: %i", score));
    orbitron_18.draw(
        130, 165,
        afk::str::format("Distance Flown: %i ft", stats[STAT_DISTANCE] / 10));
    orbitron_18.draw(
        130, 205, afk::str::format("Energy Collected: %i", stats[STAT_ENERGY]));
    orbitron_18.draw(
        130, 245,
        afk::str::format("Powerups Received: %i", stats[STAT_POWERUPS]));
    orbitron_18.draw(
        130, 285, afk::str::format("Debris Collided: %i", stats[STAT_DEBRIS]));

    if (score > highscores.getScore(9)) {
      // Input rectangle
      afk::primitives::rectfill(120, 388, orbitron_24.getWidth(edittext) + 18,
                                44, afk::color::rgb(0, 0, 0));
      afk::primitives::rectfill(122, 390, orbitron_24.getWidth(edittext) + 14,
                                40, afk::color::rgb(255, 255, 255));

      // Textbox lable
      orbitron_18.draw(129, 370, "Enter your name:");

      // Output the string to the screen
      orbitron_24.draw(129, 400, edittext);

      // Draw the caret
      // al_draw_line(orbitron_24.getWidth(edittext.substr(
      //                  0, std::distance(edittext.begin(), iter))) +
      //                  130,
      //              392,
      //              orbitron_24.getWidth(edittext.substr(
      //                  0, std::distance(edittext.begin(), iter))) +
      //                  130,
      //              428, al_map_rgb(0, 0, 0), 2);

      // Draw the congrats message
      orbitron_18.draw(150, 330, "New highscore!", afk::color::rgb(0, 255, 0));
      orbitron_24.draw(150, 450, "Press Enter/   to continue");
      ui_b.draw(370, 450);
    } else {
      orbitron_24.draw(150, 395, "Press Enter/   to continue");
      ui_b.draw(370, 395);
    }
  }
}
