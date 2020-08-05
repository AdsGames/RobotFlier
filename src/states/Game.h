/*
 * Game state
 * A.D.S. Games
 * 03/01/2016
 * Main game state
 */
#ifndef STATE_GAME_H
#define STATE_GAME_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include "../engine/Input/JoystickListener.h"
#include "../engine/Input/KeyListener.h"
#include "../engine/Input/MouseListener.h"
#include "../engine/Particles/Particle.h"
#include "../engine/State.h"
#include "../entities/Debris.h"
#include "../entities/Energy.h"
#include "../entities/Powerup.h"
#include "../entities/Robot.h"
#include "../helpers/tools.h"
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
  ALLEGRO_BITMAP* space;
  ALLEGRO_BITMAP* parallaxBack;
  ALLEGRO_BITMAP* groundOverlay;
  ALLEGRO_BITMAP* groundUnderlay;

  // GUI Images
  ALLEGRO_BITMAP* debug;
  ALLEGRO_BITMAP* pauseMenu;
  ALLEGRO_BITMAP* ui_game_end;
  ALLEGRO_BITMAP* ui_a;
  ALLEGRO_BITMAP* ui_b;
  ALLEGRO_BITMAP* ui_up;

  // Danger images
  ALLEGRO_BITMAP* energyImage;
  ALLEGRO_BITMAP* asteroidImage;
  ALLEGRO_BITMAP* bombImage;
  ALLEGRO_BITMAP* cometImage;

  // Powerup Images
  ALLEGRO_BITMAP* powerStar;
  ALLEGRO_BITMAP* powerMagnet[4];

  // Declare sounds
  ALLEGRO_SAMPLE* sound_orb;
  ALLEGRO_SAMPLE* sound_bomb;
  ALLEGRO_SAMPLE* sound_asteroid;
  ALLEGRO_SAMPLE* sound_magnet;
  ALLEGRO_SAMPLE* sound_star;
  ALLEGRO_SAMPLE* sound_snap;

  // Music
  ALLEGRO_SAMPLE* music_ingame;
  ALLEGRO_SAMPLE* music_death;

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
  std::vector<Debris> debries;
  std::vector<Powerup> powerups;
};

#endif  // STATE_GAME_H
