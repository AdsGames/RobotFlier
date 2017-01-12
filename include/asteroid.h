/*
 * Asteroid
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef ASTEROID_H
#define ASTEROID_H

#include "game_object.h"

class asteroid : public game_object{
  public:
    // Constructor
    asteroid( BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newSize);

    // Logic override
    void logic( int newMotion);
};

#endif
