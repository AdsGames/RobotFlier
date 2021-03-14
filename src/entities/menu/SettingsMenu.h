/*
 * SettingsMenu
 * Allan Legemaate
 * Renders game settings menu
 * 31/10/2020
 */
#ifndef SRC_ENTITIES_MENU_SETTINGSMENU_H_
#define SRC_ENTITIES_MENU_SETTINGSMENU_H_

#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

class SettingsMenu : public afk::GameObject {
 public:
  // Constructor
  explicit SettingsMenu(afk::Scene& scene);
};

#endif  // SRC_ENTITIES_MENU_SETTINGSMENU_H_
