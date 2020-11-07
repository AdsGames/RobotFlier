/*
 * Robot Flier
 * @breif Entry point of robot flier game, Robots in space!
 *
 * @author A.D.S. Games
 * @date 03/01/2016
 */
#include "engine/Engine.h"

// main function of program
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
