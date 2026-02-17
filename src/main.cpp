/*
 * Robot Flier
 * A.D.S. Games
 * 03/01/2016
 * Robots in space!
 */
#include <asw/asw.h>
#include <time.h>

#include <string>

#include "constants/globals.h"
#include "states/Game.h"
#include "states/Init.h"
#include "states/Intro.h"
#include "states/Menu.h"

// main function of program
int main(int argc, char* argv[]) {
  // Copy over the command line args
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "mega") == 0)
      settings[SETTING_MEGA] = true;
    else if (strcmp(argv[i], "supershake") == 0)
      settings[SETTING_SUPERSHAKE] = true;
    else if (strcmp(argv[i], "merrychristmas") == 0)
      settings[SETTING_CHRISTMAS] = true;
    else if (strcmp(argv[i], "debug") == 0)
      settings[SETTING_DEBUG] = true;

    std::cout << argv[i];
  }

  asw::core::init(SCREEN_W, SCREEN_H, 1);

  // Starts Game
  auto app = asw::scene::SceneManager<Scenes>();
  app.registerScene<InitScene>(Scenes::Init, app);
  app.registerScene<IntroScene>(Scenes::Intro, app);
  app.registerScene<MenuScene>(Scenes::Menu, app);
  app.registerScene<GameScene>(Scenes::Game, app);
  app.setNextScene(Scenes::Init);
  app.start();

  return 0;
}
