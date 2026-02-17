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

#include <asw/asw.h>

#include "../constants/globals.h"

class Particle {
 public:
  Particle(int        x,
           int        y,
           asw::Color color,
           int        velocity_x,
           int        velocity_y,
           int        size,
           int        type);

  void update(float deltaTime);
  void scroll(float x, float y);
  void draw();

 private:
  float x;
  float y;

  int size;
  int type;

  int velocity_x;
  int velocity_y;

  asw::Color color;
};

#endif
