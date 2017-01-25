/*
 * Game state
 * A.D.S. Games
 * 03/01/2016
 * Main game state
 */
#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

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
#include "joystickListener.h"
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
    ALLEGRO_BITMAP* screenshot;

    // Game images
    ALLEGRO_BITMAP* space;
    ALLEGRO_BITMAP* parallaxBack;
    ALLEGRO_BITMAP* groundOverlay;
    ALLEGRO_BITMAP* groundUnderlay;

    // GUI Images
    ALLEGRO_BITMAP* debug;
    ALLEGRO_BITMAP* pauseMenu;
    ALLEGRO_BITMAP *ui_game_end;
    ALLEGRO_BITMAP *ui_a;
    ALLEGRO_BITMAP *ui_b;
    ALLEGRO_BITMAP *ui_up;

    // Danger images
    ALLEGRO_BITMAP* energyImage;
    ALLEGRO_BITMAP* asteroidImage;
    ALLEGRO_BITMAP* bombImage;
    ALLEGRO_BITMAP* cometImage;

    // Powerup Images
    ALLEGRO_BITMAP* powerStar;
    ALLEGRO_BITMAP* powerMagnet[4];

    // Declare sounds
    ALLEGRO_SAMPLE* sound_orb;
    ALLEGRO_SAMPLE* sound_bomb;
    ALLEGRO_SAMPLE* sound_asteroid;
    ALLEGRO_SAMPLE* sound_magnet;
    ALLEGRO_SAMPLE* sound_star;
    ALLEGRO_SAMPLE* sound_snap;

    // Music
    ALLEGRO_SAMPLE* music_ingame;
    ALLEGRO_SAMPLE* music_death;

    // Our robot
    robot hectar;

    // Declare integers
    int scroll;
    int themeNumber;
    int screenshake_x;
    int screenshake_y;
    double arrow_animation;
    float motion;

    // Declare booleans
    bool paused;

    // Text input
    std::string edittext;
    std::string::iterator iter;

    // Containers of objects
    std::vector<energy> energys;
    std::vector<debrie> debries;
    std::vector<powerup> powerups;
};

#endif // GAME_H
