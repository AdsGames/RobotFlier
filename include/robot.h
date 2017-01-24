/*
 * Robot
 * Spacetoaster!
 * A.D.S. Games
 * 12/01/2017
 */
#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include <iostream>
#include "particle.h"
#include "keyListener.h"
#include "mouseListener.h"
#include "joystickListener.h"
#include "tools.h"
#include "globals.h"

class robot{
  public:
    robot();
    robot( float newX, float newY);
    ~robot();

    void load_resources();
    void logic();
    void draw();
    void draw_overlay();

    // Getters
    int getHealth(){ return health;}
    void addHealth( int amount){ health += amount; }

    float getX(){ return x; }
    float getY(){ return y; }

    float getWidth(){ return width; }
    float getHeight(){ return height; }

    bool isOnGround(){ return onGround; }
    bool isAlive(){ return alive;}

    // Invincibility
    bool isInvincible(){ return invincibleTimer > 0;}
    int getInvincibleTimer(){ return invincibleTimer; }
    void setInvincibleTimer( int newTimer){ invincibleTimer += newTimer; }

    // Magnetic
    bool isMagnetic(){ return magneticTimer > 0;}
    int getMagneticTimer(){ return magneticTimer; }
    void setMagneticTimer( int newTimer){ magneticTimer += newTimer; }
  protected:

  private:
    // Robot specific
    float gravity, speed;
    bool alive;
    int invincibleTimer, magneticTimer;
    bool rocket;
    bool onGround;
    float x, y;
    int health;
    int width, height;

    // Images
    ALLEGRO_BITMAP *main_robot;
    ALLEGRO_BITMAP *robotFire;
    ALLEGRO_BITMAP *robotInvincible;
    ALLEGRO_BITMAP *robotInvincibleFire;
    ALLEGRO_BITMAP *robotInvincibleTop;
    ALLEGRO_BITMAP *robotDie;
    ALLEGRO_BITMAP *christmas_hat;

    // Sounds
    ALLEGRO_SAMPLE* sound_flame;
    ALLEGRO_SAMPLE* sound_hitground;

    // Particles
    std::vector<particle> rocketPart;
    std::vector<particle> smokePart;
};

#endif // ROBOT_H
