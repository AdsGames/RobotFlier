#include "PauseMenu.h"

#include <afk/common/str.h>
#include <afk/entities/Sprite.h>
#include <afk/entities/ui/Button.h>
#include <afk/entities/ui/Label.h>

#include "../constants/globals.h"

PauseMenu::PauseMenu(afk::Scene& scene) : GameObject(scene) {
  // Background
  scene.addObj<afk::Sprite>(scene, "pauseMenu", 130, 140, z).setParent(id);

  // Stats
  auto& lbl_stat_1 = scene.addObj<afk::Label>(scene, 220, 250, z + 1);
  lbl_stat_1.setFont("orbitron_18");
  lbl_stat_1.setParent(id);
  lbl_stat_1_id = lbl_stat_1.id;

  auto& lbl_stat_2 = scene.addObj<afk::Label>(scene, 220, 280, z + 1);
  lbl_stat_2.setFont("orbitron_18");
  lbl_stat_2.setParent(id);
  lbl_stat_2_id = lbl_stat_2.id;

  auto& lbl_stat_3 = scene.addObj<afk::Label>(scene, 220, 310, z + 1);
  lbl_stat_3.setFont("orbitron_18");
  lbl_stat_3.setParent(id);
  lbl_stat_3_id = lbl_stat_3.id;

  auto& lbl_stat_4 = scene.addObj<afk::Label>(scene, 220, 340, z + 1);
  lbl_stat_4.setFont("orbitron_18");
  lbl_stat_4.setParent(id);
  lbl_stat_4_id = lbl_stat_4.id;

  // Buttons
  auto& button_quit = scene.addObj<afk::Button>(scene, 220, 445, z + 1);
  button_quit.setFont("orbitron_18");
  button_quit.setText("QUIT");
  button_quit.setParent(id);
  button_quit.sizeToText();
  button_quit.setOnClick([&]() { scene.scene.setNextScene("exit"); });

  auto& button_menu = scene.addObj<afk::Button>(scene, 300, 445, z + 1);
  button_menu.setFont("orbitron_18");
  button_menu.setText("MENU");
  button_menu.setParent(id);
  button_menu.sizeToText();
  button_menu.setOnClick([&]() { scene.scene.setNextScene("menu"); });
}

void PauseMenu::update(Uint32 delta) {
  auto& lbl_stat_1 = scene.get<afk::Label>(lbl_stat_1_id);
  lbl_stat_1.setText(
      afk::str::format("Distance Flown: %i ft", stats[STAT_DISTANCE] / 10));

  auto& lbl_stat_2 = scene.get<afk::Label>(lbl_stat_2_id);
  lbl_stat_2.setText(
      afk::str::format("Energy Collected: %i", stats[STAT_ENERGY]));

  auto& lbl_stat_3 = scene.get<afk::Label>(lbl_stat_3_id);
  lbl_stat_3.setText(
      afk::str::format("Powerups Received: %i", stats[STAT_POWERUPS]));

  auto& lbl_stat_4 = scene.get<afk::Label>(lbl_stat_4_id);
  lbl_stat_4.setText(
      afk::str::format("Debris Collided: %i", stats[STAT_DEBRIS]));
}
