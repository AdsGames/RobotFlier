#include "GameObject.h"

#include "../constants/globals.h"
#include "../engine/Core.h"

// Constructor
GameObject::GameObject(const float x, const float y)
    : x(x), y(y), height(0), width(0), isDead(false), damage(0) {}

// Destructor
GameObject::~GameObject() {}

// Updates object logic
void GameObject::logic(const float motion) {
  // Update particles
  if (Engine::settings.get<int>("particleType", 0) != 3) {
    for (unsigned int i = 0; i < parts.size(); i++) {
      parts.at(i).update();
      parts.at(i).scroll(motion, 0.0f);
    }
  }
}

void GameObject::setTexture(const Texture& texture) {
  this->texture = texture;
  this->width = texture.getWidth();
  this->height = texture.getHeight();
}

// Has it been hit?
bool GameObject::dead() const {
  return isDead;
}

// Is the object off screen?
bool GameObject::offScreen() const {
  return x + width <= 0;
}

// Draw
void GameObject::draw() {
  // Draw image unless dead
  if (!isDead) {
    texture.drawScaled(x, y, width, height);
  }

  // Draw particles
  if (Engine::settings.get<int>("particleType", 0) != 3) {
    for (unsigned int i = 0; i < parts.size(); i++) {
      parts.at(i).draw();
    }
  }

  // Draw bounding box
  if (Engine::settings.get<bool>("debug", false)) {
    al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(88, 88, 88), 1);
  }
}
