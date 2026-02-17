/*
 * Robot Flier
 * A.D.S. Games
 * 03/01/2016
 * Robots in space!
 */
#include <asw/asw.h>

#include "./constants/globals.h"
#include "./constants/settings.h"
#include "./states/game.h"
#include "./states/init.h"
#include "./states/intro.h"
#include "./states/menu.h"

// main function of program
int main(int argc, char* argv[])
{
    // Copy over the command line args
    settings.parseArgs(argc, argv);

    asw::core::init(SCREEN_W, SCREEN_H, 1);
    asw::core::print_info();

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
