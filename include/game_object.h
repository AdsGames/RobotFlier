/*
 * Game Object
 * A collision object! Parent class for many others
 * Allan Legemaate
 * 03/01/2017
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"
#include "particle.h"
#include "tools.h"
#include "robot.h"

class game_object{
  public:
    // Constructor
    game_object( ALLEGRO_BITMAP* newImage, ALLEGRO_SAMPLE* newSoundEffect, int newX, int newY);

    // Destructor
    ~game_object();

    // Updates asteroid logic
    void logic( int newMotion);

    // Has it been hit?
    bool dead();

    // Has it passed the screen bounds?
    bool offScreen();

    // Draws the object to screen
    void draw();
  protected:
    // Images
    ALLEGRO_BITMAP* image;

    // Sounds
    ALLEGRO_SAMPLE* soundEffect;

    // Position
    float x, y;

    // Size
    int height, width;

    // Dead or naw
    bool isDead;

    // Particles
    std::vector<particle> parts;

    // Damage
    int damage;
};

#endif // GAME_OBJECT_H
