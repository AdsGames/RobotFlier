#include "Game.h"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "../constants/globals.h"
#include "../engine/Core.h"
#include "../engine/Locator.h"
#include "../engine/helpers/stringFns.h"
#include "../engine/input/JoystickListener.h"
#include "../engine/input/KeyListener.h"
#include "../engine/input/MouseListener.h"
#include "../entities/Background.h"
#include "../entities/EntitySpawner.h"
#include "../entities/GameHud.h"
#include "../entities/PauseMenu.h"
#include "../entities/Robot.h"
#include "../helpers/tools.h"

// Constructor
Game::Game() {
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
  edittext = "Player";
  iter = edittext.end();

  // Reset stats
  for (int i = 0; i < 4; i++) {
    stats[i] = 0;
  }

  // Images
  // Gui
  ui_game_end = Engine::asset_manager.getImage("ui_game_end");
  ui_a = Engine::asset_manager.getImage("ui_a");
  ui_b = Engine::asset_manager.getImage("ui_b");
  ui_up = Engine::asset_manager.getImage("ui_up");
  debug = Engine::asset_manager.getImage("debug");

  // Fonts
  orbitron_18 = Engine::asset_manager.getFont("orbitron_18");
  orbitron_24 = Engine::asset_manager.getFont("orbitron_24");

  // Nullfiy bitmaps not loaded yet
  screenshot = nullptr;

  // Objects
  powerStar = Engine::asset_manager.getImage("powerStar");
  powerMagnet = Engine::asset_manager.getImage("powerMagnet");

  // Sets the level to 1
  themeNumber = 0;

  // Mouse
  Engine::window.hideMouse();

  // Init hectar
  hectar_id = this->add(std::make_unique<Robot>(Robot(*this, 80, 300)));

  // Load scores
  highscores = ScoreTable("data/scores.dat");

  // Create game hud
  this->add(std::make_unique<GameHud>(GameHud(*this, hectar_id)));

  // Create game hud
  pause_menu_id = this->add(std::make_unique<PauseMenu>(PauseMenu(*this)));

  // Add entity spawner
  this->add(std::make_unique<EntitySpawner>(
      EntitySpawner(*this, hectar_id, pause_menu_id)));

  // Play music
  Locator::getAudio()->playStream("in_game", true);

  this->add(std::make_unique<Background>(Background(*this)));
}

// Destructor
Game::~Game() {
  // Stop music
  Locator::getAudio()->stopStream("death");
  Locator::getAudio()->stopStream("in_game");
}

// Take screenshot
void Game::takeScreenshot() {
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
  Locator::getAudio()->playSound("snap");
}

