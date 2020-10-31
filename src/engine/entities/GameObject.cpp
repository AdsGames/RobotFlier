#include "GameObject.h"
#include <iostream>

#include "../../constants/globals.h"
#include "../Core.h"
#include "../scene/Scene.h"

// Constructor
GameObject::GameObject(const Scene& scene,
                       const float x,
                       const float y,
                       const int z)
    : scene(scene), x(x), y(y), z(z), height(0), width(0), isDead(false) {}

// Destructor
GameObject::~GameObject() {}

// Update
void GameObject::update() {}

// Draw
void GameObject::draw() {}

// Is colliding with game object
bool GameObject::colliding(const GameObject& other) {
  return x < other.x + other.width && y < other.y + other.width &&
         other.x < x + width && other.y < y + width;
}

// On collide can be overriden
void GameObject::onCollide(const GameObject& other) {
  (void)(other);
}

// Has it been hit?
bool GameObject::dead() const {
  return isDead;
}

// Is the object off screen?
bool GameObject::offScreen() const {
  return x + width <= 0;
}

// Get z index
int GameObject::getZ() const {
  return z;
}