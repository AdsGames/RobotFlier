#include "Menu.h"

#include <functional>
#include <iostream>

#include "../constants/globals.h"
#include "../engine/entities/Sprite.h"
#include "../engine/random/RandomGenerator.h"
#include "../engine/ui/Button.h"
#include "../entities/menu/HighScores.h"
#include "../entities/menu/MouseRocket.h"
#include "../entities/menu/SettingsMenu.h"

// Construct scene
Menu::Menu() : current_menu(MENU::NONE) {
  // Load intro image
  // Random menu
  std::string background_image =
      "background_" + std::to_string(RandomGenerator::randomInt(0, 3));
  this->add<Sprite>(*this, background_image, 0.0f, 0.0f, 0);

  // Add mouse
  this->add<MouseRocket>(*this);

  // Add title
  this->add<Sprite>(*this, "title", 20, 20, 0);

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

  // Xbox start button
  if (this->getSettings().get<int>("controlMode", 0) != 1 &&
      this->getInput().joystick().enabled) {
    this->add<Sprite>(*this, "xbox_start", 240, 480, 3);
  }

  // Add credits button
  this->addObj<Button>(*this, 540, 548, 2, "ui_credits")
      .setOnClick(std::bind(&Menu::handleClickCredits, this));

  // Add help button
  this->addObj<Button>(*this, 696, 548, 2, "ui_help")
      .setOnClick(std::bind(&Menu::handleClickHelp, this));

  // Add settings button
  this->addObj<Button>(*this, 748, 548, 2, "ui_options")
      .setOnClick(std::bind(&Menu::handleClickSettings, this));

  // Add controls button
  this->addObj<Button>(*this, 644, 548, 2, "ui_controls")
      .setOnClick(std::bind(&Menu::handleClickControls, this));

  // Add highscores button
  this->addObj<Button>(*this, 660, 20, 2, "highscores")
      .setOnClick(std::bind(&Menu::handleClickScores, this));

  // Add start button
  this->addObj<Button>(*this, 20, 440, 2, "start")
      .setOnClick(std::bind(&Menu::handleClickStart, this));

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

void Menu::closeMenu(MENU menu) {
  switch (menu) {
    case HELP:
      this->get<Sprite>(help_sprite).setVisible(false);
      break;
    case CREDITS:
      this->get<Sprite>(credits_sprite).setVisible(false);
      break;
    case HIGHSCORES:
      this->get<HighScores>(scores_screen).setOpen(false);
      break;
    case CONTROLS:
      this->get<Sprite>(controls_sprite).setVisible(false);
      break;
    case SETTINGS:
      this->get<SettingsMenu>(settings_screen).setOpen(false);
      break;
    default:
      break;
  }

  // Reset open menu
  current_menu = MENU::NONE;
}

// Update loop
void Menu::update() {
  // Start game with controller
  if (this->getInput().joystick().buttonPressed[JOY_XBOX_START] ||
      this->getInput().joystick().buttonPressed[JOY_XBOX_A]) {
    handleClickStart();
  }

  // CLose menu
  if (this->getInput().mouse().down[1] ||
      this->getInput().keyboard().anyKeyPressed) {
    closeMenu(current_menu);
  }

  // Close game
  if (this->getInput().keyboard().key[ALLEGRO_KEY_ESCAPE]) {
    Scene::setNextScene(SCENE_EXIT);
  }
}

// Click Start
void Menu::handleClickStart() {
  if (current_menu == MENU::NONE) {
    Scene::setNextScene(SCENE_GAME);
  }
}

// Click settings button
void Menu::handleClickSettings() {
  if (current_menu == MENU::NONE) {
    this->get<SettingsMenu>(settings_screen).setOpen(true);
    current_menu = MENU::SETTINGS;
  }
}

// Click help button
void Menu::handleClickHelp() {
  if (current_menu == MENU::NONE) {
    this->get<Sprite>(help_sprite).setVisible(true);
    current_menu = MENU::HELP;
  }
}

// Click credits button
void Menu::handleClickCredits() {
  if (current_menu == MENU::NONE) {
    this->get<Sprite>(credits_sprite).setVisible(true);
    current_menu = MENU::CREDITS;
  }
}

// Click scores button
void Menu::handleClickScores() {
  if (current_menu == MENU::NONE) {
    this->get<HighScores>(scores_screen).setOpen(true);
    current_menu = MENU::HIGHSCORES;
  }
}

// Click controls button
void Menu::handleClickControls() {
  if (current_menu == MENU::NONE) {
    this->get<Sprite>(controls_sprite).setVisible(true);
    current_menu = MENU::CONTROLS;
  }
}
