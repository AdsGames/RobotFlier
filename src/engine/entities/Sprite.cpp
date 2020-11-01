#include "Sprite.h"

#include "../../constants/globals.h"
#include "../Core.h"
#include "../scene/Scene.h"

// Constructor
Sprite::Sprite(Scene& scene, const float x, const float y, const int z)
    : GameObject(scene, x, y, z) {}

// Constructor
Sprite::Sprite(Scene& scene,
               const std::string texture,
               const float x,
               const float y,
               const int z)
    : GameObject(scene, x, y, z) {
  setTexture(texture);
}

// Destructor
Sprite::~Sprite() {}

void Sprite::setTexture(const std::string& texture) {
  this->texture = Engine::asset_manager.getImage(texture);
  this->width = this->texture.getWidth();
  this->height = this->texture.getHeight();
}

// Draw
void Sprite::draw() {
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
