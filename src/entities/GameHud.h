/*
 * Game Hud
 * A.D.S. Games
 * 30/10/2020
 * Game hud
 */
#ifndef ENTITIES_GAMEHUD_H
#define ENTITIES_GAMEHUD_H

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include <afk/entities/GameObject.h>
#include <afk/fonts/Font.h>
#include <afk/scene/Scene.h>
#include <afk/textures/Texture.h>

// Game class
class GameHud : public GameObject {
 public:
  GameHud(Scene& scene, const ObjId robotId);

  virtual ~GameHud(){};

  virtual void draw() override;

 private:
  // GUI Images
  Texture debug;

  // Powerup Images
  Texture powerStar;
  Texture powerMagnet;

  // Fonts
  Font orbitron_12;
  Font orbitron_18;
  Font orbitron_24;
  Font orbitron_30;

  // Robot id
  ObjId robot_id;
};

#endif  // ENTITIES_GAMEHUD_H
