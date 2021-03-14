#include "DieMenu.h"

#include <afk/common/str.h>
#include <afk/entities/Sprite.h>
#include <afk/entities/ui/Inputbox.h>
#include <afk/entities/ui/Label.h>

#include "../constants/globals.h"

DieMenu::DieMenu(afk::Scene& scene) : GameObject(scene, 0, 0, 20) {
  // Load scores
  highscores = ScoreTable("data/scores.dat");

  // Add images
  scene.add<afk::Sprite>(scene, "ui_game_end", 0, 0, z).setParent(id);
  scene.add<afk::Sprite>(scene, "ui_b", 370, 450, z).setParent(id);

  // Add Input box
  auto& inp_name = scene.add<afk::Inputbox>(scene, 120, 388, z + 1);
  inp_name.setFont("orbitron_24");
  inp_name.setText("Player");
  inp_name.setParent(id);
  inp_name_id = inp_name.id;

  // Add lables
  auto& lbl_prompt = scene.add<afk::Label>(scene, 150, 450, z + 1);
  lbl_prompt.setFont("orbitron_24");
  lbl_prompt.setText("Press Enter/   to continue");
  lbl_prompt.setParent(id);

  auto& lbl_enter_name = scene.add<afk::Label>(scene, 120, 348, z + 1);
  lbl_enter_name.setFont("orbitron_18");
  lbl_enter_name.setText("Enter your name:");
  lbl_enter_name.setParent(id);

  // Stats
  auto& lbl_stat_1 = scene.add<afk::Label>(scene, 130, 125, z + 1);
  lbl_stat_1.setFont("orbitron_18");
  lbl_stat_1.setParent(id);
  lbl_stat_1_id = lbl_stat_1.id;

  auto& lbl_stat_2 = scene.add<afk::Label>(scene, 130, 165, z + 1);
  lbl_stat_2.setFont("orbitron_18");
  lbl_stat_2.setParent(id);
  lbl_stat_2_id = lbl_stat_2.id;

  auto& lbl_stat_3 = scene.add<afk::Label>(scene, 130, 205, z + 1);
  lbl_stat_3.setFont("orbitron_18");
  lbl_stat_3.setParent(id);
  lbl_stat_3_id = lbl_stat_3.id;

  auto& lbl_stat_4 = scene.add<afk::Label>(scene, 130, 245, z + 1);
  lbl_stat_4.setFont("orbitron_18");
  lbl_stat_4.setParent(id);
  lbl_stat_4_id = lbl_stat_4.id;

  auto& lbl_stat_5 = scene.add<afk::Label>(scene, 130, 285, z + 1);
  lbl_stat_5.setFont("orbitron_18");
  lbl_stat_5.setParent(id);
  lbl_stat_5_id = lbl_stat_5.id;
}

void DieMenu::update(Uint32 delta) {
  // Submit
  if (scene.input.keyDown(afk::Keys::RETURN) ||
      scene.input.joyPressed(afk::JoystickButtons::START) ||
      scene.input.joyPressed(afk::JoystickButtons::A)) {
    auto& inp_name = scene.get<afk::Inputbox>(inp_name_id);
    highscores.add(inp_name.getText(), score);
    scene.scene.setNextScene("menu");
  }

  // Stats
  auto& lbl_stat_1 = scene.get<afk::Label>(lbl_stat_1_id);
  lbl_stat_1.setText(afk::str::format("Final Score: %i", score));

  auto& lbl_stat_2 = scene.get<afk::Label>(lbl_stat_2_id);
  lbl_stat_2.setText(
      afk::str::format("Distance Flown: %i ft", stats[STAT_DISTANCE] / 10));

  auto& lbl_stat_3 = scene.get<afk::Label>(lbl_stat_3_id);
  lbl_stat_3.setText(
      afk::str::format("Energy Collected: %i", stats[STAT_ENERGY]));

  auto& lbl_stat_4 = scene.get<afk::Label>(lbl_stat_4_id);
  lbl_stat_4.setText(
      afk::str::format("Powerups Received: %i", stats[STAT_POWERUPS]));

  auto& lbl_stat_5 = scene.get<afk::Label>(lbl_stat_5_id);
  lbl_stat_5.setText(
      afk::str::format("Debris Collided: %i", stats[STAT_DEBRIS]));
}
