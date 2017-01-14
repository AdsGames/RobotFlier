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
    powerup( BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newTimerLength, int newType);

    // Logic override
    void logic( int newMotion, robot *ourRobot);

    // Vars
    int timerLength;
    int type;
};

#endif

