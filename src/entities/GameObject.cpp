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

  // Draw bounding box
  if (settings.debug) {
    asw::draw::rect(transform, asw::color::gray);
  }
}
