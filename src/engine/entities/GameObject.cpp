#include "GameObject.h"

#include "../../constants/globals.h"
#include "../Core.h"

// Constructor
GameObject::GameObject(const Scene& scene,
                       const float x,
                       const float y,
                       const int z)
    : scene(scene),
      x(x),
      y(y),
      z(z),
      height(0),
      width(0),
      isDead(false),
      damage(0) {}

// Destructor
GameObject::~GameObject() {}

// Updates object logic
void GameObject::update() {}

void GameObject::setTexture(const std::string& texture) {
  this->texture = Engine::asset_manager.getImage(texture);
  this->width = this->texture.getWidth();
  this->height = this->texture.getHeight();
}

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

// Draw
void GameObject::draw() {
  // Draw image
  texture.drawScaled(x, y, width, height);

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

// Get z index
int GameObject::getZ() {
  return z;
}