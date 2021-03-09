/*
 * Init scene
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef SCENES_INIT_H
#define SCENES_INIT_H

#include <afk/scene/Scene.h>

class Init : public afk::Scene {
 public:
  // Override parent
  virtual void start() override;
  virtual void update(Uint32 delta) override;
  virtual void draw() override{};
  virtual void stop() override{};
};

#endif  // SCENES_INIT_H
