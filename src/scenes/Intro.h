/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#ifndef SCENES_INTRO_H
#define SCENES_INTRO_H

#include <chrono>

#include <afk/assets/Texture.h>
#include <afk/scene/Scene.h>

class Intro : public afk::Scene {
 public:
  // Override parent
  virtual void start() override;
  virtual void update(Uint32 delta) override;
  virtual void draw() override{};
  virtual void stop() override{};

 private:
  // Splash image
  afk::Texture img_intro;

  // Start time
  std::chrono::high_resolution_clock::time_point start_time;
};

#endif  // SCENES_INTRO_H
