/*
 * Menu
 * A.D.S. Games
 * 03/01/2016
 * The menu of Robot Flier
 */
#ifndef SCENES_MENU_H
#define SCENES_MENU_H

#define MINISTATE_MENU 0
#define MINISTATE_TUTORIAL 1
#define MINISTATE_CREDITS 2
#define MINISTATE_OPTIONS 3
#define MINISTATE_CONTROLS 4
#define MINISTATE_SCORES 5

#include <time.h>

#include <vector>

#include "../engine/audio/Stream.h"
#include "../engine/fonts/Font.h"
#include "../engine/particles/Particle.h"
#include "../engine/scene/Scene.h"
#include "../engine/textures/Texture.h"
#include "../helpers/tools.h"
#include "ScoreTable.h"

class menu : public Scene {
 public:
  // Construct/deconstruct
  menu();
  virtual ~menu();

  // Override parent
  virtual void update() override;
  virtual void draw() override;

 private:
  // Settings
  static void readSettings();
  static void writeSettings();

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

  // Screens
  Texture img_menu;
  Texture options;
  Texture helpScreen;
  Texture controls;
  Texture credits;
  Texture highscores_table;

  // Buttons
  Texture start;
  Texture title;
  Texture highscores_button;

  // Mouse
  Texture mouse;
  Texture mouse_rocket;

  // Start button for xbox control
  Texture xbox_start;

  // Options menu
  Texture ui_sound[2];
  Texture ui_music[2];
  Texture ui_screenshake[4];
  Texture ui_window[2];
  Texture ui_particle[4];
  Texture ui_control[3];

  Texture ui_options;
  Texture ui_options_small;
  Texture ui_back;
  Texture ui_credits;
  Texture ui_exit;
  Texture ui_help;
  Texture ui_screenshot_notification;
  Texture ui_controls;

  // Fonts
  Font orbitron_36;
  Font orbitron_24;
  Font orbitron_18;
  Font orbitron_12;
};

#endif  // SCENES_MENU_H
