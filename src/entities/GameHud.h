/*
 * Game Hud
 * A.D.S. Games
 * 30/10/2020
 * Game hud
 */
#ifndef ENTITIES_GAMEHUD_H
#define ENTITIES_GAMEHUD_H

#include <afk/assets/Font.h>
#include <afk/assets/Texture.h>
#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

// Game class
class GameHud : public afk::GameObject {
 public:
  GameHud(afk::Scene& scene, const ObjId robotId);

  virtual ~GameHud(){};

  virtual void draw() override;

 private:
  // GUI Images
  afk::Texture debug;

  // Powerup Images
  afk::Texture powerStar;
  afk::Texture powerMagnet;

  // Fonts
  afk::Font orbitron_12;
  afk::Font orbitron_18;
  afk::Font orbitron_24;
  afk::Font orbitron_30;

  // Robot id
  ObjId robot_id;
};

#endif  // ENTITIES_GAMEHUD_H
