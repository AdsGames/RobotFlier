#include "Menu.h"

#include <functional>
#include <iostream>

#include <afk/entities/Sprite.h>
#include <afk/entities/ui/Button.h>
#include <afk/random/RandomGenerator.h>
#include <afk/services/Services.h>

#include "../constants/globals.h"
#include "../entities/menu/HighScores.h"
#include "../entities/menu/MouseRocket.h"
#include "../entities/menu/SettingsMenu.h"

// Construct scene
void Menu::start() {
  afk::ConfigService& config = afk::Services::getConfigService();
  afk::DisplayService& display = afk::Services::getDisplayService();
  afk::InputService& input = afk::Services::getInputService();
  afk::AudioService& audio = afk::Services::getAudioService();

  current_menu = MENU::NONE;

  // Load intro image
  // Random menu
  std::string background_image =
      "background_" + std::to_string(afk::Random::randomInt(0, 3));
  add<afk::Sprite>(*this, background_image, 0.0f, 0.0f, 0);

  // Add mouse
  add<MouseRocket>(*this);

  // Add title
  add<afk::Sprite>(*this, "title", 20, 20, 0);

  // Add settings screen component
  settings_screen = add<SettingsMenu>(*this);

  // Add highscores component
  scores_screen = add<HighScores>(*this);

  // Add help sprite
  help_sprite = add<afk::Sprite>(*this, "helpScreen", 0, 0, 10);
  get<afk::Sprite>(help_sprite).setVisible(false);

  // Add credits sprite
  credits_sprite = add<afk::Sprite>(*this, "credits", 0, 0, 10);
  get<afk::Sprite>(credits_sprite).setVisible(false);

  // Add controls sprite
  controls_sprite = add<afk::Sprite>(*this, "controls", 0, 0, 10);
  get<afk::Sprite>(controls_sprite).setVisible(false);

  // Xbox start button
  if (config.get<int>("controlMode", 0) != 1 && input.joyEnabled()) {
    add<afk::Sprite>(*this, "xbox_start", 240, 480, 3);
  }

  // Add credits button
  addObj<afk::Button>(*this, 540, 548, 2, "ui_credits")
      .setOnClick(std::bind(&Menu::handleClickCredits, this));

  // Add help button
  addObj<afk::Button>(*this, 696, 548, 2, "ui_help")
      .setOnClick(std::bind(&Menu::handleClickHelp, this));

  // Add settings button
  addObj<afk::Button>(*this, 748, 548, 2, "ui_options")
      .setOnClick(std::bind(&Menu::handleClickSettings, this));

  // Add controls button
  addObj<afk::Button>(*this, 644, 548, 2, "ui_controls")
      .setOnClick(std::bind(&Menu::handleClickControls, this));

  // Add highscores button
  addObj<afk::Button>(*this, 660, 20, 2, "highscores")
      .setOnClick(std::bind(&Menu::handleClickScores, this));

  // Add start button
  addObj<afk::Button>(*this, 20, 440, 2, "start")
      .setOnClick(std::bind(&Menu::handleClickStart, this));

  // Hide mouse
  display.hideMouse();

  // Play music
  if (config.get<bool>("music", false) == true) {
    audio.playStream("mainmenu");
  }
}

void Menu::stop() {
  // Stops music
  afk::AudioService& audio = afk::Services::getAudioService();
  audio.stopStream("mainmenu");
}

void Menu::closeMenu(MENU menu) {
  switch (menu) {
    case HELP:
      get<afk::Sprite>(help_sprite).setVisible(false);
      break;
    case CREDITS:
      get<afk::Sprite>(credits_sprite).setVisible(false);
      break;
    case HIGHSCORES:
      get<HighScores>(scores_screen).setOpen(false);
      break;
    case CONTROLS:
      get<afk::Sprite>(controls_sprite).setVisible(false);
      break;
    case SETTINGS:
      get<SettingsMenu>(settings_screen).setOpen(false);
      break;
    default:
      break;
  }

  // Reset open menu
  current_menu = MENU::NONE;
}

// Update loop
void Menu::update() {
  afk::InputService& input = afk::Services::getInputService();
  afk::SceneService& scene = afk::Services::getSceneService();

  // Start game with controller
  if (input.joyPressed(afk::JoystickButtons::JOY_XBOX_START) ||
      input.joyPressed(afk::JoystickButtons::JOY_XBOX_A)) {
    handleClickStart();
  }

  // CLose menu
  if (input.mousePressed(afk::MouseButtons::BUTTON_LEFT) ||
      input.anyKeyDown()) {
    closeMenu(current_menu);
  }

  // Close game
  if (input.keyPressed(afk::Keys::KEY_ESCAPE)) {
    scene.setNextScene("exit");
  }
}

// Click Start
void Menu::handleClickStart() {
  afk::SceneService& scene = afk::Services::getSceneService();

  if (current_menu == MENU::NONE) {
    scene.setNextScene("game");
  }
}

// Click settings button
void Menu::handleClickSettings() {
  if (current_menu == MENU::NONE) {
    get<SettingsMenu>(settings_screen).setOpen(true);
    current_menu = MENU::SETTINGS;
  }
}

// Click help button
void Menu::handleClickHelp() {
  if (current_menu == MENU::NONE) {
    get<afk::Sprite>(help_sprite).setVisible(true);
    current_menu = MENU::HELP;
  }
}

// Click credits button
void Menu::handleClickCredits() {
  if (current_menu == MENU::NONE) {
    get<afk::Sprite>(credits_sprite).setVisible(true);
    current_menu = MENU::CREDITS;
  }
}

// Click scores button
void Menu::handleClickScores() {
  if (current_menu == MENU::NONE) {
    get<HighScores>(scores_screen).setOpen(true);
    current_menu = MENU::HIGHSCORES;
  }
}

// Click controls button
void Menu::handleClickControls() {
  if (current_menu == MENU::NONE) {
    get<afk::Sprite>(controls_sprite).setVisible(true);
    current_menu = MENU::CONTROLS;
  }
}
