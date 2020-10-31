#include "Menu.h"

#include "../constants/globals.h"
#include "../engine/Core.h"
#include "../engine/Locator.h"
#include "../engine/input/JoystickListener.h"
#include "../engine/input/KeyListener.h"
#include "../engine/input/MouseListener.h"

// Construct scene
menu::menu() {
  // Init vars
  startMove = false;
  startClicked = false;
  mouse_rocket_up = false;
  mouseMove = MouseListener::mouse_y;

  // Screen on
  mini_screen = MINISTATE_MENU;

  // Load intro image
  // Random menu
  img_menu = Engine::asset_manager.getImage(
      "background_" + std::to_string(Engine::random.randomInt(0, 3)));
  start = Engine::asset_manager.getImage("start");
  highscores_button = Engine::asset_manager.getImage("highscores");
  mouse = Engine::asset_manager.getImage("mouse");
  mouse_rocket = Engine::asset_manager.getImage("mouse_rocket");
  title = Engine::asset_manager.getImage("title");
  options = Engine::asset_manager.getImage("options");

  ui_sound[1] = Engine::asset_manager.getImage("ui_sound_on");
  ui_sound[0] = Engine::asset_manager.getImage("ui_sound_off");

  ui_music[1] = Engine::asset_manager.getImage("ui_music_on");
  ui_music[0] = Engine::asset_manager.getImage("ui_music_off");

  ui_window[1] = Engine::asset_manager.getImage("ui_window_windowed");
  ui_window[0] = Engine::asset_manager.getImage("ui_window_fullscreen");

  ui_particle[0] = Engine::asset_manager.getImage("ui_particle_pixel");
  ui_particle[1] = Engine::asset_manager.getImage("ui_particle_square");
  ui_particle[2] = Engine::asset_manager.getImage("ui_particle_circle");
  ui_particle[3] = Engine::asset_manager.getImage("ui_particle_off");

  ui_control[0] = Engine::asset_manager.getImage("ui_control_xbox");
  ui_control[1] = Engine::asset_manager.getImage("ui_control_keyboard");
  ui_control[2] = Engine::asset_manager.getImage("ui_control_auto");

  ui_screenshake[0] = Engine::asset_manager.getImage("ui_screenshake_none");
  ui_screenshake[1] = Engine::asset_manager.getImage("ui_screenshake_low");
  ui_screenshake[2] = Engine::asset_manager.getImage("ui_screenshake_medium");
  ui_screenshake[3] = Engine::asset_manager.getImage("ui_screenshake_high");

  ui_options = Engine::asset_manager.getImage("ui_options");
  ui_options_small = Engine::asset_manager.getImage("ui_options_small");
  ui_back = Engine::asset_manager.getImage("ui_back");
  credits = Engine::asset_manager.getImage("credits");
  ui_credits = Engine::asset_manager.getImage("ui_credits");
  highscores_table = Engine::asset_manager.getImage("highscores_table");
  ui_help = Engine::asset_manager.getImage("ui_help");
  helpScreen = Engine::asset_manager.getImage("helpScreen");
  ui_exit = Engine::asset_manager.getImage("ui_exit");
  xbox_start = Engine::asset_manager.getImage("xbox_start");
  ui_screenshot_notification =
      Engine::asset_manager.getImage("ui_screenshot_notification");
  ui_controls = Engine::asset_manager.getImage("ui_controls");
  controls = Engine::asset_manager.getImage("controls");

  // Load fonts
  orbitron_36 = Engine::asset_manager.getFont("orbitron_36");
  orbitron_24 = Engine::asset_manager.getFont("orbitron_24");
  orbitron_18 = Engine::asset_manager.getFont("orbitron_18");
  orbitron_12 = Engine::asset_manager.getFont("orbitron_12");

  // Init animation vars
  animation_pos = 0;

  // Hide mouse
  Engine::window.hideMouse();

  // Play music
  if (Engine::settings.get<bool>("music", false) == true) {
    Locator::getAudio()->playStream("mainmenu");
  }
}

// Destructor
menu::~menu() {
  // Stops music
  Locator::getAudio()->stopStream("mainmenu");
}

