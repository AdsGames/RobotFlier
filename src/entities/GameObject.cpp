#include "GameObject.h"

// Constructor
GameObject::GameObject(asw::Texture sprite, const int x, const int y) {
  this->sprite = sprite;
  this->x      = x;
  this->y      = y;
  isDead       = false;

  height = sprite->h;
  width  = sprite->w;

  damage = 0;
}

// Updates object logic
void GameObject::logic(int newMotion, float deltaTime) {
  // Update particles
  if (settings[SETTING_PARTICLE_TYPE] != 3) {
    for (unsigned int i = 0; i < parts.size(); i++) {
      parts.at(i).update(deltaTime);
      parts.at(i).scroll(newMotion, 0.0f);
    }
  }
}

// Has it been hit?
bool GameObject::dead() const {
  return isDead;
}

// Is the object off screen?
bool GameObject::offScreen() const {
  return (x <= 0 - width);
}

// Draw
void GameObject::draw() {
  // Draw image unless dead
  if (!isDead) {
    asw::draw::stretchSprite(sprite, asw::Quad<float>(x, y, width, height));
  }

  // Draw particles
  if (settings[SETTING_PARTICLE_TYPE] != 3) {
    for (auto& part : parts) {
      part.draw();
    }
  }

  // Draw bounding box
  if (settings[SETTING_DEBUG] == 1) {
    asw::draw::rect(asw::Quad<float>(x, y, width, height),
                    asw::Color(88, 88, 88));
  }
}
