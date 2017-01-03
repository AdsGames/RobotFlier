/*
 * Bomb
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef BOMB_H
#define BOMB_H

#include "game_object.h"

class bomb : public game_object{
  public:
    // Constructor
    bomb( BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY);

    // Logic
    void logic( int newMotion);
};

#endif

