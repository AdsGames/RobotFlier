/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef STATES_INIT_H
#define STATES_INIT_H

#include "../engine/State.h"

class init : public state {
 public:
  // Construct/deconstruct
  init();
  virtual ~init();

  // Override parent
  virtual void update() override{};
  virtual void draw() override;
};

#endif  // STATES_INIT_H
