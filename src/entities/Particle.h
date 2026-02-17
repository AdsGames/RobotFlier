/*
 * Particle
 * Just little blips that make things look cool
 * A.D.S. Games
 */
#ifndef PARTICLE_H
#define PARTICLE_H

#include <asw/asw.h>

#include "../constants/globals.h"

class Particle {
 public:
  Particle(const asw::Vec2<float>& position,
           asw::Color              color,
           const asw::Vec2<float>& velocity,
           float                   size,
           ParticleType            type);

  void update(float deltaTime);
  void scroll(float x, float y);
  void draw() const;

 private:
  asw::Quad<float> transform;
  asw::Vec2<float> velocity;

  ParticleType type;
  asw::Color   color;
};

#endif
