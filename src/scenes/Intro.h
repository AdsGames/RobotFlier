/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#ifndef SCNES_INTRO_H
#define SCNES_INTRO_H

#include "../engine/Scene.h"
#include "../engine/Textures/Texture.h"

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

#endif  // SCNES_INTRO_H
