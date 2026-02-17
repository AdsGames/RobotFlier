/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#pragma once

#include "../constants/globals.h"
#include "../helpers/tools.h"
#include "State.h"

class IntroScene : public asw::scene::Scene<Scenes> {
 public:
  // Construct/deconstruct
  using asw::scene::Scene<Scenes>::Scene;

  // Override parent
  void init() override;
  void update(float deltaTime) override;

 private:
  // Splash image
  asw::Texture img_intro;
};
