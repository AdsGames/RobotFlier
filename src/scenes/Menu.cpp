#include "Menu.h"

#include "../constants/globals.h"
#include "../engine/entities/Sprite.h"
#include "../engine/input/JoystickListener.h"
#include "../engine/input/KeyListener.h"
#include "../engine/input/MouseListener.h"
#include "../engine/random/RandomGenerator.h"
#include "../entities/menu/MouseRocket.h"
#include "../entities/menu/SettingsMenu.h"

// Construct scene
Menu::Menu() {
  // Init vars
  startMove = false;
  startClicked = false;

  // Screen on
  mini_screen = MINISTATE_MENU;

  // Load intro image
  // Random menu
  std::string background_image =
      "background_" + std::to_string(RandomGenerator::randomInt(0, 3));
  this->add<Sprite>(*this, background_image, 0.0f, 0.0f, 0);

  // Add mouse
  this->add<MouseRocket>(*this);

  // Add settings screen component
  settings_screen = this->add<SettingsMenu>(*this);

  start = this->getAsset().getImage("start");
  highscores_button = this->getAsset().getImage("highscores");
  title = this->getAsset().getImage("title");

  credits = this->getAsset().getImage("credits");
  ui_credits = this->getAsset().getImage("ui_credits");
  highscores_table = this->getAsset().getImage("highscores_table");
  ui_help = this->getAsset().getImage("ui_help");
  helpScreen = this->getAsset().getImage("helpScreen");
  xbox_start = this->getAsset().getImage("xbox_start");
  ui_screenshot_notification =
      this->getAsset().getImage("ui_screenshot_notification");
  ui_controls = this->getAsset().getImage("ui_controls");
  controls = this->getAsset().getImage("controls");

  ui_options = this->getAsset().getImage("ui_options");
  ui_options_small = this->getAsset().getImage("ui_options_small");

  // Load fonts
  orbitron_36 = this->getAsset().getFont("orbitron_36");
  orbitron_24 = this->getAsset().getFont("orbitron_24");
  orbitron_18 = this->getAsset().getFont("orbitron_18");
  orbitron_12 = this->getAsset().getFont("orbitron_12");

  // Init animation vars
  animation_pos = 0;

  // Hide mouse
  this->getWindow().hideMouse();

  // Play music
  if (this->getSettings().get<bool>("music", false) == true) {
    this->getAudio().playStream("mainmenu");
  }
}

// Destructor
Menu::~Menu() {
  // Stops music
  this->getAudio().stopStream("mainmenu");
}

// Update loop
void Menu::update() {
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
        SettingsMenu& settings = this->get<SettingsMenu>(settings_screen);
        settings.setOpen(true);
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

  // Close game
  if (KeyListener::key[ALLEGRO_KEY_ESCAPE])
    Scene::setNextScene(SCENE_EXIT);
}

// Draw to screen
void Menu::draw() {
  // Menu Background
  img_menu.draw(0, 0, 0);

  // Start button
  start.draw((animation_pos * 3.2) - start.getWidth(), 400, 0);

  // Highscores button
  highscores_button.draw(SCREEN_W - (animation_pos * 1.4), 30, 0);

  // Joystick Mode
  if (this->getSettings().get<int>("controlMode", 0) != 1 && joystick_enabled) {
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

  // Debug
  if (this->getSettings().get<bool>("debug", false)) {
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
}
