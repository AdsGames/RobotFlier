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

#include <allegro5/allegro_primitives.h>

#include "globals.h"

class particle{
  public:
    float x;
    float y;

    ALLEGRO_COLOR color;

    int size;
    int type;

    int velocity_x;
    int velocity_y;

    particle(int newX, int newY, ALLEGRO_COLOR newColor, int newXVel, int newYVel, int newSize, int newType);
    ~particle();

    void logic();
    void draw();

  private:
};

#endif

