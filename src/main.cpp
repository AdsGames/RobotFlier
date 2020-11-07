/**
 * Robot Flier
 * @brief Entry point of robot flier game, Robots in space!
 *
 * @author A.D.S. Games
 * @date 03/01/2016
 */
#include "engine/Engine.h"

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

  // Start it up!
  game.start(SCENE_INIT);

  // Exit!
  return 0;
}
