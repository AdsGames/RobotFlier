/*
 * SettingsMenu
 * Allan Legemaate
 * Renders game settings menu
 * 31/10/2020
 */
#ifndef ENTITIES_MENU_SETTINGS_MENU_H
#define ENTITIES_MENU_SETTINGS_MENU_H

#include "../../engine/entities/GameObject.h"
#include "../../engine/fonts/Font.h"
#include "../../engine/scene/Scene.h"
#include "../../engine/textures/Texture.h"

class SettingsMenu : public GameObject {
 public:
  // Constructor
  SettingsMenu(Scene& scene);

  // Logic override
  virtual void update() override;

  // Draw
  virtual void draw() override;

  // Set open state
  void setOpen(const bool open);

 private:
  bool open;

  // Options menu
  Texture options;

  Texture ui_sound[2];
  Texture ui_music[2];
  Texture ui_screenshake[4];
  Texture ui_window[2];
  Texture ui_particle[4];
  Texture ui_control[3];

  Texture ui_back;
  Texture ui_exit;

  // Fonts
  Font orbitron_24;
};

#endif  // ENTITIES_MENU_SETTINGS_MENU_H
