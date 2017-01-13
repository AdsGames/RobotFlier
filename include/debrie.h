/*
 * Debris
 * A collision object that can be crashed into
 * A.D.S. Games
 */
#ifndef DEBRIE_H
#define DEBRIE_H

#include "game_object.h"

class debrie : public game_object{
  public:
    // Constructor
    debrie( BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newDamage, float newMotionMultiplier = 1.0f, int newSize = -1);

    // Logic override
    void logic( int newMotion);
  private:
    // Motion multiplier
    float motion_multiplier;
};

#endif
