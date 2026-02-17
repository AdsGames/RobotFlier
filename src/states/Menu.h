/*
 * Menu
 * A.D.S. Games
 * 03/01/2016
 * The menu of Robot Flier
 */
#pragma once

constexpr int MINISTATE_MENU     = 0;
constexpr int MINISTATE_TUTORIAL = 1;
constexpr int MINISTATE_CREDITS  = 2;
constexpr int MINISTATE_OPTIONS  = 3;
constexpr int MINISTATE_CONTROLS = 4;
constexpr int MINISTATE_SCORES   = 5;

#include <asw/asw.h>
#include <time.h>
#include <array>
#include <vector>

#include "../constants/globals.h"
#include "ScoreTable.h"
#include "State.h"

class MenuScene : public asw::scene::Scene<Scenes> {
 public:
  static constexpr float ANIMATION_DURATION = 1.3F;

  using asw::scene::Scene<Scenes>::Scene;

  // Override parent
  void init() override;
  void update(float deltaTime) override;
  void draw() override;

 private:
  // Score table
  ScoreTable highscores;

  // Particle emitter
  asw::ParticleEmitter emitter;

  // Vars
  float animation_ticker;

  int  mini_screen;
  bool startClicked;

  // Screens
  asw::game::Sprite img_menu;
  asw::game::Sprite options;
  asw::game::Sprite helpScreen;
  asw::game::Sprite controls;
  asw::game::Sprite credits;
  asw::game::Sprite highscores_table;

  // Buttons
  asw::game::Sprite start;
  asw::game::Sprite title;
  asw::game::Sprite highscores_button;

  // Start button for xbox control
  asw::game::Sprite xbox_start;

  // Options menu
  asw::game::Sprite ui_sound[2];
  asw::game::Sprite ui_music[2];
  asw::game::Sprite ui_screenshake[4];
  asw::game::Sprite ui_window[2];
  asw::game::Sprite ui_particle[4];
  asw::game::Sprite ui_control[3];

  asw::game::Sprite ui_options;
  asw::game::Sprite ui_back;
  asw::game::Sprite ui_credits;
  asw::game::Sprite ui_exit;
  asw::game::Sprite ui_help;
  asw::game::Sprite ui_controls;

  // Music
  asw::Music music_mainmenu;
};
