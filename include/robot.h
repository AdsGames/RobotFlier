/*
 * Robot
 * Spacetoaster!
 * A.D.S. Games
 * 12/01/2017
 */
#ifndef ROBOT_H
#define ROBOT_H

#include <allegro.h>
#include <vector>
#include "particle.h"
#include "globals.h"

class robot{
  public:
    robot();
    robot( float newX, float newY);
    virtual ~robot();

    void logic();
    void draw( BITMAP *tempImage);
    void draw_overlay( BITMAP *tempImage);

    // Robot specific
    float gravity, speed;
    bool alive;
    bool rocket;
    bool onGround;
    float x, y;
  protected:

  private:
    // Images
    BITMAP *main_robot;
    BITMAP *robotFire;
    BITMAP *robotInvincible;
    BITMAP *robotInvincibleFire;
    BITMAP *robotInvincibleTop;
    BITMAP *robotDie;
    BITMAP *christmas_hat;

    // Sounds
    SAMPLE* sound_flame;
    SAMPLE* sound_hitground;

    // Particles
    std::vector<particle> rocketPart;
    std::vector<particle> smokePart;
};

#endif // ROBOT_H
