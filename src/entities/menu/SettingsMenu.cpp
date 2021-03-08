#include "SettingsMenu.h"

#include <afk/services/Services.h>

#include "../../constants/globals.h"
#include "../../helpers/tools.h"

SettingsMenu::SettingsMenu(afk::Scene& scene)
    : GameObject(scene, 0, 0, 10), open(false) {
  options = scene.assets.getImage("options");

  ui_sound[1] = scene.assets.getImage("ui_sound_on");
  ui_sound[0] = scene.assets.getImage("ui_sound_off");

  ui_music[1] = scene.assets.getImage("ui_music_on");
  ui_music[0] = scene.assets.getImage("ui_music_off");

  ui_window[1] = scene.assets.getImage("ui_window_windowed");
  ui_window[0] = scene.assets.getImage("ui_window_fullscreen");

  ui_particle[0] = scene.assets.getImage("ui_particle_pixel");
  ui_particle[1] = scene.assets.getImage("ui_particle_square");
  ui_particle[2] = scene.assets.getImage("ui_particle_circle");
  ui_particle[3] = scene.assets.getImage("ui_particle_off");

  ui_control[0] = scene.assets.getImage("ui_control_xbox");
  ui_control[1] = scene.assets.getImage("ui_control_keyboard");
  ui_control[2] = scene.assets.getImage("ui_control_auto");

  ui_screenshake[0] = scene.assets.getImage("ui_screenshake_none");
  ui_screenshake[1] = scene.assets.getImage("ui_screenshake_low");
  ui_screenshake[2] = scene.assets.getImage("ui_screenshake_medium");
  ui_screenshake[3] = scene.assets.getImage("ui_screenshake_high");

  ui_back = scene.assets.getImage("ui_back");
  ui_exit = scene.assets.getImage("ui_exit");

  orbitron_24 = scene.assets.getFont("orbitron_24");
}

void SettingsMenu::update() {
  if (open && scene.input.mousePressed(afk::MouseButtons::LEFT)) {
    // Particles toggle
    if (collision(280, 360, scene.input.mouseX(), scene.input.mouseX(), 400,
                  480, scene.input.mouseY(), scene.input.mouseY())) {
      scene.config.set("particleType",
                       (scene.config.get<int>("particleType", 0) + 1) % 4);
    }
    // Sound button toggle
    else if (collision(120, 200, scene.input.mouseX(), scene.input.mouseX(),
                       180, 260, scene.input.mouseY(), scene.input.mouseY())) {
      scene.config.set("sound", !scene.config.get<bool>("sound", true));
    }
    // Music button toggle
    else if (collision(280, 360, scene.input.mouseX(), scene.input.mouseX(),
                       180, 260, scene.input.mouseY(), scene.input.mouseY())) {
      scene.config.set("music", !scene.config.get<bool>("music", true));

      if (scene.config.get<bool>("music", false)) {
        scene.audio.playStream("mainmenu");
      } else {
        scene.audio.stopStream("mainmenu");
      }
    }
    // Fullscreen toggle
    else if (collision(120, 200, scene.input.mouseX(), scene.input.mouseX(),
                       400, 480, scene.input.mouseY(), scene.input.mouseY())) {
      const bool isFullscreen = scene.config.get<bool>("fullscreen", false);

      if (isFullscreen) {
        scene.display.setMode(afk::DisplayMode::WINDOWED);
        scene.config.set("fullscreen", false);
      } else {
        scene.display.setMode(afk::DisplayMode::FULLSCREEN_WINDOW_LETTERBOX);
        scene.config.set("fullscreen", true);
      }
      scene.display.hideMouse();
    }
    // Screen shake
    else if (collision(280, 360, scene.input.mouseX(), scene.input.mouseX(),
                       290, 370, scene.input.mouseY(), scene.input.mouseY())) {
      scene.config.set("screenshake",
                       (scene.config.get<int>("screenshake", 0) + 1) % 4);
    }
    // Control Toggle
    else if (collision(120, 200, scene.input.mouseX(), scene.input.mouseX(),
                       290, 370, scene.input.mouseY(), scene.input.mouseY())) {
      scene.config.set("controlMode",
                       (scene.config.get<int>("controlMode", 0) + 1) % 3);
    }
    // Power off
    else if (collision(540, 620, scene.input.mouseX(), scene.input.mouseX(),
                       180, 260, scene.input.mouseY(), scene.input.mouseY())) {
      scene.scene.setNextScene("exit");
    }
    // Exit menu
    else if (collision(540, 620, scene.input.mouseX(), scene.input.mouseX(),
                       407, 487, scene.input.mouseY(), scene.input.mouseY())) {
      setOpen(false);
    }
  }
}

void SettingsMenu::draw() {
  if (!open) {
    return;
  }

  // Background
  options.draw(0, 0);

  // Buttons
  ui_particle[scene.config.get<int>("particleType", 0)].draw(280, 407);
  ui_sound[scene.config.get<bool>("sound", true)].draw(120, 180);
  ui_music[scene.config.get<bool>("music", true)].draw(280, 180);
  ui_window[scene.config.get<bool>("fullscreen", false)].draw(120, 407);
  ui_screenshake[scene.config.get<int>("screenshake", 0)].draw(280, 295);
  ui_control[scene.config.get<int>("controlMode", 0)].draw(120, 295);

  // Button Text
  orbitron_24.draw(110, 154,
                   "Sounds         Music                            Exit");
  orbitron_24.draw(126, 268, "Input      Screen Shake");
  orbitron_24.draw(108, 382,
                   "Window       Particles                        Back");

  // Exit and back
  ui_exit.draw(540, 180);
  ui_back.draw(540, 407);
}

// Set open
void SettingsMenu::setOpen(const bool open) {
  this->open = open;
}
