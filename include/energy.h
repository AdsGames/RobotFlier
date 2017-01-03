/*
 * Energy
 * Gives the player health
 * A.D.S. Games
 */
#ifndef ENERGY_H
#define ENERGY_H

#include "game_object.h"

class energy : public game_object{
  public:
    // Constructor
    energy(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY);

    // Logic override
    void logic(int newMotion);
};

#endif

