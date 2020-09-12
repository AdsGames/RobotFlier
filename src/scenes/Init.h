/*
 * Init scene
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef SCNES_INIT_H
#define SCNES_INIT_H

#include "../engine/Scene.h"

class init : public Scene {
 public:
  // Construct/deconstruct
  init();
  virtual ~init();

  // Override parent
  virtual void update() override{};
  virtual void draw() override;
};

#endif  // SCNES_INIT_H
