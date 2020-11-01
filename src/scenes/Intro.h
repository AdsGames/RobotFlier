/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#ifndef SCENES_INTRO_H
#define SCENES_INTRO_H

#include <chrono>

#include "../engine/scene/Scene.h"
#include "../engine/textures/Texture.h"

class Intro : public Scene {
 public:
  // Construct/deconstruct
  Intro();
  virtual ~Intro(){};

  // Override parent
  virtual void update() override;
  virtual void draw() override{};

 private:
  // Splash image
  Texture img_intro;

  // Start time
  std::chrono::high_resolution_clock::time_point start_time;
};

#endif  // SCENES_INTRO_H
