/*
 * Particle
 * Just little blips that make things look cool
 * A.D.S. Games
 */
#ifndef PARTICLE_H
#define PARTICLE_H

#define CIRCLE 0
#define SQUARE 1
#define PIXEL 2

#include <allegro.h>

class particle{
  public:
    float x;
    float y;

    int color;

    int size;
    int type;

    int velocity_x;
    int velocity_y;

    particle(int newX, int newY, int newColor, int newXVel, int newYVel, int newSize, int newType);
    ~particle();

    void logic();
    void draw( BITMAP* tempBitmap);

  private:
};

#endif

