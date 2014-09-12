#ifndef POWERUP_H
#define POWERUP_H

#include "globals.h"

class powerup{
  public:
    explicit powerup(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY, int newTimerLength, int newType, int newStrength);
    ~powerup();
    void logic(int newMotion);   
    bool dead();
    void draw(BITMAP* tempBitmap);
    
    int timerLength;
    int type;
    int strength;
    
  private:
    BITMAP* image[2];
    SAMPLE* soundEffect;
    
    int x;
    int y;
    int height;
    int width;
};

#endif

