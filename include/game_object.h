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

class game_object{
  public:
    // Constructor
    game_object(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY, int newSize);

    // Destructor
    ~game_object();

    // Updates asteroid logic
    void logic(int newMotion);

    // Has it been hit?
    bool dead();

    // Has it passed the screen bounds?
    bool offScreen();

    // Draws the asteroid to screen
    void draw(BITMAP* tempBitmap);
  protected:
    // Images
    BITMAP* image[2];

    // Sounds
    SAMPLE* soundEffect;

    // Position
    int x, y;

    // Size
    int height, width;

    // Dead or naw
    bool isDead;

    // Particles for explosion
    vector<particle> debris;

    // Damage
    int damage;
};

#endif // GAME_OBJECT_H
