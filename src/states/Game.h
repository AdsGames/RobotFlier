/*
 * Game state
 * A.D.S. Games
 * 03/01/2016
 * Main game state
 */
#ifndef GAME_H
#define GAME_H

#include <asw/asw.h>

#include "../constants/globals.h"
#include "../entities/Debris.h"
#include "../entities/Energy.h"
#include "../entities/Powerup.h"
#include "../entities/Robot.h"
#include "ScoreTable.h"
#include "State.h"

// Game class
class GameScene : public asw::scene::Scene<Scenes> {
 public:
  using asw::scene::Scene<Scenes>::Scene;

  // Override parent
  void init() override;
  void update(float deltaTime) override;
  void draw() override;

 private:
  // Score table
  ScoreTable highscores;

  // Change theme
  void changeTheme(int NewThemeNumber);

  // Ticker
  void  gameTick();
  void  spawnWave();
  float difficulty() const;

  // Declare bitmaps
  asw::Texture screenshot;

  // Game images
  asw::Texture space;
  asw::Texture parallaxBack;
  asw::Texture groundOverlay;
  asw::Texture groundUnderlay;

  // GUI Images
  asw::Texture debug;
  asw::Texture pauseMenu;
  asw::Texture ui_game_end;
  asw::Texture ui_a;
  asw::Texture ui_b;
  asw::Texture ui_up;

  // Danger images
  asw::Texture energyImage;
  asw::Texture asteroidImage;
  asw::Texture bombImage;
  asw::Texture cometImage;

  // Powerup Images
  asw::Texture powerStar;
  asw::Texture powerMagnet[4];

  // Declare sounds
  asw::Sample sound_orb;
  asw::Sample sound_bomb;
  asw::Sample sound_asteroid;
  asw::Sample sound_magnet;
  asw::Sample sound_star;
  asw::Sample sound_snap;

  // Music
  asw::Music music_ingame;
  asw::Music music_death;

  // Our robot
  Robot hectar;

  // Declare integers
  float scroll;
  int   themeNumber;
  int   screenshake_x;
  int   screenshake_y;
  float arrow_animation;
  float motion;
  float ticker;

  // Declare booleans
  bool paused;

  // Text input
  std::string           edittext;
  std::string::iterator iter;

  // Containers of objects
  std::vector<Energy>  energys;
  std::vector<Debris>  debries;
  std::vector<Powerup> powerups;
};

#endif  // GAME_H
