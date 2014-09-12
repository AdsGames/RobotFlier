#ifndef ENERGY_H
#define ENERGY_H

#define MAX_PARTICLES 20

#include "globals.h"
#include "particle.h"

class energy{
  public:
    energy(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY);
    ~energy();
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

