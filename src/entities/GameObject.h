/*
 * Game Object
 * A collision object! Parent class for many others
 * Allan Legemaate
 * 03/01/2017
 */

#ifndef ENTITIES_GAME_OBJECT_H
#define ENTITIES_GAME_OBJECT_H

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include <vector>

#include "../engine/Particles/Particle.h"
#include "../engine/Textures/Texture.h"
#include "Robot.h"

class GameObject {
 public:
  // Constructor
  GameObject(const float x = 0.0f, const float y = 0.0f);

  // Destructor
  ~GameObject();

  // Updates asteroid logic
  void logic(const float motion);

  // Set game object texture
  void setTexture(const Texture& texture);

  // Has it been hit?
  bool dead() const;

  // Has it passed the screen bounds?
  bool offScreen() const;

  // Draws the object to screen
  void draw();

 protected:
  // Images
  Texture texture;

  // Position
  float x, y;

  // Size
  int height, width;

  // Dead or naw
  bool isDead;

  // Damage
  int damage;

  // Particles
  std::vector<Particle> parts;
};

#endif  // ENTITIES_GAME_OBJECT_H
