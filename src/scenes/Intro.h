/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#ifndef SCENES_INTRO_H
#define SCENES_INTRO_H

#include "../engine/scene/Scene.h"
#include "../engine/textures/Texture.h"

class intro : public Scene {
 public:
  // Construct/deconstruct
  intro();
  virtual ~intro(){};

  // Override parent
  virtual void update() override;
  virtual void draw() override{};

 private:
  // Splash image
  Texture img_intro;
};

#endif  // SCENES_INTRO_H
