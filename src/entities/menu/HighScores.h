/*
 * Mouse Rocket
 * Allan Legemaate
 * Renders game settings menu
 * 01/11/2020
 */
#ifndef ENTITIES_MENU_HIGH_SCORES_H
#define ENTITIES_MENU_HIGH_SCORES_H

#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>
#include <afk/textures/Texture.h>
#include "ScoreTable.h"

class HighScores : public GameObject {
 public:
  // Constructor
  explicit HighScores(Scene& scene);

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
  Texture highscores_table;

  // Fonts
  Font orbitron_36;
  Font orbitron_24;
  Font orbitron_18;
};

#endif  // ENTITIES_MENU_HIGH_SCORES_H