// Update loop
void menu::update() {
  // Menu animations
  if (animation_pos < 100 && !startClicked) {
    animation_pos += 4;
  }

  if (animation_pos > 0 && startClicked) {
    animation_pos -= 4;
  }

  // Start the game
  if (startClicked && animation_pos <= 0) {
    Scene::setNextScene(SCENE_GAME);
  }

  // Open submenu or start game
  if (mini_screen == MINISTATE_MENU) {
    // Start game with controller
    if (JoystickListener::buttonPressed[JOY_XBOX_START] ||
        JoystickListener::buttonPressed[JOY_XBOX_A]) {
      startClicked = true;
    }

    // Buttons
    if (MouseListener::mouse_pressed & 1) {
      // Start game
      if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 40,
                    40 + start.getWidth(), MouseListener::mouse_y,
                    MouseListener::mouse_y, 410, 410 + start.getHeight())) {
        startClicked = true;
      }
      // Scores
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 660,
                         660 + highscores_button.getWidth(),
                         MouseListener::mouse_y, MouseListener::mouse_y, 30,
                         30 + highscores_button.getHeight())) {
        mini_screen = MINISTATE_SCORES;
      }
      // Credits menu
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 542,
                         644, MouseListener::mouse_y, MouseListener::mouse_y,
                         548, 600)) {
        mini_screen = MINISTATE_CREDITS;
      }
      // Controls menu
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 644,
                         696, MouseListener::mouse_y, MouseListener::mouse_y,
                         548, 600)) {
        mini_screen = MINISTATE_CONTROLS;
      }
      // Help screen
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 696,
                         749, MouseListener::mouse_y, MouseListener::mouse_y,
                         548, 600)) {
        mini_screen = MINISTATE_TUTORIAL;
      }
      // Options menu
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 749,
                         800, MouseListener::mouse_y, MouseListener::mouse_y,
                         548, 600)) {
        mini_screen = MINISTATE_OPTIONS;
      }
    }
  }
  // Exit menus
  else if (mini_screen == MINISTATE_TUTORIAL ||
           mini_screen == MINISTATE_CREDITS ||
           mini_screen == MINISTATE_CONTROLS ||
           mini_screen == MINISTATE_SCORES) {
    if (KeyListener::lastKeyPressed != -1 || MouseListener::mouse_pressed & 1 ||
        JoystickListener::lastButtonPressed != -1) {
      mini_screen = MINISTATE_MENU;
      draw();
    }
  }
  // Options
  else if (mini_screen == MINISTATE_OPTIONS &&
           MouseListener::mouse_pressed & 1) {
    // Particles toggle
    if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x, 400,
                  480, MouseListener::mouse_y, MouseListener::mouse_y)) {
      Engine::settings.set(
          "particleType",
          (Engine::settings.get<int>("particleType", 0) + 1) % 4);
    }
    // Sound button toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      Engine::settings.set("sound", !Engine::settings.get<bool>("sound", true));
    }
    // Music button toggle
    else if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      Engine::settings.set("music", !Engine::settings.get<bool>("music", true));

      if (Engine::settings.get<bool>("music", false)) {
        Locator::getAudio()->playStream("mainmenu");
      } else {
        Locator::getAudio()->stopStream("mainmenu");
      }

    }
    // Fullscreen toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       400, 480, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      const bool isFullscreen = Engine::settings.get<bool>("fullscreen", false);

      if (isFullscreen) {
        Engine::window.setMode(DISPLAY_MODE::WINDOWED);
        Engine::settings.set("fullscreen", false);
      } else {
        Engine::window.setMode(DISPLAY_MODE::FULLSCREEN_WINDOW_LETTERBOX);
        Engine::settings.set("fullscreen", true);
      }
      Engine::window.hideMouse();
    }
    // Screen shake
    else if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x,
                       290, 370, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      Engine::settings.set(
          "screenshake", (Engine::settings.get<int>("screenshake", 0) + 1) % 4);
    }
    // Control Toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       290, 370, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      Engine::settings.set(
          "controlMode", (Engine::settings.get<int>("controlMode", 0) + 1) % 3);
    }
    // Power off
    else if (collision(540, 620, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      // write_settings();
      Scene::setNextScene(SCENE_EXIT);
    }
    // Exit menu
    else if (collision(540, 620, MouseListener::mouse_x, MouseListener::mouse_x,
                       407, 487, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      mini_screen = MINISTATE_MENU;
      // write_settings();
    }
  }

  // Update mouse particles
  if (Engine::settings.get<int>("particleType", 0) != 3 && mouse_rocket_up) {
    for (int i = 0; i < 500; i++) {
      if (Engine::random.randomInt(1, 10) == 1) {
        ALLEGRO_COLOR part_color =
            al_map_rgb(255, Engine::random.randomInt(0, 255), 0);

        if (Engine::settings.get<bool>("christmas", false)) {
          int red_or_green = Engine::random.randomInt(0, 1) * 255;
          part_color = al_map_rgb(red_or_green, 255 - red_or_green, 0);
        }

        Particle newParticle(
            MouseListener::mouse_x, MouseListener::mouse_y + 16, part_color,
            Engine::random.randomInt(-2, 2), Engine::random.randomInt(8, 20), 1,
            Engine::settings.get<int>("particleType", 0));
        mousePart.push_back(newParticle);
      }
    }
  }

  for (unsigned int i = 0; i < mousePart.size(); i++) {
    mousePart.at(i).update();

    if (Engine::random.randomInt(0, 10) == 0)
      mousePart.erase(mousePart.begin() + i);
  }

  // Close game
  if (KeyListener::key[ALLEGRO_KEY_ESCAPE])
    Scene::setNextScene(SCENE_EXIT);

  // Check if mouse is going up
  mouse_rocket_up = (MouseListener::mouse_y < mouseMove);
  mouseMove = MouseListener::mouse_y;
}

