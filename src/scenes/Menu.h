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

#include <vector>

#include "../engine/audio/Stream.h"
#include "../engine/fonts/Font.h"
#include "../engine/particles/Particle.h"
#include "../engine/scene/Scene.h"
#include "../engine/textures/Texture.h"
#include "../helpers/tools.h"

class Menu : public Scene {
 public:
  // Construct/deconstruct
  Menu();
  virtual ~Menu();

  // Override parent
  virtual void update() override;
  virtual void draw() override;

 private:
  // Settings
  static void readSettings();
  static void writeSettings();

  // Vars
  int animation_pos;
  int mini_screen;
  bool startMove;
  bool startClicked;

  // Screens
  Texture img_menu;
  Texture helpScreen;
  Texture controls;
  Texture credits;

  // Buttons
  Texture start;
  Texture title;
  Texture highscores_button;

  // Start button for xbox control
  Texture xbox_start;

  Texture ui_credits;
  Texture ui_help;
  Texture ui_controls;
  Texture ui_options;

  unsigned int settings_screen;
  unsigned int scores_screen;
  unsigned int help_sprite;
  unsigned int credits_sprite;
  unsigned int controls_sprite;
  unsigned int mouse_rocket;
};

#endif  // SCENES_MENU_H
