#include "HighScores.h"

#include <afk/color/Color.h>
#include <afk/services/Services.h>
#include <iostream>

HighScores::HighScores(afk::Scene& scene)
    : GameObject(scene, 0, 0, 3), open(false) {
  afk::AssetService& assets = afk::Services::getAssetService();
  highscores_table = assets.getImage("highscores_table");
  orbitron_36 = assets.getFont("orbitron_36");
  orbitron_24 = assets.getFont("orbitron_24");
  orbitron_18 = assets.getFont("orbitron_18");
}

void HighScores::draw() {
  // Do not display if closed
  if (!open) {
    return;
  }

  // Highscore background
  highscores_table.draw(200, 50);

  // Title
  orbitron_36.draw(400, 75, "Highscores", afk::color::rgb(0, 0, 0),
                   afk::FontAlign::ALIGN_CENTER);

  // Read the top 10 scores
  for (int i = 0; i < 10; i++) {
    orbitron_24.draw(250, (i * 40) + 130,
                     std::to_string(highscores.getScore(i)),
                     afk::color::rgb(0, 0, 0), afk::FontAlign::ALIGN_CENTER);
    orbitron_18.draw(575, (i * 40) + 132, highscores.getName(i),
                     afk::color::rgb(0, 0, 0), afk::FontAlign::ALIGN_RIGHT);
  }
}

// Set open statet
void HighScores::setOpen(const bool open) {
  this->open = open;
}
