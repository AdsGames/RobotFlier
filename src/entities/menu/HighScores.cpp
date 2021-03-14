#include "HighScores.h"

#include <afk/color/Color.h>
#include <afk/entities/Sprite.h>
#include <afk/entities/ui/Label.h>

HighScores::HighScores(afk::Scene& scene) : GameObject(scene, 0, 0, 3) {
  auto& spr_back = scene.add<afk::Sprite>(scene, 200, 50, z + 1);
  spr_back.setTexture("highscores_table");
  spr_back.setParent(id);

  auto& lbl_title = scene.add<afk::Label>(scene, 400, 75, z + 2);
  lbl_title.setFont("orbitron_36");
  lbl_title.setText("Highscores");
  lbl_title.setTextAlign(afk::TextAlign::CENTER);
  lbl_title.setParent(id);

  // Read the top 10 scores
  for (int i = 0; i < 10; i++) {
    auto& lbl_score = scene.add<afk::Label>(scene, 250, (i * 40) + 130, z + 2);
    lbl_score.setFont("orbitron_24");
    lbl_score.setText(std::to_string(highscores.getScore(i)));
    lbl_score.setTextAlign(afk::TextAlign::CENTER);
    lbl_score.setParent(id);

    auto& lbl_name = scene.add<afk::Label>(scene, 575, (i * 40) + 130, z + 2);
    lbl_name.setFont("orbitron_18");
    lbl_name.setText(highscores.getName(i));
    lbl_name.setTextAlign(afk::TextAlign::RIGHT);
    lbl_name.setParent(id);
  }
}
