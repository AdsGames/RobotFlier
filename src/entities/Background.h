/*
 * Background
 * Allan Legemaate
 * Renders game background
 * 12/08/2020
 */
#ifndef ENTITIES_BACKGROUND_H
#define ENTITIES_BACKGROUND_H

#include "../engine/Audio/Sound.h"
#include "GameObject.h"

class Background : public GameObject {
 public:
  // Constructor
  Background();

  // Logic override
  void update(const int motion);

  // Move towards point
  void draw();

 private:
  // Change theme
  void changeTheme(const int theme);

  // Images
  Texture space;
  Texture parallaxBack;
  Texture groundOverlay;
  Texture groundUnderlay;

  // Position
  int scroll;
};

#endif  // ENTITIES_BACKGROUND_H
