#include "Menu.h"

#include <iostream>

#include "../constants/globals.h"
#include "../engine/entities/Sprite.h"
#include "../engine/input/JoystickListener.h"
#include "../engine/input/KeyListener.h"
#include "../engine/input/MouseListener.h"
#include "../engine/random/RandomGenerator.h"
#include "../engine/ui/Button.h"
#include "../entities/menu/HighScores.h"
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
  mouse_rocket = this->add<MouseRocket>(*this);

  // Add random button
  int button_id =
      this->add<Button>(*this, 10, 10, 2, "hello world", "orbitron_24");
  this->get<Button>(button_id).setOnClick(
      []() -> void { std::cout << "hia" << std::endl; });

  // Add settings screen component
  settings_screen = this->add<SettingsMenu>(*this);

  // Add highscores component
  scores_screen = this->add<HighScores>(*this);

  // Add help sprite
  help_sprite = this->add<Sprite>(*this, "helpScreen", 0, 0, 10);
  this->get<Sprite>(help_sprite).setVisible(false);

  // Add credits sprite
  credits_sprite = this->add<Sprite>(*this, "credits", 0, 0, 10);
  this->get<Sprite>(credits_sprite).setVisible(false);

  // Add controls sprite
  controls_sprite = this->add<Sprite>(*this, "controls", 0, 0, 10);
  this->get<Sprite>(controls_sprite).setVisible(false);

  start = this->getAsset().getImage("start");
  highscores_button = this->getAsset().getImage("highscores");
  title = this->getAsset().getImage("title");

  ui_credits = this->getAsset().getImage("ui_credits");
  ui_help = this->getAsset().getImage("ui_help");
  xbox_start = this->getAsset().getImage("xbox_start");
  ui_controls = this->getAsset().getImage("ui_controls");
  ui_options = this->getAsset().getImage("ui_options");

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
      this->get<HighScores>(scores_screen).setOpen(true);
    }
    // Credits menu
    else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 542, 644,
                       MouseListener::mouse_y, MouseListener::mouse_y, 548,
                       600)) {
      this->get<Sprite>(credits_sprite).setVisible(true);
    }
    // Controls menu
    else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 644, 696,
                       MouseListener::mouse_y, MouseListener::mouse_y, 548,
                       600)) {
      this->get<Sprite>(controls_sprite).setVisible(false);
    }
    // Help screen
    else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 696, 749,
                       MouseListener::mouse_y, MouseListener::mouse_y, 548,
                       600)) {
      this->get<Sprite>(help_sprite).setVisible(false);
    }
    // Options menu
    else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 749, 800,
                       MouseListener::mouse_y, MouseListener::mouse_y, 548,
                       600)) {
      this->get<SettingsMenu>(settings_screen).setOpen(true);
    }
  }

  // Close game
  if (KeyListener::key[ALLEGRO_KEY_ESCAPE]) {
    Scene::setNextScene(SCENE_EXIT);
  }
}

// Draw to screen
void Menu::draw() {
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
}
