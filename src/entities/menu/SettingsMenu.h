/*
 * SettingsMenu
 * Allan Legemaate
 * Renders game settings menu
 * 31/10/2020
 */
#ifndef ENTITIES_MENU_SETTINGS_MENU_H
#define ENTITIES_MENU_SETTINGS_MENU_H

#include <afk/assets/Font.h>
#include <afk/assets/Texture.h>
#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

class SettingsMenu : public afk::GameObject {
 public:
  // Constructor
  explicit SettingsMenu(afk::Scene& scene);

  // Logic override
  virtual void update() override;

  // Draw
  virtual void draw() override;

  // Set open state
  void setOpen(const bool open);

 private:
  bool open;

  // Options menu
  afk::Texture options;

  afk::Texture ui_sound[2];
  afk::Texture ui_music[2];
  afk::Texture ui_screenshake[4];
  afk::Texture ui_window[2];
  afk::Texture ui_particle[4];
  afk::Texture ui_control[3];

  afk::Texture ui_back;
  afk::Texture ui_exit;

  // Fonts
  afk::Font orbitron_24;
};

#endif  // ENTITIES_MENU_SETTINGS_MENU_H
