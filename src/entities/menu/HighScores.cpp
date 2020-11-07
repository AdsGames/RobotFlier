#include "HighScores.h"

#include <iostream>

HighScores::HighScores(Scene& scene) : GameObject(scene, 0, 0, 3), open(false) {
  highscores_table = scene.getAsset().getImage("highscores_table");
  orbitron_36 = scene.getAsset().getFont("orbitron_36");
  orbitron_24 = scene.getAsset().getFont("orbitron_24");
  orbitron_18 = scene.getAsset().getFont("orbitron_18");
}

void HighScores::draw() {
  // Do not display if closed
  if (!open) {
    return;
  }

  // Highscore background
  highscores_table.draw(200, 50);

  // Title
  orbitron_36.draw(400, 75, "Highscores", al_map_rgb(0, 0, 0),
                   ALLEGRO_ALIGN_CENTRE);

  // Read the top 10 scores
  for (int i = 0; i < 10; i++) {
    orbitron_24.draw(250, (i * 40) + 130,
                     std::to_string(highscores.getScore(i)),
                     al_map_rgb(0, 0, 0), ALLEGRO_ALIGN_CENTRE);
    orbitron_18.draw(575, (i * 40) + 132, highscores.getName(i),
                     al_map_rgb(0, 0, 0), ALLEGRO_ALIGN_RIGHT);
  }
}

// Set open statet
void HighScores::setOpen(const bool open) {
  this->open = open;
}
