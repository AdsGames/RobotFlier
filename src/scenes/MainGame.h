/*
 * Game scene
 * A.D.S. Games
 * 03/01/2016
 * Main game scene
 */
#ifndef SCENES_MAIN_GAME_H
#define SCENES_MAIN_GAME_H

#include <afk/assets/Font.h>
#include <afk/assets/Texture.h>
#include <afk/scene/Scene.h>

#include "../entities/menu/ScoreTable.h"

// Game class
class MainGame : public afk::Scene {
 public:
  // Override parent
  virtual void start() override;
  virtual void update() override;
  virtual void draw() override;
  virtual void stop() override;

 private:
  void spawnObjects();
  void takeScreenshot();

  // Score table
  ScoreTable highscores;

  // Change theme
  void changeTheme(int NewThemeNumber);

  // GUI Images
  afk::Texture debug;
  afk::Texture ui_game_end;
  afk::Texture ui_a;
  afk::Texture ui_b;
  afk::Texture ui_up;

  // Powerup Images
  afk::Texture powerStar;
  afk::Texture powerMagnet;

  // Fonts
  afk::Font orbitron_18;
  afk::Font orbitron_24;

  // Our robot
  ObjId hectar_id;

  // Pause menu
  ObjId pause_menu_id;

  // Declare integers
  int themeNumber;
  int screenshake_x;
  int screenshake_y;
  double arrow_animation;

  // Text input
  std::string edittext;
  std::string::iterator iter;
};

#endif  // SCENES_MAIN_GAME_H
