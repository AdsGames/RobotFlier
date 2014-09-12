#ifndef BOMB_H
#define BOMB_H

#define MAX_PARTICLES 50

#include "globals.h"
#include "particle.h"

class bomb{
  public:
    bomb(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY);
    ~bomb();
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

