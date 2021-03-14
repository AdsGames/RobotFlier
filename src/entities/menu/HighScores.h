/*
 * Mouse Rocket
 * Allan Legemaate
 * Renders game settings menu
 * 01/11/2020
 */
#ifndef SRC_ENTITIES_MENU_HIGHSCORES_H_
#define SRC_ENTITIES_MENU_HIGHSCORES_H_

#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

#include "ScoreTable.h"

class HighScores : public afk::GameObject {
 public:
  // Constructor
  explicit HighScores(afk::Scene& scene);

 private:
  // Score table
  ScoreTable highscores;
};

#endif  // SRC_ENTITIES_MENU_HIGHSCORES_H_
