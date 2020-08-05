/*
 * Game Object
 * A collision object! Parent class for many others
 * Allan Legemaate
 * 03/01/2017
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>

#include <vector>

#include "../engine/Particles/Particle.h"
#include "../helpers/tools.h"
#include "Robot.h"

class GameObject {
 public:
  // Constructor
  GameObject(ALLEGRO_BITMAP* sprite, const int x, const int y);

  // Destructor
  ~GameObject();

  // Updates asteroid logic
  void logic(int newMotion);

  // Has it been hit?
  bool dead() const;

  // Has it passed the screen bounds?
  bool offScreen() const;

  // Draws the object to screen
  void draw();

 protected:
  // Images
  ALLEGRO_BITMAP* sprite;

  // Position
  float x, y;

  // Size
  int height, width;

  // Dead or naw
  bool isDead;

  // Particles
  std::vector<Particle> parts;

  // Damage
  int damage;
};

#endif  // GAME_OBJECT_H
