/*
 * Game state
 * A.D.S. Games
 * 03/01/2016
 * Main game state
 */
#ifndef STATE_GAME_H
#define STATE_GAME_H

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

#include "../engine/Audio/Sound.h"
#include "../engine/Audio/Stream.h"
#include "../engine/Fonts/Font.h"
#include "../engine/Input/JoystickListener.h"
#include "../engine/Input/KeyListener.h"
#include "../engine/Input/MouseListener.h"
#include "../engine/State.h"
#include "../engine/Textures/Texture.h"
#include "../entities/Energy.h"
#include "../entities/Robot.h"
#include "../entities/debris/Debris.h"
#include "../entities/powerups/Powerup.h"
#include "ScoreTable.h"

// Game class
class game : public state {
 public:
  // Construct/deconstruct
  game();
  virtual ~game();

  // Override parent
  virtual void update() override;
  virtual void draw() override;

 private:
  // Score table
  ScoreTable highscores;

  // Change theme
  void changeTheme(int NewThemeNumber);

  // Declare bitmaps
  ALLEGRO_BITMAP* screenshot;

  // Game images
  Texture space;
  Texture parallaxBack;
  Texture groundOverlay;
  Texture groundUnderlay;

  // GUI Images
  Texture debug;
  Texture pauseMenu;
  Texture ui_game_end;
  Texture ui_a;
  Texture ui_b;
  Texture ui_up;

  // Powerup Images
  Texture powerStar;
  Texture powerMagnet;

  // Declare sounds
  Sound sound_snap;

  // Music
  Stream music_ingame;
  Stream music_death;

  // Fonts
  Font orbitron_12;
  Font orbitron_18;
  Font orbitron_24;
  Font orbitron_30;

  // Our robot
  Robot hectar;

  // Declare integers
  int scroll;
  int themeNumber;
  int screenshake_x;
  int screenshake_y;
  double arrow_animation;
  float motion;

  // Declare booleans
  bool paused;

  // Text input
  std::string edittext;
  std::string::iterator iter;

  // Containers of objects
  std::vector<Energy> energys;
  std::vector<std::unique_ptr<Debris>> debries;
  std::vector<std::unique_ptr<Powerup>> powerups;
};

#endif  // STATE_GAME_H
