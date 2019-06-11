/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef INIT_H
#define INIT_H

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "state.h"
#include "globals.h"
#include "tools.h"

class init : public state {
  public:
    // Construct/deconstruct
    init();
    ~init();

    // Override parent
    void update() {};
    void draw() {};

  protected:

  private:
};

#endif // INIT_H