// Draw to screen
void menu::draw() {
  // Menu Background
  img_menu.draw(0, 0, 0);

  // Start button
  start.draw((animation_pos * 3.2) - start.getWidth(), 400, 0);

  // Highscores button
  highscores_button.draw(SCREEN_W - (animation_pos * 1.4), 30, 0);

  // Joystick Mode
  if (Engine::settings.get<int>("controlMode", 0) != 1 && joystick_enabled) {
    xbox_start.draw((animation_pos * 3.2) - start.getWidth() + 220, 430, 0);
  }

  // Nice title image
  title.draw(20, (animation_pos * 1.2) - title.getHeight());

  // Bottom Right Buttons
  ui_credits.draw(541,
                  SCREEN_H - (animation_pos * ui_credits.getHeight()) / 100);

  ui_controls.draw(645,
                   SCREEN_H - (animation_pos * ui_controls.getHeight()) / 100);

  ui_help.draw(697, SCREEN_H - (animation_pos * ui_help.getHeight()) / 100);

  ui_options.draw(749,
                  SCREEN_H - (animation_pos * ui_options.getHeight()) / 100);

  // Draw scores
  if (mini_screen == MINISTATE_SCORES) {
    // Highscore background
    highscores_table.draw(200, 50);

    // Title
    orbitron_36.draw(400, 75, "Highscores", al_map_rgb(0, 0, 0),
                     ALLEGRO_ALIGN_CENTRE);

    // Read the top 10 scores
    for (int i = 0; i < 10; i++) {
      orbitron_24.draw(250, (i * 40) + 130,
                       std::to_string(highscores.getScore(i)),
                       al_map_rgb(0, 0, 0), ALLEGRO_ALIGN_CENTRE);
      orbitron_18.draw(575, (i * 40) + 132, highscores.getName(i),
                       al_map_rgb(0, 0, 0), ALLEGRO_ALIGN_RIGHT);
    }
  }
  // Tutorial screen
  else if (mini_screen == MINISTATE_TUTORIAL) {
    helpScreen.draw(0, 0);
  }
  // Credits screen
  else if (mini_screen == MINISTATE_CREDITS) {
    credits.draw(0, 0);
  }
  // Credits screen
  else if (mini_screen == MINISTATE_CONTROLS) {
    controls.draw(0, 0);
  }
  // Option Menu drawing(page and ingame)
  else if (mini_screen == MINISTATE_OPTIONS) {
    // Background
    options.draw(0, 0);

    // Buttons
    ui_particle[Engine::settings.get<int>("particleType", 0)].draw(280, 407);
    ui_sound[Engine::settings.get<bool>("sound", true)].draw(120, 180);
    ui_music[Engine::settings.get<bool>("music", true)].draw(280, 180);
    ui_window[Engine::settings.get<bool>("fullscreen", false)].draw(120, 407);
    ui_screenshake[Engine::settings.get<int>("screenshake", 0)].draw(280, 295,
                                                                     0);
    ui_control[Engine::settings.get<int>("controlMode", 0)].draw(120, 295);

    // Button Text
    orbitron_24.draw(110, 154,
                     "Sounds         Music                            Exit");
    orbitron_24.draw(126, 268, "Input      Screen Shake");
    orbitron_24.draw(108, 382,
                     "Window       Particles                        Back");

    // Exit and back
    ui_exit.draw(540, 180);
    ui_back.draw(540, 407);
  }

  // Debug
  if (Engine::settings.get<bool>("debug", false)) {
    // Joystick testing
    if (joystick_enabled) {
      for (int i = 0; i < JoystickListener::JOY_MAX_BUTTONS; i++) {
        orbitron_12.draw(20, 10 * i + 20,
                         "Joystick B " + std::to_string(i) + " : " +
                             std::to_string(JoystickListener::button[i]));
      }
    }

    // FPS
    orbitron_12.draw(SCREEN_W - 100, 20, "FPS:" + std::to_string(fps));
  }

  // Draw rocket if no particles
  if (Engine::settings.get<int>("particleType", 0) == 3 && mouse_rocket_up) {
    mouse_rocket.draw(MouseListener::mouse_x - 10, MouseListener::mouse_y);
  }

  // Draw mouse particles
  for (unsigned int i = 0; i < mousePart.size(); i++) {
    mousePart.at(i).draw();
  }

  mouse.draw(MouseListener::mouse_x - 10, MouseListener::mouse_y, 0);
}
