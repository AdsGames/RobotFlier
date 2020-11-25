/*
 * Menu
 * A.D.S. Games
 * 03/01/2016
 * The menu of Robot Flier
 */
#ifndef SCENES_MENU_H
#define SCENES_MENU_H

#include <afk/scene/Scene.h>

// Open menu enum
enum MENU { CREDITS, CONTROLS, SETTINGS, HIGHSCORES, HELP, NONE };

class Menu : public Scene {
 public:
  // Override parent
  virtual void start() override;
  virtual void update() override;
  virtual void draw() override{};
  virtual void stop() override;

 private:
  // Close menu
  void closeMenu(MENU menu);

  // On click events
  void handleClickStart();
  void handleClickSettings();
  void handleClickHelp();
  void handleClickCredits();
  void handleClickScores();
  void handleClickControls();

  // Is a menu open?
  MENU current_menu;

  // Objects
  ObjId settings_screen;
  ObjId scores_screen;
  ObjId help_sprite;
  ObjId credits_sprite;
  ObjId controls_sprite;
};

#endif  // SCENES_MENU_H
