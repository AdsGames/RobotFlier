/*
 * Init scene
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef SRC_SCENES_INIT_H_
#define SRC_SCENES_INIT_H_

#include <afk/scene/Scene.h>

class Init : public afk::Scene {
 public:
  // Override parent
  void start() override;
  void update(Uint32 delta) override;
};

#endif  // SRC_SCENES_INIT_H_
