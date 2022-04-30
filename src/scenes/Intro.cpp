#include "Intro.h"

#include <afk/common/math.h>
#include <afk/components/Sprite.h>
#include <afk/primitives/Primitives.h>

const int INTRO_TIME = 0;

// Construct scene
void Intro::start() {
  start_time = std::chrono::high_resolution_clock::now();
  // Load intro image
  auto intro = createEntity();
  createComponent<afk::Sprite>(intro, assets.getImage("intro"));
  createComponent<afk::Transform>(intro, afk::Vec3(0, 0, 0),
                                  afk::Vec2(800, 600));
}

// Update (goto menu!)
void Intro::update(Uint32 delta) {
  auto current_time = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = current_time - start_time;
  if (elapsed.count() > INTRO_TIME || input.anyKeyDown()) {
    // Go to menu
    scene.setNextScene("menu");
  }

  Scene::update(delta);
}
