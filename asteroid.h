#ifndef ASTEROID_Hw
#define ASTEROID_H

//#define MAX_PARTICLES 50

#include "globals.h"
#include "particle.h"

class asteroid{
  public:
    asteroid(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY, int newSize);
    ~asteroid();
    void logic(int newMotion);
    bool dead();
    void draw(BITMAP* tempBitmap);
    bool offScreen();

  private:
    BITMAP* image[2];
    SAMPLE* soundEffect;

    int x;
    int y;
    int height;
    int width;

    bool isDead;
    vector<particle> debris;
};

#endif

