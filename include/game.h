/*
 * Game state
 * A.D.S. Games
 * 03/01/2016
 * Main game state
 */
#ifndef GAME_H
#define GAME_H

#include "state.h"
#include "globals.h"
#include "tools.h"

#include "energy.h"
#include "debrie.h"
#include "powerup.h"
#include "particle.h"
#include "globals.h"
#include "mouseListener.h"
#include "keyListener.h"
#include "robot.h"

// Game class
class game : public state{
  public:
    // Construct/deconstruct
    game();
    ~game();

    // Override parent
    void update();
    void draw();

  protected:

  private:
    // Change theme
    void changeTheme( int NewThemeNumber);

    // Declare bitmaps
    /*BITMAP* buffer;
    BITMAP* screenshot;

    // Game images
    BITMAP* space;
    BITMAP* parallaxBack;
    BITMAP* groundOverlay;
    BITMAP* groundUnderlay;

    // GUI Images
    BITMAP* debug;
    BITMAP* pauseMenu;
    BITMAP *ui_game_end;
    BITMAP *ui_a;
    BITMAP *ui_b;

    // Danger images
    BITMAP* energyImage;
    BITMAP* asteroidImage;
    BITMAP* bombImage;
    BITMAP* cometImage;

    // Powerup Images
    BITMAP* powerStar;
    BITMAP* powerMagnet[4];

    // Declare sounds
    SAMPLE* sound_orb;
    SAMPLE* sound_bomb;
    SAMPLE* sound_asteroid;
    SAMPLE* sound_magnet;
    SAMPLE* sound_star;
    SAMPLE* sound_snap;

    // Music
    SAMPLE* music_ingame;
    SAMPLE* music_death;

    // Our robot
    robot hectar;

    // Declare integers
    int scroll;
    int themeNumber;
    int screenshake_x;
    int screenshake_y;
    float motion;

    // Declare booleans
    bool paused;

    // Text input
    std::string edittext;
    std::string::iterator iter;

    // Containers of objects
    std::vector<energy> energys;
    std::vector<debrie> debries;
    std::vector<powerup> powerups;*/
};

#endif // GAME_H
