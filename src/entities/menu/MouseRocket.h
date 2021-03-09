/*
 * Mouse Rocket
 * Allan Legemaate
 * Renders game settings menu
 * 01/11/2020
 */
#ifndef SRC_ENTITIES_MENU_MOUSEROCKET_H_
#define SRC_ENTITIES_MENU_MOUSEROCKET_H_

#include <afk/entities/Sprite.h>
#include <afk/scene/Scene.h>

class MouseRocket : public afk::Sprite {
 public:
  // Constructor
  explicit MouseRocket(afk::Scene& scene);

  // Logic override
  void update(Uint32 delta) override;

 private:
  bool mouse_rocket_up;
  int mouse_y;
  ObjId emitter_id;
};

#endif  // SRC_ENTITIES_MENU_MOUSEROCKET_H_
