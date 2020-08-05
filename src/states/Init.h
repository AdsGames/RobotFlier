/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef STATE_INIT_H
#define STATE_INIT_H

#include <allegro5/allegro_font.h>

#include "../engine/State.h"
#include "../helpers/tools.h"

class init : public state {
 public:
  // Construct/deconstruct
  init();
  virtual ~init();

  // Override parent
  virtual void update() override{};
  virtual void draw() override{};
};

#endif  // STATE_INIT_H
