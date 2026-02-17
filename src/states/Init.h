/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#pragma once

#include <asw/asw.h>

#include "../constants/globals.h"
#include "../helpers/tools.h"
#include "State.h"

class InitScene : public asw::scene::Scene<Scenes> {
 public:
  using asw::scene::Scene<Scenes>::Scene;

  // Override parent
  void init() override;

  void update(float deltaTime) override {
    // Go to menu
    sceneManager.setNextScene(Scenes::Menu);
  }
};
