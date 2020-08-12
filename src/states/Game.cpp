#include "Game.h"

#include <algorithm>
#include <fstream>

#include "../constants/globals.h"
#include "../engine/Core.h"
#include "../entities/debris/Asteroid.h"
#include "../entities/debris/Bomb.h"
#include "../entities/debris/Comet.h"
#include "../entities/powerups/Magnet.h"
#include "../entities/powerups/PowerStar.h"
#include "../helpers/stringFns.h"
#include "../helpers/tools.h"

// Constructor
game::game() {
  // From globals
  score = 0;
  screenshake = 0;

  // Game related
  scroll = 0;
  motion = 5;
  themeNumber = 0;
  screenshake_x = 0;
  screenshake_y = 0;
  arrow_animation = 0.0f;
  paused = false;

  // End game menu
  edittext = "Player";
  iter = edittext.end();

  // Reset stats
  for (int i = 0; i < 4; i++) {
    stats[i] = 0;
  }

  // Sounds
  sound_snap = Engine::asset_manager.getAudio("snap");

  // Music
  music_death = Engine::asset_manager.getStream("death");
  music_ingame = Engine::asset_manager.getStream("in_game");

  // Images
  // Gui
  pauseMenu = Engine::asset_manager.getImage("pauseMenu");
  ui_game_end = Engine::asset_manager.getImage("ui_game_end");
  ui_a = Engine::asset_manager.getImage("ui_a");
  ui_b = Engine::asset_manager.getImage("ui_b");
  ui_up = Engine::asset_manager.getImage("ui_up");
  debug = Engine::asset_manager.getImage("debug");

  // Background
  space = Engine::asset_manager.getImage("space");

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
  changeTheme(0);

  // Mouse
  // al_hide_mouse_cursor(display);

  // Init hectar
  hectar = Robot(80, 300);
  hectar.loadResources();

  // Load scores
  highscores = ScoreTable("scores.dat");

  // Play music
  if (Engine::settings.get<bool>("music", true) == 1) {
    music_ingame.play(true);
  }
}

// Destructor
game::~game() {
  // Clear objects
  energys.clear();
  debries.clear();
  powerups.clear();

  // Stop music
  music_ingame.stop();
  music_death.stop();
}

// Themes
void game::changeTheme(int themeNumber) {
  std::string themeName;

  if (themeNumber == 0)
    themeName = "moon";
  else if (themeNumber == 1)
    themeName = "mars";
  else if (themeNumber == 2)
    themeName = "sun";
  else if (themeNumber == 3)
    themeName = "dark";

  this->themeNumber = themeNumber;

  // Other theme images
  groundOverlay = Engine::asset_manager.getImage("groundOverlay_" + themeName);
  groundUnderlay =
      Engine::asset_manager.getImage("groundUnderlay_" + themeName);
  parallaxBack = Engine::asset_manager.getImage("paralax_" + themeName);
}

