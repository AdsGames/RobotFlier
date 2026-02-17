/*
 * Menu
 * A.D.S. Games
 * 03/01/2016
 * The menu of Robot Flier
 */
#ifndef MENU_H
#define MENU_H

#define MINISTATE_MENU 0
#define MINISTATE_TUTORIAL 1
#define MINISTATE_CREDITS 2
#define MINISTATE_OPTIONS 3
#define MINISTATE_CONTROLS 4
#define MINISTATE_SCORES 5

#include <asw/asw.h>
#include <time.h>
#include <vector>

#include "../constants/globals.h"
#include "../entities/Particle.h"
#include "../helpers/tools.h"
#include "ScoreTable.h"
#include "State.h"

class MenuScene : public asw::scene::Scene<Scenes> {
 public:
  using asw::scene::Scene<Scenes>::Scene;

  // Override parent
  void init() override;
  void update(float deltaTime) override;
  void draw() override;

 private:
  // Settings
  static void read_settings();
  static void write_settings();

  // Score table
  ScoreTable highscores;

  // Vars
  int animation_pos;

  float mouseMove;
  int   mini_screen;
  bool  startMove;
  bool  startClicked;
  bool  mouse_rocket_up;

  // Particles
  std::vector<Particle> mousePart;
  std::vector<Particle> menuPart;

  // Screens
  asw::Texture img_menu;
  asw::Texture options;
  asw::Texture helpScreen;
  asw::Texture controls;
  asw::Texture credits;
  asw::Texture highscores_table;

  // Buttons
  asw::Texture start;
  asw::Texture title;
  asw::Texture highscores_button;

  // Mouse
  asw::Texture mouse;
  asw::Texture mouse_rocket;

  // Start button for xbox control
  asw::Texture xbox_start;

  // Options menu
  asw::Texture ui_sound[2];
  asw::Texture ui_music[2];
  asw::Texture ui_screenshake[4];
  asw::Texture ui_window[2];
  asw::Texture ui_particle[4];
  asw::Texture ui_control[3];

  asw::Texture ui_options;
  asw::Texture ui_options_small;
  asw::Texture ui_back;
  asw::Texture ui_credits;
  asw::Texture ui_exit;
  asw::Texture ui_help;
  asw::Texture ui_screenshot_notification;
  asw::Texture ui_controls;

  // Music
  asw::Music music_mainmenu;
};

#endif  // MENU_H