// Update logic of game
void Game::update() {
  // Get hectar
  Robot hectar = this->get<Robot>(hectar_id);

  // Get pause menu
  PauseMenu pauseMenu = this->get<PauseMenu>(pause_menu_id);

  // Actual game stuff
  if (!pauseMenu.getPaused()) {
    // Check if hectar has died between update();
    bool hectarHasDied = hectar.isAlive();

    // Update robot
    hectar.update();

    // If its different he died play music
    if (hectarHasDied != hectar.isAlive()) {
      Locator::getAudio()->stopStream("in_game");

      if (Engine::settings.get<bool>("music", true) == 1) {
        Locator::getAudio()->playStream("death", true);
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
      if (score > highscores.getScore(9) && KeyListener::lastKeyPressed != -1) {
        // Last key pressed
        int newkey = KeyListener::lastKeyPressed;

        // Letters
        if (newkey >= ALLEGRO_KEY_A && newkey <= ALLEGRO_KEY_Z &&
            edittext.length() < 14) {
          iter = edittext.insert(
              iter, newkey + 96 - (KeyListener::key[ALLEGRO_KEY_LSHIFT] * 32));
          ++iter;
        }
        // Numbers
        else if (newkey >= ALLEGRO_KEY_0 && newkey <= ALLEGRO_KEY_9 &&
                 edittext.length() < 14) {
          iter = edittext.insert(iter, newkey + 21);
          ++iter;
        }
        // Some other, "special" key was pressed, handle it here
        else if (newkey == ALLEGRO_KEY_BACKSPACE && iter != edittext.begin()) {
          --iter;
          iter = edittext.erase(iter);
        } else if (newkey == ALLEGRO_KEY_RIGHT && iter != edittext.end()) {
          ++iter;
        } else if (newkey == ALLEGRO_KEY_LEFT && iter != edittext.begin()) {
          --iter;
        }
      }

      if (KeyListener::key[ALLEGRO_KEY_ENTER] ||
          JoystickListener::buttonPressed[JOY_XBOX_START] ||
          JoystickListener::buttonPressed[JOY_XBOX_A]) {
        highscores.add(edittext, score);
        Scene::setNextScene(SCENE_MENU);
      }
    }
  } else {
    motion = 0;
  }

  // Screenshot
  if (KeyListener::keyPressed[ALLEGRO_KEY_F11] ||
      JoystickListener::buttonPressed[3]) {
    takeScreenshot();
  }

  // Screen shake
  if (screenshake > 0 && Engine::settings.get<int>("screenshake", 0) != 0) {
    screenshake_x = screenshake_y = Engine::random.randomInt(
        -(screenshake * Engine::settings.get<int>("screenshake", 0) +
          100 * Engine::settings.get<bool>("supershake", false)),
        screenshake * Engine::settings.get<int>("screenshake", 0) +
            100 * Engine::settings.get<bool>("supershake", false));
    screenshake--;
  }

  if (screenshake <= 0 || !hectar.isAlive()) {
    screenshake_x = screenshake_y = 0;
  }

  // Random test stuff for devs
  if (Engine::settings.get<bool>("debug", false)) {
    if (KeyListener::key[ALLEGRO_KEY_R])
      score += 10;

    if (KeyListener::key[ALLEGRO_KEY_E] || JoystickListener::button[2])
      hectar.addHealth(1);

    if (KeyListener::key[ALLEGRO_KEY_T])
      hectar.addHealth(-100);
  }
}

// Draw to screen
void Game::draw() {
  // Get hectar
  Robot hectar = this->get<Robot>(hectar_id);

  // Start arrow
  if (!hectar.isKeyPressed()) {
    if (joystick_enabled)
      ui_a.draw(hectar.getX() + 15,
                hectar.getY() - 60 - sin(arrow_animation) * 10);
    else
      ui_up.draw(hectar.getX() + 15,
                 hectar.getY() - 70 - sin(arrow_animation) * 10);
  }

  // Lose scripts
  if (hectar.isOnGround()) {
    ui_game_end.draw(0, 0);
    orbitron_18.draw(130, 125, stringFns::format("Final Score: %i", score));
    orbitron_18.draw(
        130, 165,
        stringFns::format("Distance Flown: %i ft", stats[STAT_DISTANCE] / 10));
    orbitron_18.draw(
        130, 205,
        stringFns::format("Energy Collected: %i", stats[STAT_ENERGY]));
    orbitron_18.draw(
        130, 245,
        stringFns::format("Powerups Received: %i", stats[STAT_POWERUPS]));
    orbitron_18.draw(
        130, 285, stringFns::format("Debris Collided: %i", stats[STAT_DEBRIS]));

    if (score > highscores.getScore(9)) {
      // Input rectangle
      al_draw_filled_rectangle(120, 388, orbitron_24.getWidth(edittext) + 138,
                               432, al_map_rgb(0, 0, 0));
      al_draw_filled_rectangle(122, 390, orbitron_24.getWidth(edittext) + 136,
                               430, al_map_rgb(255, 255, 255));

      // Textbox lable
      orbitron_18.draw(129, 370, "Enter your name:");

      // Output the string to the screen
      orbitron_24.draw(129, 400, edittext);

      // Draw the caret
      al_draw_line(orbitron_24.getWidth(edittext.substr(
                       0, std::distance(edittext.begin(), iter))) +
                       130,
                   392,
                   orbitron_24.getWidth(edittext.substr(
                       0, std::distance(edittext.begin(), iter))) +
                       130,
                   428, al_map_rgb(0, 0, 0), 2);

      // Draw the congrats message
      orbitron_18.draw(150, 330, "New highscore!", al_map_rgb(0, 255, 0));
      orbitron_24.draw(150, 450, "Press Enter/   to continue");
      ui_b.draw(370, 450, 0);
    } else {
      orbitron_24.draw(150, 395, "Press Enter/   to continue");
      ui_b.draw(370, 395, 0);
    }
  }
}
