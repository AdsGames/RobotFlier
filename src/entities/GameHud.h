/*
 * Game Hud
 * A.D.S. Games
 * 30/10/2020
 * Game hud
 */
#ifndef ENTITIES_GAMEHUD_H
#define ENTITIES_GAMEHUD_H

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include "../engine/fonts/Font.h"
#include "../engine/textures/Texture.h"
#include "../entities/Robot.h"
#include "../scenes/ScoreTable.h"

// Game class
class GameHud {
 public:
  GameHud();

  void update(const float motion);

  void draw(const Robot& robot,
            const ScoreTable& highscores,
            const int num_energy,
            const int num_powerup,
            const int num_debris,
            const int themenumber);

 private:
  // GUI Images
  Texture debug;

  // Powerup Images
  Texture powerStar;
  Texture powerMagnet;

  // Fonts
  Font orbitron_12;
  Font orbitron_18;
  Font orbitron_24;
  Font orbitron_30;
};

#endif  // ENTITIES_GAMEHUD_H
