/*
 * Background
 * Allan Legemaate
 * Renders game background
 * 12/08/2020
 */
#ifndef ENTITIES_BACKGROUND_H
#define ENTITIES_BACKGROUND_H

#include "../engine/audio/Sound.h"
#include "../engine/entities/GameObject.h"
#include "../engine/scene/Scene.h"

class Background : public GameObject {
 public:
  // Constructor
  Background(const Scene& scene);

  // Logic override
  virtual void update() override;

  // Draw
  virtual void draw() override;

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
