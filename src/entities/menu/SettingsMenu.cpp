#include "SettingsMenu.h"

#include <afk/services/Services.h>

#include "../../constants/globals.h"
#include "../../helpers/tools.h"

SettingsMenu::SettingsMenu(afk::Scene& scene)
    : GameObject(scene, 0, 0, 10), open(false) {
  afk::AssetService& assets = afk::Services::getAssetService();

  options = assets.getImage("options");

  ui_sound[1] = assets.getImage("ui_sound_on");
  ui_sound[0] = assets.getImage("ui_sound_off");

  ui_music[1] = assets.getImage("ui_music_on");
  ui_music[0] = assets.getImage("ui_music_off");

  ui_window[1] = assets.getImage("ui_window_windowed");
  ui_window[0] = assets.getImage("ui_window_fullscreen");

  ui_particle[0] = assets.getImage("ui_particle_pixel");
  ui_particle[1] = assets.getImage("ui_particle_square");
  ui_particle[2] = assets.getImage("ui_particle_circle");
  ui_particle[3] = assets.getImage("ui_particle_off");

  ui_control[0] = assets.getImage("ui_control_xbox");
  ui_control[1] = assets.getImage("ui_control_keyboard");
  ui_control[2] = assets.getImage("ui_control_auto");

  ui_screenshake[0] = assets.getImage("ui_screenshake_none");
  ui_screenshake[1] = assets.getImage("ui_screenshake_low");
  ui_screenshake[2] = assets.getImage("ui_screenshake_medium");
  ui_screenshake[3] = assets.getImage("ui_screenshake_high");

  ui_back = assets.getImage("ui_back");
  ui_exit = assets.getImage("ui_exit");

  orbitron_24 = assets.getFont("orbitron_24");
}

void SettingsMenu::update() {
  afk::InputService& input = afk::Services::getInputService();
  afk::ConfigService& config = afk::Services::getConfigService();
  afk::AudioService& audio = afk::Services::getAudioService();
  afk::DisplayService& display = afk::Services::getDisplayService();
  afk::SceneService& scene = afk::Services::getSceneService();

  if (open && input.mousePressed(afk::MouseButtons::BUTTON_LEFT)) {
    // Particles toggle
    if (collision(280, 360, input.mouseX(), input.mouseX(), 400, 480,
                  input.mouseY(), input.mouseY())) {
      config.set("particleType", (config.get<int>("particleType", 0) + 1) % 4);
    }
    // Sound button toggle
    else if (collision(120, 200, input.mouseX(), input.mouseX(), 180, 260,
                       input.mouseY(), input.mouseY())) {
      config.set("sound", !config.get<bool>("sound", true));
    }
    // Music button toggle
    else if (collision(280, 360, input.mouseX(), input.mouseX(), 180, 260,
                       input.mouseY(), input.mouseY())) {
      config.set("music", !config.get<bool>("music", true));

      if (config.get<bool>("music", false)) {
        audio.playStream("mainmenu");
      } else {
        audio.stopStream("mainmenu");
      }

    }
    // Fullscreen toggle
    else if (collision(120, 200, input.mouseX(), input.mouseX(), 400, 480,
                       input.mouseY(), input.mouseY())) {
      const bool isFullscreen = config.get<bool>("fullscreen", false);

      if (isFullscreen) {
        display.setMode(afk::DisplayMode::WINDOWED);
        config.set("fullscreen", false);
      } else {
        display.setMode(afk::DisplayMode::FULLSCREEN_WINDOW_LETTERBOX);
        config.set("fullscreen", true);
      }
      display.hideMouse();
    }
    // Screen shake
    else if (collision(280, 360, input.mouseX(), input.mouseX(), 290, 370,
                       input.mouseY(), input.mouseY())) {
      config.set("screenshake", (config.get<int>("screenshake", 0) + 1) % 4);
    }
    // Control Toggle
    else if (collision(120, 200, input.mouseX(), input.mouseX(), 290, 370,
                       input.mouseY(), input.mouseY())) {
      config.set("controlMode", (config.get<int>("controlMode", 0) + 1) % 3);
    }
    // Power off
    else if (collision(540, 620, input.mouseX(), input.mouseX(), 180, 260,
                       input.mouseY(), input.mouseY())) {
      scene.setNextScene("exit");
    }
    // Exit menu
    else if (collision(540, 620, input.mouseX(), input.mouseX(), 407, 487,
                       input.mouseY(), input.mouseY())) {
      setOpen(false);
    }
  }
}

void SettingsMenu::draw() {
  if (!open) {
    return;
  }

  afk::ConfigService& config = afk::Services::getConfigService();

  // Background
  options.draw(0, 0);

  // Buttons
  ui_particle[config.get<int>("particleType", 0)].draw(280, 407);
  ui_sound[config.get<bool>("sound", true)].draw(120, 180);
  ui_music[config.get<bool>("music", true)].draw(280, 180);
  ui_window[config.get<bool>("fullscreen", false)].draw(120, 407);
  ui_screenshake[config.get<int>("screenshake", 0)].draw(280, 295);
  ui_control[config.get<int>("controlMode", 0)].draw(120, 295);

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