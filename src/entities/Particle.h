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

#include "../constants/globals.h"

class Particle {
 public:
  Particle(int x,
           int y,
           ALLEGRO_COLOR color,
           int velocity_x,
           int velocity_y,
           int size,
           int type);
  ~Particle();

  void update();
  void scroll(float x, float y);
  void draw();

 private:
  float x, y;

  int size;
  int type;

  int velocity_x, velocity_y;

  ALLEGRO_COLOR color;
};

#endif
