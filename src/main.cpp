/**
 * Robot Flier
 * @brief Entry point of robot flier game, Robots in space!
 *
 * @author A.D.S. Games
 * @date 03/01/2016
 */
#include <afk/Game.h>
#include <afk/services/Services.h>

// Scenes
#include "scenes/Init.h"
#include "scenes/Intro.h"
#include "scenes/MainGame.h"
#include "scenes/Menu.h"

/**
 * @brief Main game class, boots first scene
 *
 */
class GameEntry : afk::Game {
 public:
  GameEntry() : Game() {
    // Get scene manager
    afk::SceneService& scene = afk::Services::getSceneService();

    // Add scenes
    scene.addScene<Init>("init");
    scene.addScene<Intro>("intro");
    scene.addScene<Menu>("menu");
    scene.addScene<MainGame>("game");
    scene.setNextScene("init");

    // Start it up!
    start();
  }
};

/**
 * @brief Entry point
 *
 * @param argc Unused args count
 * @param argv Unused args
 * @return Exit status
 */
int main(int argv, char** args) {
  // Lets just ignore these
  (void)(args);
  (void)(argv);

  // Create instance of game
  GameEntry game = GameEntry();

  // Exit!
  return 0;
}
