/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#ifndef SRC_SCENES_INTRO_H_
#define SRC_SCENES_INTRO_H_

#include <afk/assets/Texture.h>
#include <afk/scene/Scene.h>

#include <chrono>

class Intro : public afk::Scene {
 public:
  // Override parent
  void start() override;
  void update(Uint32 delta) override;

 private:
  // Splash image
  afk::Texture img_intro;

  // Start time
  std::chrono::high_resolution_clock::time_point start_time;
};

#endif  // SRC_SCENES_INTRO_H_
