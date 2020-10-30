/*
 * Game scene
 * A.D.S. Games
 * 03/01/2016
 * Main game scene
 */
#ifndef SCENES_GAME_H
#define SCENES_GAME_H

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "../engine/audio/Sound.h"
#include "../engine/audio/Stream.h"
#include "../engine/fonts/Font.h"
#include "../engine/input/JoystickListener.h"
#include "../engine/input/KeyListener.h"
#include "../engine/input/MouseListener.h"
#include "../engine/scene/Scene.h"
#include "../engine/textures/Texture.h"
#include "../entities/Background.h"
#include "../entities/Energy.h"
#include "../entities/GameHud.h"
#include "../entities/PauseMenu.h"
#include "../entities/Robot.h"
#include "../entities/debris/Debris.h"
#include "../entities/powerups/Powerup.h"
#include "ScoreTable.h"

// Game class
class Game : public Scene {
 public:
  // Construct/deconstruct
  Game();
  virtual ~Game();

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

  // Gamehud
  GameHud hud;

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

  // Text input
  std::string edittext;
  std::string::iterator iter;

  // Containers of objects
  std::vector<std::unique_ptr<Energy>> energys;
  std::vector<std::unique_ptr<Debris>> debries;
  std::vector<std::unique_ptr<Powerup>> powerups;
};

#endif  // SCENES_GAME_H
