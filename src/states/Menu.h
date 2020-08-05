/*
 * Menu
 * A.D.S. Games
 * 03/01/2016
 * The menu of Robot Flier
 */
#ifndef STATE_MENU_H
#define STATE_MENU_H

#define MINISTATE_MENU 0
#define MINISTATE_TUTORIAL 1
#define MINISTATE_CREDITS 2
#define MINISTATE_OPTIONS 3
#define MINISTATE_CONTROLS 4
#define MINISTATE_SCORES 5

#include <time.h>

#include <vector>

#include "../engine/Particles/Particle.h"
#include "../engine/State.h"
#include "../helpers/tools.h"
#include "ScoreTable.h"

class menu : public state {
 public:
  // Construct/deconstruct
  menu();
  virtual ~menu();

  // Override parent
  virtual void update() override;
  virtual void draw() override;

 private:
  // Settings
  static void read_settings();
  static void write_settings();

  // Score table
  ScoreTable highscores;

  // Vars
  int animation_pos;

  int mouseMove;
  int mini_screen;
  bool startMove;
  bool startClicked;
  bool mouse_rocket_up;

  // Particles
  std::vector<Particle> mousePart;
  std::vector<Particle> menuPart;

  // Images
  ALLEGRO_BITMAP* buffer;

  // Screens
  ALLEGRO_BITMAP* img_menu;
  ALLEGRO_BITMAP* options;
  ALLEGRO_BITMAP* helpScreen;
  ALLEGRO_BITMAP* controls;
  ALLEGRO_BITMAP* credits;
  ALLEGRO_BITMAP* highscores_table;

  // Buttons
  ALLEGRO_BITMAP* start;
  ALLEGRO_BITMAP* title;
  ALLEGRO_BITMAP* highscores_button;

  // Mouse
  ALLEGRO_BITMAP* mouse;
  ALLEGRO_BITMAP* mouse_rocket;

  // Start button for xbox control
  ALLEGRO_BITMAP* xbox_start;

  // Options menu
  ALLEGRO_BITMAP* ui_sound[2];
  ALLEGRO_BITMAP* ui_music[2];
  ALLEGRO_BITMAP* ui_screenshake[4];
  ALLEGRO_BITMAP* ui_window[2];
  ALLEGRO_BITMAP* ui_particle[4];
  ALLEGRO_BITMAP* ui_control[3];

  ALLEGRO_BITMAP* ui_options;
  ALLEGRO_BITMAP* ui_options_small;
  ALLEGRO_BITMAP* ui_back;
  ALLEGRO_BITMAP* ui_credits;
  ALLEGRO_BITMAP* ui_exit;
  ALLEGRO_BITMAP* ui_help;
  ALLEGRO_BITMAP* ui_screenshot_notification;
  ALLEGRO_BITMAP* ui_controls;

  // Music
  ALLEGRO_SAMPLE* music_mainmenu;
};

#endif  // STATE_MENU_H
