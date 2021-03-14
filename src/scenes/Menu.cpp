#include "Menu.h"

#include <afk/entities/Sprite.h>
#include <afk/entities/ui/Image.h>
#include <afk/random/RandomGenerator.h>

#include <functional>
#include <iostream>
#include <string>

#include "../constants/globals.h"
#include "../entities/menu/HighScores.h"
#include "../entities/menu/MouseRocket.h"
#include "../entities/menu/SettingsMenu.h"

// Construct scene
void Menu::start() {
  current_menu = MenuState::NONE;

  // Load intro image
  // Random menu
  std::string background_image =
      "background_" + std::to_string(afk::Random::randomInt(0, 3));
  add<afk::Sprite>(*this, background_image, 0.0f, 0.0f, 0);

  // Add mouse
  add<MouseRocket>(*this);

  // Add title
  add<afk::Sprite>(*this, "title", 20, 20, 1);

  // Add settings screen component
  SettingsMenu& settings = add<SettingsMenu>(*this);
  settings.setHooked(false);
  settings_screen = settings.id;

  // Add highscores component
  HighScores& scores = add<HighScores>(*this);
  scores.setHooked(false);
  scores_screen = scores.id;

  // Add help sprite
  afk::Sprite& help = add<afk::Sprite>(*this, "helpScreen", 0, 0, 10);
  help.setHooked(false);
  help_sprite = help.id;

  // Add credits sprite
  afk::Sprite& credits = add<afk::Sprite>(*this, "credits", 0, 0, 10);
  credits.setHooked(false);
  credits_sprite = credits.id;

  // Add controls sprite
  afk::Sprite& controls = add<afk::Sprite>(*this, "controls", 0, 0, 10);
  controls.setHooked(false);
  controls_sprite = controls.id;

  // Xbox start button
  if (config.get<int>("controlMode", 0) != 1 && input.joyEnabled()) {
    add<afk::Sprite>(*this, "xbox_start", 240, 480, 3);
  }

  // Add credits button
  afk::Image& ui_credits = add<afk::Image>(*this, 540, 548, 2);
  ui_credits.setOnClick(std::bind(&Menu::handleClickCredits, this));
  ui_credits.setTexture("ui_credits");

  // Add help button
  afk::Image& ui_help = add<afk::Image>(*this, 696, 548, 2);
  ui_help.setOnClick(std::bind(&Menu::handleClickHelp, this));
  ui_help.setTexture("ui_help");

  // Add settings button
  afk::Image& ui_options = add<afk::Image>(*this, 748, 548, 2);
  ui_options.setOnClick(std::bind(&Menu::handleClickSettings, this));
  ui_options.setTexture("ui_options");

  // Add controls button
  afk::Image& ui_controls = add<afk::Image>(*this, 644, 548, 2);
  ui_controls.setOnClick(std::bind(&Menu::handleClickControls, this));
  ui_controls.setTexture("ui_controls");

  // Add highscores button
  afk::Image& ui_highscores = add<afk::Image>(*this, 660, 20, 2);
  ui_highscores.setOnClick(std::bind(&Menu::handleClickScores, this));
  ui_highscores.setTexture("highscores");

  // Add start button
  afk::Image& ui_start = add<afk::Image>(*this, 20, 440, 2);
  ui_start.setOnClick(std::bind(&Menu::handleClickStart, this));
  ui_start.setTexture("start");

  // Hide mouse
  display.hideMouse();

  // Play music
  if (config.get<bool>("music", false)) {
    audio.playStream("mainmenu");
  }
}

void Menu::stop() {
  // Stops music
  audio.stopStream("mainmenu");
}

void Menu::closeMenu(MenuState menu) {
  switch (menu) {
    case MenuState::HELP:
      get<afk::Sprite>(help_sprite).setHooked(false);
      break;
    case MenuState::CREDITS:
      get<afk::Sprite>(credits_sprite).setHooked(false);
      break;
    case MenuState::HIGHSCORES:
      get<HighScores>(scores_screen).setHooked(false);
      break;
    case MenuState::CONTROLS:
      get<afk::Sprite>(controls_sprite).setHooked(false);
      break;
    default:
      break;
  }

  // Reset open menu
  current_menu = MenuState::NONE;
}

// Update loop
void Menu::update(Uint32 delta) {
  // Start game with controller
  if (input.joyPressed(afk::JoystickButtons::START) ||
      input.joyPressed(afk::JoystickButtons::A)) {
    handleClickStart();
  }

  // CLose menu
  if (input.mousePressed(afk::MouseButtons::LEFT) || input.anyKeyDown()) {
    closeMenu(current_menu);
  }

  // Close game
  if (input.keyPressed(afk::Keys::ESCAPE)) {
    scene.setNextScene("exit");
  }

  Scene::update(delta);
}

// Click Start
void Menu::handleClickStart() {
  if (current_menu == MenuState::NONE) {
    scene.setNextScene("game");
  }
}

// Click settings button
void Menu::handleClickSettings() {
  if (current_menu == MenuState::NONE) {
    get<SettingsMenu>(settings_screen).setHooked(true);
    current_menu = MenuState::SETTINGS;
  }
}

// Click help button
void Menu::handleClickHelp() {
  if (current_menu == MenuState::NONE) {
    get<afk::Sprite>(help_sprite).setHooked(true);
    current_menu = MenuState::HELP;
  }
}

// Click credits button
void Menu::handleClickCredits() {
  if (current_menu == MenuState::NONE) {
    get<afk::Sprite>(credits_sprite).setHooked(true);
    current_menu = MenuState::CREDITS;
  }
}

// Click scores button
void Menu::handleClickScores() {
  if (current_menu == MenuState::NONE) {
    get<HighScores>(scores_screen).setHooked(true);
    current_menu = MenuState::HIGHSCORES;
  }
}

// Click controls button
void Menu::handleClickControls() {
  if (current_menu == MenuState::NONE) {
    get<afk::Sprite>(controls_sprite).setHooked(true);
    current_menu = MenuState::CONTROLS;
  }
}
