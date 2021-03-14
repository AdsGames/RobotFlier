/*
 * Background
 * Allan Legemaate
 * Renders game background
 * 12/08/2020
 */
#ifndef SRC_ENTITIES_BACKGROUND_H_
#define SRC_ENTITIES_BACKGROUND_H_

#include <afk/assets/Texture.h>
#include <afk/entities/GameObject.h>
#include <afk/scene/Scene.h>

class Background : public afk::GameObject {
 public:
  // Constructor
  explicit Background(afk::Scene& scene);

  // Logic override
  void update(Uint32 delta) override;

  // Draw
  void draw() override;

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

#endif  // SRC_ENTITIES_BACKGROUND_H_
