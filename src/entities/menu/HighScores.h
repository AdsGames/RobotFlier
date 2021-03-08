/*
 * Mouse Rocket
 * Allan Legemaate
 * Renders game settings menu
 * 01/11/2020
 */
#ifndef ENTITIES_MENU_HIGH_SCORES_H
#define ENTITIES_MENU_HIGH_SCORES_H

#include <afk/assets/Font.h>
#include <afk/assets/Texture.h>
#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>
#include "ScoreTable.h"

class HighScores : public afk::GameObject {
 public:
  // Constructor
  explicit HighScores(afk::Scene& scene);

  // Draw override
  virtual void draw() override;

  // Open and close
  void setOpen(const bool open);

 private:
  // Openstate
  bool open;

  // Score table
  ScoreTable highscores;

  // Textures
  afk::Texture highscores_table;

  // Fonts
  afk::Font orbitron_36;
  afk::Font orbitron_24;
  afk::Font orbitron_18;
};

#endif  // ENTITIES_MENU_HIGH_SCORES_H
