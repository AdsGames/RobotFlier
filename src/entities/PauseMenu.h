/*
 * Puase Menu
 * Allan Legemaate
 * In game pause menu
 * 12/08/2020
 */

#ifndef ENTITIES_PAUSE_MENU_H
#define ENTITIES_PAUSE_MENU_H

#include "../engine/Fonts/Font.h"
#include "../engine/Textures/Texture.h"

class PauseMenu {
 public:
  // Constructor
  PauseMenu();

  // Update pause menu
  void update();

  // Draws pause menu
  void draw();

  // Get paused state
  bool getPaused();

 private:
  // Load assets
  void loadAssets();

  // Paused state
  bool paused;

  // Images
  Texture background;

  // Fonts
  Font orbitron_18;
};

#endif  // ENTITIES_PAUSE_MENU_H
