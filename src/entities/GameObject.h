/*
 * Game Object
 * A collision object! Parent class for many others
 * Allan Legemaate
 * 03/01/2017
 */

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <asw/asw.h>

#include "../constants/globals.h"
#include "./Robot.h"

class GameObject {
 public:
  // Constructor
  GameObject(asw::Texture sprite, const asw::Vec2<float>& position);

  // Has it been hit?
  bool dead() const;

  // Has it passed the screen bounds?
  bool offScreen() const;

  // Draws the object to screen
  void draw() const;

 protected:
  // Images
  asw::Texture sprite;

  // Position
  asw::Quad<float> transform;

  // Dead or naw
  bool isDead;

  // Damage
  int damage;
};

#endif  // GAME_OBJECT_H
