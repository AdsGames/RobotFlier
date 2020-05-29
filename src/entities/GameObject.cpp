#include "GameObject.h"

// Constructor
GameObject::GameObject(ALLEGRO_BITMAP* sprite, const int x, const int y) {
  this->sprite = sprite;
  this->x      = x;
  this->y      = y;
  isDead       = false;

  height = al_get_bitmap_height(sprite);
  width  = al_get_bitmap_width(sprite);

  damage = 0;
}

// Destructor
GameObject::~GameObject() {}

// Updates object logic
void GameObject::logic(int newMotion) {
  // Update particles
  if (settings[SETTING_PARTICLE_TYPE] != 3) {
    for (unsigned int i = 0; i < parts.size(); i++) {
      parts.at(i).update();
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
    if (sprite != nullptr) {
      al_draw_scaled_bitmap(sprite, 0, 0, al_get_bitmap_width(sprite),
                            al_get_bitmap_height(sprite), x, y, width, height,
                            0);
    }
  }

  // Draw particles
  if (settings[SETTING_PARTICLE_TYPE] != 3) {
    for (unsigned int i = 0; i < parts.size(); i++) {
      parts.at(i).draw();
    }
  }

  // Draw bounding box
  if (settings[SETTING_DEBUG] == 1) {
    al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(88, 88, 88), 1);
  }
}
