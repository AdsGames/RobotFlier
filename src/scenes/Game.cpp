#include "Game.h"

#include <algorithm>
#include <fstream>

#include "../constants/globals.h"
#include "../engine/Core.h"
#include "../engine/Locator.h"
#include "../engine/helpers/stringFns.h"
#include "../entities/debris/Asteroid.h"
#include "../entities/debris/Bomb.h"
#include "../entities/debris/Comet.h"
#include "../entities/powerups/Magnet.h"
#include "../entities/powerups/PowerStar.h"
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
  orbitron_12 = Engine::asset_manager.getFont("orbitron_12");
  orbitron_18 = Engine::asset_manager.getFont("orbitron_18");
  orbitron_24 = Engine::asset_manager.getFont("orbitron_24");
  orbitron_30 = Engine::asset_manager.getFont("orbitron_30");

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
  hectar = Robot(80, 300);
  hectar.loadResources();

  // Load scores
  highscores = ScoreTable("data/scores.dat");

  // Create game hud
  hud = GameHud();

  // Play music
  Locator::getAudio()->playStream("in_game", true);

  // this->add(Background(this));
}

// Destructor
Game::~Game() {
  // Clear objects
  energys.clear();
  debries.clear();
  powerups.clear();

  // Stop music
  Locator::getAudio()->stopStream("death");
  Locator::getAudio()->stopStream("in_game");
}

// Spawn objects
void Game::spawnObjects() {
  // Energy ball spawning
  if (Engine::random.randomInt(0, 50) == 0) {
    energys.push_back(
        Energy(this, SCREEN_W, Engine::random.randomInt(30, 550)));
  }

  // Asteroids spawning
  if (score >= 100 && Engine::random.randomInt(0, 50) == 0) {
    debries.push_back(std::make_unique<Asteroid>(Asteroid(
        this, SCREEN_W, Engine::random.randomInt(30, 550), themeNumber)));
  }

  // Bomb spawning
  if (score >= 200 && Engine::random.randomInt(0, 80) == 0) {
    debries.push_back(std::make_unique<Bomb>(
        Bomb(this, SCREEN_W, Engine::random.randomInt(30, 550))));
  }

  // Comets spawning
  if (score >= 300 && Engine::random.randomInt(0, 200) == 0) {
    debries.push_back(std::make_unique<Comet>(
        Comet(this, SCREEN_W, Engine::random.randomInt(30, 550))));
  }

  // Powerup spawning
  if (score >= 100 && Engine::random.randomInt(0, 3000) == 0) {
    powerups.push_back(std::make_unique<PowerStar>(
        PowerStar(this, SCREEN_W, Engine::random.randomInt(30, 600))));
  }

  if (score >= 100 && Engine::random.randomInt(0, 500) == 0) {
    powerups.push_back(std::make_unique<Magnet>(
        Magnet(this, SCREEN_W, Engine::random.randomInt(30, 600), 0)));
  }

  if (score >= 200 && Engine::random.randomInt(0, 1000) == 0) {
    powerups.push_back(std::make_unique<Magnet>(
        Magnet(this, SCREEN_W, Engine::random.randomInt(30, 600), 1)));
  }

  if (score >= 300 && Engine::random.randomInt(0, 2000) == 0) {
    powerups.push_back(std::make_unique<Magnet>(
        Magnet(this, SCREEN_W, Engine::random.randomInt(30, 600), 2)));
  }

  if (score >= 500 && Engine::random.randomInt(0, 3000) == 0) {
    powerups.push_back(std::make_unique<Magnet>(
        Magnet(this, SCREEN_W, Engine::random.randomInt(30, 600), 3)));
  }
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
  // Update pool objects
  Scene::update();

  // Update pauseMenu
  pauseMenu.update();

  // Actual game stuff
  if (!pauseMenu.getPaused()) {
    // Check if hectar has died between update();
    bool hectarHasDied = hectar.isAlive();

    // Update robot
    hectar.update();

    // Update background
    // worldBackground.update(motion);

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

    // Energy
    for (auto& energy : energys) {
      energy.update();

      // Magnet
      if (hectar.isMagnetic()) {
        energy.moveTowards(hectar.getX() + hectar.getWidth() / 2,
                           hectar.getY() + hectar.getHeight() / 2,
                           (float)hectar.getMagneticTimer());
      }
    }

    energys.erase(std::remove_if(energys.begin(), energys.end(),
                                 [](auto& energy) -> bool {
                                   return energy.offScreen() || energy.dead();
                                 }),
                  energys.end());

    // Debries
    for (auto& deb : debries) {
      deb->update();
    }

    debries.erase(
        std::remove_if(debries.begin(), debries.end(),
                       [](auto& deb) -> bool { return deb->offScreen(); }),
        debries.end());

    // Powerups
    for (auto& powerup : powerups) {
      powerup->update();
    }

    powerups.erase(std::remove_if(powerups.begin(), powerups.end(),
                                  [](auto& powerup) -> bool {
                                    return powerup->offScreen() ||
                                           powerup->dead();
                                  }),
                   powerups.end());

    // Spawning
    if (hectar.isAlive() && hectar.isKeyPressed()) {
      spawnObjects();
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
        set_next_scene(SCENE_MENU);
      }
    }
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
  // Draw parent stuff
  Scene::draw();

  // Draw HUD
  hud.draw(hectar, highscores, energys.size(), powerups.size(), debries.size(),
           themeNumber);

  // Energy
  for (auto& energy : energys) {
    energy.draw();
  }

  // Powerups
  for (auto& powerup : powerups) {
    powerup->draw();
  }

  // Draw robot
  hectar.draw();

  // Start arrow
  if (!hectar.isKeyPressed()) {
    if (joystick_enabled)
      ui_a.draw(hectar.getX() + 15,
                hectar.getY() - 60 - sin(arrow_animation) * 10);
    else
      ui_up.draw(hectar.getX() + 15,
                 hectar.getY() - 70 - sin(arrow_animation) * 10);
  }

  // Debris
  for (auto& deb : debries) {
    deb->draw();
  }

  // Robot above asteroids
  hectar.drawOverlay();

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

  // Pause Menu Scripts
  if (pauseMenu.getPaused()) {
    pauseMenu.draw();
  }
}