// Update logic of game
void game::update() {
  // Actual game stuff
  if (!paused) {
    // Check if hectar has died between logic();
    bool hectarHasDied = hectar.isAlive();

    // Update robot
    hectar.logic();

    // If its different he died play music
    if (hectarHasDied != hectar.isAlive()) {
      music_ingame.stop();

      if (Engine::settings.get<bool>("music", true) == 1) {
        music_death.play(true);
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

    // Scrolls background
    scroll -= motion;

    if (scroll / 6 + SCREEN_W <= 0)
      scroll = 0;

    // Change theme
    if (score > 199 && themeNumber == 0)
      changeTheme(1);
    else if (score > 399 && themeNumber == 1)
      changeTheme(2);
    else if (score > 600 && themeNumber == 2)
      changeTheme(3);

    // Energy
    for (auto& energy : energys) {
      energy.logic(motion, &hectar);

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
      deb->logic(motion, &hectar);
    }

    debries.erase(
        std::remove_if(debries.begin(), debries.end(),
                       [](auto& deb) -> bool { return deb->offScreen(); }),
        debries.end());

    // Powerups
    for (auto& powerup : powerups) {
      powerup->logic(motion, &hectar);
    }

    powerups.erase(std::remove_if(powerups.begin(), powerups.end(),
                                  [](auto& powerup) -> bool {
                                    return powerup->offScreen() ||
                                           powerup->dead();
                                  }),
                   powerups.end());

    // Spawning
    if (hectar.isAlive() && hectar.isKeyPressed()) {
      // Energy ball spawning
      if (Engine::random.randomInt(0, 50) == 0) {
        energys.push_back(Energy(SCREEN_W, Engine::random.randomInt(30, 550)));
      }

      // Asteroids spawning
      if (score >= 100 && Engine::random.randomInt(0, 50) == 0) {
        debries.push_back(std::make_unique<Asteroid>(Asteroid(
            SCREEN_W, Engine::random.randomInt(30, 550), themeNumber)));
      }

      // Bomb spawning
      if (score >= 200 && Engine::random.randomInt(0, 80) == 0) {
        debries.push_back(std::make_unique<Bomb>(
            Bomb(SCREEN_W, Engine::random.randomInt(30, 550))));
      }

      // Comets spawning
      if (score >= 300 && Engine::random.randomInt(0, 200) == 0) {
        debries.push_back(std::make_unique<Comet>(
            Comet(SCREEN_W, Engine::random.randomInt(30, 550))));
      }

      // Powerup spawning
      if (score >= 100 && Engine::random.randomInt(0, 3000) == 0) {
        powerups.push_back(std::make_unique<PowerStar>(
            PowerStar(SCREEN_W, Engine::random.randomInt(30, 600))));
      }

      if (score >= 100 && Engine::random.randomInt(0, 500) == 0) {
        powerups.push_back(std::make_unique<Magnet>(
            Magnet(SCREEN_W, Engine::random.randomInt(30, 600), 0)));
      }

      if (score >= 200 && Engine::random.randomInt(0, 1000) == 0) {
        powerups.push_back(std::make_unique<Magnet>(
            Magnet(SCREEN_W, Engine::random.randomInt(30, 600), 1)));
      }

      if (score >= 300 && Engine::random.randomInt(0, 2000) == 0) {
        powerups.push_back(std::make_unique<Magnet>(
            Magnet(SCREEN_W, Engine::random.randomInt(30, 600), 2)));
      }

      if (score >= 500 && Engine::random.randomInt(0, 3000) == 0) {
        powerups.push_back(std::make_unique<Magnet>(
            Magnet(SCREEN_W, Engine::random.randomInt(30, 600), 3)));
      }
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
        set_next_state(STATE_MENU);
      }
    }
  }

  // Screenshot
  if (KeyListener::keyPressed[ALLEGRO_KEY_F11] ||
      JoystickListener::buttonPressed[3]) {
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
    sound_snap.play();
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

  if (screenshake <= 0 || !hectar.isAlive())
    screenshake_x = screenshake_y = 0;

  // Random test stuff for devs
  if (Engine::settings.get<bool>("debug", false)) {
    if (KeyListener::key[ALLEGRO_KEY_R])
      score += 10;

    if (KeyListener::key[ALLEGRO_KEY_E] || JoystickListener::button[2])
      hectar.addHealth(1);

    if (KeyListener::key[ALLEGRO_KEY_T])
      hectar.addHealth(-100);
  }

  // Pause loop code
  if (KeyListener::keyPressed[ALLEGRO_KEY_ESCAPE] ||
      MouseListener::mouse_pressed & 2 ||
      KeyListener::keyPressed[ALLEGRO_KEY_SPACE] ||
      JoystickListener::buttonPressed[JOY_XBOX_START]) {
    if (paused) {
      paused = false;
      // al_hide_mouse_cursor(display);
    } else if (hectar.isAlive()) {
      paused = true;
      // al_show_mouse_cursor(display);
    }
  }

  // Pause Menu Scripts
  if (paused) {
    // Quit game
    if (MouseListener::mouse_pressed & 1 &&
        collision(220, 280, MouseListener::mouse_x, MouseListener::mouse_x, 435,
                  460, MouseListener::mouse_y, MouseListener::mouse_y))
      set_next_state(STATE_EXIT);

    // Menu
    if (MouseListener::mouse_pressed & 1 &&
        collision(300, 430, MouseListener::mouse_x, MouseListener::mouse_x, 435,
                  460, MouseListener::mouse_y, MouseListener::mouse_y))
      set_next_state(STATE_MENU);

    // Resume
    if (MouseListener::mouse_pressed & 1 &&
        collision(470, 540, MouseListener::mouse_x, MouseListener::mouse_x, 435,
                  460, MouseListener::mouse_y, MouseListener::mouse_y))
      paused = false;
  }
}

// Draw to screen
void game::draw() {
  // Draw backgrounds and Ground Overlay
  space.draw(scroll / 6, 0);
  space.draw(scroll / 6 + SCREEN_W, 0);

  // Draw HUD
  // Info
  orbitron_30.draw(10, 10, stringFns::format("Score:%i", score),
                   al_map_rgb(255, 255, 255));
  orbitron_30.draw(10, 38, stringFns::format("Health:%i", hectar.getHealth()),
                   al_map_rgb(255, 255, 255));
  al_draw_filled_rectangle(10, 68, 10 + (hectar.getHealth() * 1.7), 78,
                           al_map_rgb(255 - hectar.getHealth() * 2.5,
                                      0 + hectar.getHealth() * 2.5, 0));

  // Power up timers
  if (hectar.isInvincible()) {
    al_draw_filled_circle(45, 105, 20, al_map_rgb(255, 255, 255));
    powerStar.draw(20, 80);
    orbitron_24.draw(44, 94, std::to_string(hectar.getInvincibleTimer() / 5),
                     al_map_rgb(255, 255, 255), ALLEGRO_ALIGN_CENTER);
    orbitron_24.draw(45, 96, std::to_string(hectar.getInvincibleTimer() / 5),
                     al_map_rgb(255, 0, 0), ALLEGRO_ALIGN_CENTER);
  }

  if (hectar.isMagnetic()) {
    al_draw_filled_circle(175, 105, 20, al_map_rgb(255, 255, 255));
    powerMagnet.draw(175, 150, 80);
    orbitron_24.draw(174, 94, std::to_string(hectar.getMagneticTimer() / 5),
                     al_map_rgb(255, 255, 255), ALLEGRO_ALIGN_CENTER);
    orbitron_24.draw(175, 96, std::to_string(hectar.getMagneticTimer() / 5),
                     al_map_rgb(255, 0, 0), ALLEGRO_ALIGN_CENTER);
  }

  // Draw the debug window
  if (Engine::settings.get<bool>("debug", false)) {
    debug.draw(0, 0, 0);

    // Column 1
    orbitron_12.draw(5, 25, stringFns::format("Motion:%4.2f", motion),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(5, 35, stringFns::format("Robot X:%4.2f", hectar.getX()),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(5, 45, stringFns::format("Robot Y:%4.2f", hectar.getY()),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(5, 55, stringFns::format("Motion:%4.2f", motion),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(
        5, 65, stringFns::format("Invincible:%i", hectar.getInvincibleTimer()),
        al_map_rgb(255, 255, 255));

    // Column 2
    orbitron_12.draw(120, 25, stringFns::format("Score:%i", score),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(
        120, 35, stringFns::format("Magnetic:%i", hectar.getMagneticTimer()),
        al_map_rgb(255, 255, 255));
    orbitron_12.draw(120, 45,
                     stringFns::format("Mouse X:%i", MouseListener::mouse_x),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(120, 55,
                     stringFns::format("Mouse Y:%i", MouseListener::mouse_y),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(
        120, 65,
        stringFns::format("Particles On:%i",
                          Engine::settings.get<int>("particleType", 0)),
        al_map_rgb(255, 255, 255));

    // Column 3
    orbitron_12.draw(245, 25,
                     stringFns::format("LowScore:%i", highscores.getScore(9)),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(245, 35, stringFns::format("Theme:%i", themeNumber),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(245, 45, stringFns::format("Energys:%i", energys.size()),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(245, 55, stringFns::format("Debris:%i", debries.size()),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(245, 65, stringFns::format("Powerups:%i", powerups.size()),
                     al_map_rgb(255, 255, 255));

    // Column 4
    orbitron_12.draw(
        360, 25, stringFns::format("Last key:%i", KeyListener::lastKeyPressed),
        al_map_rgb(255, 255, 255));
    orbitron_12.draw(
        360, 35,
        stringFns::format("Has highscore:%i", score > highscores.getScore(9)),
        al_map_rgb(255, 255, 255));

    // FPS
    orbitron_18.draw(SCREEN_W - 100, 25, stringFns::format("FPS:%i", fps),
                     al_map_rgb(255, 255, 255));
  }

  // Mountain Paralax
  parallaxBack.draw((scroll / 3) % SCREEN_W, 0);
  parallaxBack.draw((scroll / 3) % SCREEN_W + SCREEN_W, 0);

  // Ground
  groundUnderlay.draw(scroll % SCREEN_W, SCREEN_H - 40);
  groundUnderlay.draw(scroll % SCREEN_W + SCREEN_W, SCREEN_H - 40);

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

  // Ground underlay
  groundOverlay.draw(scroll % SCREEN_W, SCREEN_H - 20);
  groundOverlay.draw(scroll % SCREEN_W + SCREEN_W, SCREEN_H - 20);

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
  if (paused) {
    // Menu
    pauseMenu.draw(130, 140, 0);

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
    orbitron_18.draw(
        220, 340, stringFns::format("Debris Collided: %i", stats[STAT_DEBRIS]),
        al_map_rgb(255, 255, 255));

    // Buttons
    orbitron_18.draw(220, 445, "Quit");
    orbitron_18.draw(300, 445, "Main Menu");
    orbitron_18.draw(470, 445, "Resume");
  }
}
