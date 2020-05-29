/*
 * Init state
 * Allan Legemaate
 * 30/12/2016
 * Program inits here
 */
#ifndef INIT_H
#define INIT_H

#include <allegro5/allegro_font.h>


#include "State.h"
#include "../constants/globals.h"
#include "../helpers/tools.h"

class init : public state {
  public:
    // Construct/deconstruct
    init();
    virtual ~init();

    // Override parent
    virtual void update() override {};
    virtual void draw() override {};
};

#endif // INIT_H
