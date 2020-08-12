/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#ifndef STATE_INTRO_H
#define STATE_INTRO_H

#include "../engine/State.h"
#include "../engine/Textures/Texture.h"

class intro : public state {
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

#endif  // STATE_INTRO_H
