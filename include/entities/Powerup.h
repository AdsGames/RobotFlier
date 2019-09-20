/*
 * Powerup
 * Various powerups do various things
 * A.D.S. Games
 */
#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class Powerup : public GameObject {
  public:
    // Constructor
    Powerup(ALLEGRO_BITMAP *sprite, ALLEGRO_SAMPLE *sound, const int x, const int y, const int timerLength, const int type);

    // Logic override
    void logic(const int motion, Robot *robot);

    // Vars
    int timerLength;
    int type;
  private:
    ALLEGRO_SAMPLE *sound;
};

#endif

