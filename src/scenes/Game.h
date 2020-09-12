/*
 * Game scene
 * A.D.S. Games
 * 03/01/2016
 * Main game scene
 */
#ifndef SCNES_GAME_H
#define SCNES_GAME_H

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "../engine/Audio/Sound.h"
#include "../engine/Audio/Stream.h"
#include "../engine/Fonts/Font.h"
#include "../engine/Input/JoystickListener.h"
#include "../engine/Input/KeyListener.h"
#include "../engine/Input/MouseListener.h"
#include "../engine/Scene.h"
#include "../engine/Textures/Texture.h"
#include "../entities/Background.h"
#include "../entities/Energy.h"
#include "../entities/PauseMenu.h"
#include "../entities/Robot.h"
#include "../entities/debris/Debris.h"
#include "../entities/powerups/Powerup.h"
#include "ScoreTable.h"

// Game class
class game : public Scene {
 public:
  // Construct/deconstruct
  game();
  virtual ~game();

  // Override parent
  virtual void update() override;
  virtual void draw() override;

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

  // Background of world
  Background worldBackground;

  // Pause menu
  PauseMenu pauseMenu;

  // Fonts
  Font orbitron_12;
  Font orbitron_18;
  Font orbitron_24;
  Font orbitron_30;

  // Our robot
  Robot hectar;

  // Declare integers
  int themeNumber;
  int screenshake_x;
  int screenshake_y;
  double arrow_animation;
  float motion;

  // Text input
  std::string edittext;
  std::string::iterator iter;

  // Containers of objects
  std::vector<Energy> energys;
  std::vector<std::unique_ptr<Debris>> debries;
  std::vector<std::unique_ptr<Powerup>> powerups;
};

#endif  // SCNES_GAME_H
