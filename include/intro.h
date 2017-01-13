/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#ifndef INTRO_H
#define INTRO_H

#include <allegro.h>

#include "state.h"
#include "globals.h"
#include "tools.h"

class intro : public state{
  public:
    // Construct/deconstruct
    intro();
    ~intro();

    // Override parent
    void update() {};
    void draw() {};
  private:
    // Splash image
    BITMAP* img_intro;
};

#endif // INTRO_H
