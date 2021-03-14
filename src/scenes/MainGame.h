/*
 * Game scene
 * A.D.S. Games
 * 03/01/2016
 * Main game scene
 */
#ifndef SRC_SCENES_MAINGAME_H_
#define SRC_SCENES_MAINGAME_H_

#include <afk/scene/Scene.h>

#include <string>

// Game class
class MainGame : public afk::Scene {
 public:
  // Override parent
  void start() override;
  void update(Uint32 delta) override;
  void stop() override;

 private:
  void takeScreenshot();

  // Up arrow
  ObjId ui_up_id;

  // Our robot
  ObjId hectar_id;

  // Pause menu
  ObjId pause_menu_id;
  ObjId die_menu_id;
  ObjId spawner_id;

  // Declare integers
  int themeNumber;
  int screenshake_x;
  int screenshake_y;
  double arrow_animation;
  bool hectarIsAlive;
  bool paused;

};

#endif  // SRC_SCENES_MAINGAME_H_
