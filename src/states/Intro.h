/*
 * Intro
 * A.D.S. Games
 * 30/12/2016
 * A pretty nice splash screen
 */
#ifndef INTRO_H
#define INTRO_H

#include "State.h"
#include "../constants/globals.h"
#include "../helpers/tools.h"

class intro : public state {
  public:
    // Construct/deconstruct
    intro();
    virtual ~intro();

    // Override parent
    virtual void update() override;
    virtual void draw() override {};
  private:
    // Splash image
    ALLEGRO_BITMAP *img_intro;
};

#endif // INTRO_H
