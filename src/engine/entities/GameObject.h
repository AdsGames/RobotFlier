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

#include "../particles/Particle.h"
#include "../scene/Scene.h"
#include "../textures/Texture.h"

class GameObject {
 public:
  // Constructor
  GameObject(const Scene& scene,
             const float x = 0.0f,
             const float y = 0.0f,
             const int z = 0);

  // Destructor
  virtual ~GameObject();

  // Updates game object
  virtual void update();

  // Set game object texture
  void setTexture(const std::string& texture);

  // Is colliding with game object
  bool colliding(const GameObject& other);

  // On collide
  virtual void onCollide(const GameObject& other);

  // Has it been hit?
  bool dead() const;

  // Has it passed the screen bounds?
  bool offScreen() const;

  // Draws the object to screen
  virtual void draw();

  // Get z index
  int getZ();

 protected:
  // Current scene
  const Scene& scene;

  // Images
  Texture texture;

  // Position
  float x, y;
  int z;

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
