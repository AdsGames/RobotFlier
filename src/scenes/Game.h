/*
 * Game scene
 * A.D.S. Games
 * 03/01/2016
 * Main game scene
 */
#ifndef SCENES_GAME_H
#define SCENES_GAME_H

#include "../engine/fonts/Font.h"
#include "../engine/scene/Scene.h"
#include "../engine/textures/Texture.h"
#include "../entities/menu/ScoreTable.h"

// Game class
class Game : public Scene {
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

  // Declare bitmaps
  ALLEGRO_BITMAP* screenshot;

  // GUI Images
  Texture debug;
  Texture ui_game_end;
  Texture ui_a;
  Texture ui_b;
  Texture ui_up;

  // Powerup Images
  Texture powerStar;
  Texture powerMagnet;

  // Fonts
  Font orbitron_18;
  Font orbitron_24;

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

#endif  // SCENES_GAME_H
