/*
 * Powerup
 * Various powerups do various things
 * A.D.S. Games
 */
#ifndef POWERUP_H
#define POWERUP_H

#include "game_object.h"

class powerup : public game_object{
  public:
    // Constructor
    powerup(BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newTimerLength, int newType, int newStrength);

    // Logic override
    void logic(int newMotion);

    // Vars
    int timerLength;
    int type;
    int strength;
};

#endif

