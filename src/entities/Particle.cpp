#include "Particle.h"

// Constructor
Particle::Particle(int           x,
                   int           y,
                   ALLEGRO_COLOR color,
                   int           velocity_x,
                   int           velocity_y,
                   int           size,
                   int           type)
    : x(x),
      y(y),
      size(size),
      type(type),
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

// Scrolly by
void Particle::scroll(float x, float y) {
  this->x += x;
  this->y += y;
}

// Draw
void Particle::draw() {
  if (type == PIXEL) {
    al_put_pixel(x, y, color);
  } else if (type == SQUARE) {
    al_draw_rectangle(x, y, x + size, y + size, color, 1);
  } else if (type == CIRCLE) {
    al_draw_circle(x, y, size, color, 1);
  }
}
