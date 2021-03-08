/*
 * Background
 * Allan Legemaate
 * Renders game background
 * 12/08/2020
 */
#ifndef ENTITIES_BACKGROUND_H
#define ENTITIES_BACKGROUND_H

#include <afk/assets/Texture.h>
#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

class Background : public afk::GameObject {
 public:
  // Constructor
  explicit Background(afk::Scene& scene);

  // Logic override
  virtual void update() override;

  // Draw
  virtual void draw() override;

 private:
  // Change theme
  void changeTheme(const int theme);

  // Textures
  afk::Texture space;
  afk::Texture parallaxBack;
  afk::Texture groundOverlay;
  afk::Texture groundUnderlay;

  // Position
  int scroll;
};

#endif  // ENTITIES_BACKGROUND_H
