#include "SettingsMenu.h"

#include <afk/entities/Sprite.h>
#include <afk/entities/ui/Button.h>
#include <afk/entities/ui/Checkbox.h>

#include <functional>

#include "../../constants/globals.h"

SettingsMenu::SettingsMenu(afk::Scene& scene) : GameObject(scene, 0, 0, 10) {
  // Background
  auto& spr_background = scene.add<afk::Sprite>(scene, 0, 0, z);
  spr_background.setTexture("options");
  spr_background.setParent(id);

  // Music
  auto& chk_music = scene.add<afk::Checkbox>(scene, 280, 180, z + 1);
  chk_music.setChecked(scene.config.get("music", true));
  chk_music.setOnCheck([&](const bool checked) {
    scene.config.set("music", checked);
    if (checked) {
      scene.audio.playStream("mainmenu");
    } else {
      scene.audio.stopStream("mainmenu");
    }
  });
  chk_music.setFont("orbitron_24");
  chk_music.setText("Music");
  chk_music.setParent(id);

  // Sound
  auto& chk_sound = scene.add<afk::Checkbox>(scene, 120, 180, z + 1);
  chk_sound.setChecked(scene.config.get("sound", true));
  chk_sound.setOnCheck(
      [&](const bool checked) { scene.config.set("sound", checked); });
  chk_sound.setFont("orbitron_24");
  chk_sound.setText("Sound");
  chk_sound.setParent(id);

  // Back button
  auto& btn_back = scene.add<afk::Button>(scene, 540, 407, z + 1);
  btn_back.setOnClick(std::bind(&SettingsMenu::setHooked, this, false));
  btn_back.setFont("orbitron_24");
  btn_back.setText("Back");
  btn_back.sizeToText();
  btn_back.setParent(id);

  // Exit button
  auto& btn_exit = scene.add<afk::Button>(scene, 540, 180, z + 1);
  btn_exit.setOnClick([&]() { scene.scene.setNextScene("exit"); });
  btn_exit.setFont("orbitron_24");
  btn_exit.setText("Exit");
  btn_exit.sizeToText();
  btn_exit.setParent(id);
}
