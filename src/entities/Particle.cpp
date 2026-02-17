#include "Particle.h"

// Constructor
Particle::Particle(int        x,
                   int        y,
                   asw::Color color,
                   int        velocity_x,
                   int        velocity_y,
                   int        size,
                   int        type)
    : x(x),
      y(y),
      size(size),
      type(type),
      velocity_x(velocity_x),
      velocity_y(velocity_y),
      color(color) {}

// Logic
void Particle::update(float deltaTime) {
  x += velocity_x * (deltaTime / 16.0F);
  y += velocity_y * (deltaTime / 16.0F);
}

// Scrolly by
void Particle::scroll(float x, float y) {
  this->x += x;
  this->y += y;
}

// Draw
void Particle::draw() {
  if (type == PIXEL) {
    asw::draw::point(asw::Vec2<float>(x, y), color);
  } else if (type == SQUARE || type == CIRCLE) {
    asw::draw::rectFill(asw::Quad<float>(x, y, size, size), color);
  }
}
