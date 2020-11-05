/*
 * Sprite
 * A simple texturable game object
 * Allan Legemaate
 * 30/10/2020
 */

#ifndef ENGINE_ENTITIES_SPRITE_H
#define ENGINE_ENTITIES_SPRITE_H

#include <vector>

#include "../particles/Particle.h"
#include "../textures/Texture.h"
#include "GameObject.h"

class Sprite : public GameObject {
 public:
  // Constructor
  explicit Sprite(Scene& scene,
                  const float x = 0.0f,
                  const float y = 0.0f,
                  const int z = 0);

  // Constructor
  Sprite(Scene& scene,
         const std::string& texture,
         const float x = 0.0f,
         const float y = 0.0f,
         const int z = 0);

  // Destructor
  virtual ~Sprite();

  // Draws the object to screen
  virtual void draw() override;

  // Set visiblity
  void setVisible(const bool visible);

  // Set game object texture
  void setTexture(const std::string& texture);

 protected:
  // Images
  Texture texture;

  // Visibility
  bool visible;

  // Particles
  std::vector<Particle> parts;
};

#endif  // ENGINE_ENTITIES_SPRITE_H
