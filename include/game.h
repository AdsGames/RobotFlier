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

#include "energy.h"
#include "asteroid.h"
#include "bomb.h"
#include "comet.h"
#include "powerup.h"
#include "particle.h"
#include "globals.h"
#include "mouseListener.h"
#include "keyListener.h"

// Structure of ground
struct ground_tiles{
  BITMAP* groundImage;
  int x;
  int y;
};

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
    // Pieces of ground
    ground_tiles groundPieces[14];

    // Declare bitmaps
    BITMAP* buffer;
    BITMAP* screenshot;

    // Game images
    BITMAP* space;
    BITMAP* space2;
    BITMAP* groundOverlay;

    // GUI Images
    BITMAP* debug;
    BITMAP* pauseMenu;
    BITMAP* christmas_hat;

    //Robot images
    BITMAP* robot;
    BITMAP* robotFire;
    BITMAP* robotInvincible;
    BITMAP* robotInvincibleFire;
    BITMAP* robotInvincibleTop;
    BITMAP* robotDie;

    // Danger images
    BITMAP* energyImage;
    BITMAP* asteroidImage;
    BITMAP* bombImage;
    BITMAP* cometImage;

    // Powerup Images
    BITMAP* powerStar;
    BITMAP* powerMagnet[4];

    BITMAP *ui_game_end;
    BITMAP *ui_a;
    BITMAP *ui_b;

    // Declare ground bitmaps
    BITMAP* ground[13];

    // Declare sounds
    SAMPLE* sound_orb;
    SAMPLE* sound_bomb;
    SAMPLE* sound_asteroid;
    SAMPLE* magnetSound;
    SAMPLE* sound_star;
    SAMPLE* sound_flame;
    SAMPLE* sound_hitground;

    // Music
    FSOUND_STREAM* music_ingame;
    FSOUND_STREAM* music_mainmenu;
    FSOUND_STREAM* music_death;

    // Declare integers
    float deltatime;
    int running;
    float gravity, motion, speed;
    int scroll;
    int groundScroll;
    int gameScreen;
    int handling_speed;
    int themeNumber;
    int screenshake_x;
    int screenshake_y;

    // Declare booleans
    bool rocket;
    bool paused;
    bool alive;
    bool onGround;
    bool deadSoundSwitch;
    bool joystick_enabled;
    bool key_binding_screen;
    bool magnetic;

    //Text input
    string edittext;
    string::iterator iter;

    // Declares that the void functions are there
    void changeTheme( int NewThemeNumber);

    // Containers of objects
    vector<energy> energys;
    vector<asteroid> asteroids;
    vector<bomb> bombs;
    vector<comet> comets;
    vector<powerup> powerups;

    // Particles
    vector<particle> rocketPart;
    vector<particle> smokePart;

};

#endif // GAME_H