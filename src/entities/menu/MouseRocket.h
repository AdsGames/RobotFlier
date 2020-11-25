/*
 * Mouse Rocket
 * Allan Legemaate
 * Renders game settings menu
 * 01/11/2020
 */
#ifndef ENTITIES_MENU_MOUSE_ROCKET_H
#define ENTITIES_MENU_MOUSE_ROCKET_H

#include <afk/entities/Sprite.h>
#include <afk/scene/Scene.h>

class MouseRocket : public Sprite {
 public:
  // Constructor
  explicit MouseRocket(Scene& scene);

  // Logic override
  virtual void update() override;

 private:
  bool mouse_rocket_up;
  int mouse_y;
};

#endif  // ENTITIES_MENU_MOUSE_ROCKET_H
