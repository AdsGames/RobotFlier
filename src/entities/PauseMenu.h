/*
 * Puase Menu
 * Allan Legemaate
 * In game pause menu
 * 12/08/2020
 */

#ifndef ENTITIES_PAUSE_MENU_H
#define ENTITIES_PAUSE_MENU_H

#include <afk/entities/GameObject.h>
#include <afk/fonts/Font.h>
#include <afk/scene/Scene.h>
#include <afk/textures/Texture.h>

class PauseMenu : public GameObject {
 public:
  // Constructor
  explicit PauseMenu(Scene& scene);

  // Update pause menu
  virtual void update() override;

  // Draws pause menu
  virtual void draw() override;

  // Get paused state
  bool getPaused() const;

 private:
  // Paused state
  bool paused;

  // Images
  Texture background;

  // Fonts
  Font orbitron_18;
};

#endif  // ENTITIES_PAUSE_MENU_H
