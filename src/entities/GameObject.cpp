#include "GameObject.h"

// Constructor
GameObject::GameObject(asw::Texture sprite, const asw::Vec2<float>& position) {
  this->sprite         = sprite;
  transform.position.x = position.x;
  transform.position.y = position.y;
  isDead               = false;

  transform.size.x = static_cast<float>(sprite->w);
  transform.size.y = static_cast<float>(sprite->h);

  damage = 0;
}

// Updates object logic
void GameObject::logic(float motion, float deltaTime) {
  // Update particles
  if (settings.particlesEnabled()) {
    for (auto& part : parts) {
      part.update(deltaTime);
      part.scroll(motion, 0.0f);
    }
  }
}

// Has it been hit?
bool GameObject::dead() const {
  return isDead;
}

// Is the object off screen?
bool GameObject::offScreen() const {
  return transform.position.x <= 0 - transform.size.x;
}

// Draw
void GameObject::draw() const {
  // Draw image unless dead
  if (!isDead) {
    asw::draw::stretchSprite(sprite, transform);
  }

  // Draw particles
  if (settings.particlesEnabled()) {
    for (const auto& part : parts) {
      part.draw();
    }
  }

  // Draw bounding box
  if (settings.debug) {
    asw::draw::rect(transform, asw::color::gray);
  }
}
