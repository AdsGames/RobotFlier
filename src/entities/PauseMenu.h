/*
 * Puase Menu
 * Allan Legemaate
 * In game pause menu
 * 12/08/2020
 */

#ifndef ENTITIES_PAUSE_MENU_H
#define ENTITIES_PAUSE_MENU_H

#include <afk/assets/Font.h>
#include <afk/assets/Texture.h>
#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

class PauseMenu : public afk::GameObject {
 public:
  // Constructor
  explicit PauseMenu(afk::Scene& scene);

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
  afk::Texture background;

  // Fonts
  afk::Font orbitron_18;
};

#endif  // ENTITIES_PAUSE_MENU_H
