#include "./Particle.h"

// Helper for int conversion
ParticleType int_to_particle_type(int type) {
  switch (type) {
    case 0:
      return ParticleType::PIXEL;
    case 1:
      return ParticleType::SQUARE;
    case 2:
      return ParticleType::CIRCLE;
    case 3:
    default:
      return ParticleType::NONE;
  }
}

// Constructor
Particle::Particle(float x,
                   float y,
                   ALLEGRO_COLOR color,
                   float velocity_x,
                   float velocity_y,
                   int size,
                   ParticleType type)
    : x(x),
      y(y),
      size(size),
      type(type),
      velocity_x(velocity_x),
      velocity_y(velocity_y),
      color(color) {}

Particle::Particle(float x,
                   float y,
                   ALLEGRO_COLOR color,
                   float velocity_x,
                   float velocity_y,
                   int size,
                   int type)
    : x(x),
      y(y),
      size(size),
      type(int_to_particle_type(type)),
      velocity_x(velocity_x),
      velocity_y(velocity_y),
      color(color) {}

// Destructor
Particle::~Particle() {}

// Logic
void Particle::update() {
  x += velocity_x;
  y += velocity_y;
}

// Scroll by
void Particle::scroll(float x, float y) {
  this->x += x;
  this->y += y;
}

// Draw
void Particle::draw() {
  switch (type) {
    case ParticleType::SQUARE:
      al_draw_rectangle(x, y, x + size, y + size, color, 1);
      break;
    case ParticleType::CIRCLE:
      al_draw_circle(x, y, size, color, 1);
      break;
    case ParticleType::PIXEL:
      al_draw_rectangle(x, y, x, y, color, 1);
      break;
    default:
      break;
  }
}