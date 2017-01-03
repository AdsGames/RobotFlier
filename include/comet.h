/*
 * Comet
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef COMET_H
#define COMET_H

#include "game_object.h"

class comet : public game_object{
  public:
    // Constructor
    comet(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY);

    // Logic override
    void logic( int newMotion);
};

#endif

