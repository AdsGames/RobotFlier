#include "Particle.h"

// Constructor
Particle::Particle(const asw::Vec2<float>& position,
                   asw::Color              color,
                   const asw::Vec2<float>& velocity,
                   float                   size,
                   ParticleType            type)
    : transform(position.x, position.y, size, size),
      velocity(velocity),
      type(type),
      color(color) {}

// Logic
void Particle::update(float deltaTime) {
  transform.position += velocity * (deltaTime * 62.5F);
}

// Scrolly by
void Particle::scroll(float x, float y) {
  transform.position += asw::Vec2<float>(x, y);
}

// Draw
void Particle::draw() const {
  if (type == ParticleType::Pixel) {
    asw::draw::point(transform.position, color);
  } else if (type == ParticleType::Square) {
    asw::draw::rectFill(transform, color);
  } else if (type == ParticleType::Circle) {
    asw::draw::circleFill(transform.position + transform.size / 2.0F,
                          transform.size.x / 2.0F, color);
  }
}
