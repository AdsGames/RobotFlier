/**
 * Robot Flier
 * @brief Entry point of robot flier game, Robots in space!
 *
 * @author A.D.S. Games
 * @date 03/01/2016
 */
#include "engine/Engine.h"

// Scenes
#include "scenes/Game.h"
#include "scenes/Init.h"
#include "scenes/Intro.h"
#include "scenes/Menu.h"

/**
 * @brief Entry point
 *
 * @param argc Unused args count
 * @param argv Unused args
 * @return Exit status
 */
int main(int argc, char** argv) {
  // Lets just ignore these
  (void)(argc);
  (void)(argv);

  // Create instance of game
  Engine game = Engine();

  // Add scenes
  game.addScene<Init>("init");
  game.addScene<Intro>("intro");
  game.addScene<Menu>("menu");
  game.addScene<Game>("game");

  // Start it up!
  game.start("init");

  // Exit!
  return 0;
}
