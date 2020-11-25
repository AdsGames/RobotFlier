/*
 * Init scene
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef SCENES_INIT_H
#define SCENES_INIT_H

#include <afk/scene/Scene.h>

class Init : public Scene {
 public:
  // Override parent
  virtual void start() override;
  virtual void update() override;
  virtual void draw() override{};
  virtual void stop() override{};
};

#endif  // SCENES_INIT_H
