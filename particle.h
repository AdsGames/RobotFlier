#ifndef PARTICLE_H
#define PARTICLE_H

#define CIRCLE 0
#define SQUARE 1
#define PIXEL 2
#define RANDOM 3

#include "globals.h"

class particle{
  public:
    BITMAP* image[2];

    int x;
    int y;

    int particleColor;
    int particleRed;
    int particleGreen;
    int particleBlue;

    int size;

    int xMax;
    int xMin;
    int yMin;
    int yMax;

    particle(int newX, int newY, int newColor, int newXMin, int newXMax, int newYMin, int newYMax, int newSize);
    ~particle();

    void logic();
    void draw(BITMAP* tempBitmap);

  private:
};

#endif

