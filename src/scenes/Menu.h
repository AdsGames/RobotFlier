/*
 * Menu
 * A.D.S. Games
 * 03/01/2016
 * The menu of Robot Flier
 */
#ifndef SRC_SCENES_MENU_H_
#define SRC_SCENES_MENU_H_

#include <afk/scene/Scene.h>

// Open menu enum
enum class MenuState { CREDITS, CONTROLS, SETTINGS, HIGHSCORES, HELP, NONE };

class Menu : public afk::Scene {
 public:
  // Override parent
  void start() override;
  void update(Uint32 delta) override;
  void stop() override;

 private:
  // Close menu
  void closeMenu(MenuState menu);

  // On click events
  void handleClickStart();
  void handleClickSettings();
  void handleClickHelp();
  void handleClickCredits();
  void handleClickScores();
  void handleClickControls();

  // Is a menu open?
  MenuState current_menu;

  // Objects
  afk::Entity settings_screen;
  afk::Entity scores_screen;
  afk::Entity help_sprite;
  afk::Entity credits_sprite;
  afk::Entity controls_sprite;
};

#endif  // SRC_SCENES_MENU_H_
