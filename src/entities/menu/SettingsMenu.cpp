#include "SettingsMenu.h"

#include "../../constants/globals.h"
#include "../../engine/input/MouseListener.h"
#include "../../helpers/tools.h"

SettingsMenu::SettingsMenu(Scene& scene)
    : GameObject(scene, 0, 0, 10), open(false) {
  options = scene.getAsset().getImage("options");

  ui_sound[1] = scene.getAsset().getImage("ui_sound_on");
  ui_sound[0] = scene.getAsset().getImage("ui_sound_off");

  ui_music[1] = scene.getAsset().getImage("ui_music_on");
  ui_music[0] = scene.getAsset().getImage("ui_music_off");

  ui_window[1] = scene.getAsset().getImage("ui_window_windowed");
  ui_window[0] = scene.getAsset().getImage("ui_window_fullscreen");

  ui_particle[0] = scene.getAsset().getImage("ui_particle_pixel");
  ui_particle[1] = scene.getAsset().getImage("ui_particle_square");
  ui_particle[2] = scene.getAsset().getImage("ui_particle_circle");
  ui_particle[3] = scene.getAsset().getImage("ui_particle_off");

  ui_control[0] = scene.getAsset().getImage("ui_control_xbox");
  ui_control[1] = scene.getAsset().getImage("ui_control_keyboard");
  ui_control[2] = scene.getAsset().getImage("ui_control_auto");

  ui_screenshake[0] = scene.getAsset().getImage("ui_screenshake_none");
  ui_screenshake[1] = scene.getAsset().getImage("ui_screenshake_low");
  ui_screenshake[2] = scene.getAsset().getImage("ui_screenshake_medium");
  ui_screenshake[3] = scene.getAsset().getImage("ui_screenshake_high");

  ui_back = scene.getAsset().getImage("ui_back");
  ui_exit = scene.getAsset().getImage("ui_exit");
}

void SettingsMenu::update() {
  if (open && MouseListener::mouse_pressed & 1) {
    // Particles toggle
    if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x, 400,
                  480, MouseListener::mouse_y, MouseListener::mouse_y)) {
      scene.getSettings().set(
          "particleType",
          (scene.getSettings().get<int>("particleType", 0) + 1) % 4);
    }
    // Sound button toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      scene.getSettings().set("sound",
                              !scene.getSettings().get<bool>("sound", true));
    }
    // Music button toggle
    else if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      scene.getSettings().set("music",
                              !scene.getSettings().get<bool>("music", true));

      if (scene.getSettings().get<bool>("music", false)) {
        scene.getAudio().playStream("mainmenu");
      } else {
        scene.getAudio().stopStream("mainmenu");
      }

    }
    // Fullscreen toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       400, 480, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      const bool isFullscreen =
          scene.getSettings().get<bool>("fullscreen", false);

      if (isFullscreen) {
        scene.getWindow().setMode(DISPLAY_MODE::WINDOWED);
        scene.getSettings().set("fullscreen", false);
      } else {
        scene.getWindow().setMode(DISPLAY_MODE::FULLSCREEN_WINDOW_LETTERBOX);
        scene.getSettings().set("fullscreen", true);
      }
      scene.getWindow().hideMouse();
    }
    // Screen shake
    else if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x,
                       290, 370, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      scene.getSettings().set(
          "screenshake",
          (scene.getSettings().get<int>("screenshake", 0) + 1) % 4);
    }
    // Control Toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       290, 370, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      scene.getSettings().set(
          "controlMode",
          (scene.getSettings().get<int>("controlMode", 0) + 1) % 3);
    }
    // Power off
    else if (collision(540, 620, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      Scene::setNextScene(SCENE_EXIT);
    }
    // Exit menu
    else if (collision(540, 620, MouseListener::mouse_x, MouseListener::mouse_x,
                       407, 487, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
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
  ui_particle[scene.getSettings().get<int>("particleType", 0)].draw(280, 407);
  ui_sound[scene.getSettings().get<bool>("sound", true)].draw(120, 180);
  ui_music[scene.getSettings().get<bool>("music", true)].draw(280, 180);
  ui_window[scene.getSettings().get<bool>("fullscreen", false)].draw(120, 407);
  ui_screenshake[scene.getSettings().get<int>("screenshake", 0)].draw(280, 295,
                                                                      0);
  ui_control[scene.getSettings().get<int>("controlMode", 0)].draw(120, 295);

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