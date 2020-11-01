/*
 * Init scene
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef SCENES_INIT_H
#define SCENES_INIT_H

#include "../engine/scene/Scene.h"

class Init : public Scene {
 public:
  // Construct/deconstruct
  Init();
  virtual ~Init();

  // Override parent
  virtual void update() override{};
  virtual void draw() override;
};

#endif  // SCENES_INIT_H
