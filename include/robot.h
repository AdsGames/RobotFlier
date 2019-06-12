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

class robot {
  public:
    robot();
    robot (float newX, float newY);
    ~robot();

    void load_resources();
    void logic();
    void draw();
    void draw_overlay();

    // Getters
    int getHealth() const;
    void addHealth (int amount);

    float getX() const;
    float getY() const;

    float getWidth() const;
    float getHeight() const;

    bool isOnGround() const;
    bool isAlive() const;
    bool isKeyPressed() const;

    // Invincibility
    bool isInvincible() const;
    int getInvincibleTimer() const;
    void setInvincibleTimer (int newTimer);

    // Magnetic
    bool isMagnetic() const;
    int getMagneticTimer() const;
    void setMagneticTimer (int newTimer);

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

    // Wait for keypress
    bool keyPressed;

    // Images
    ALLEGRO_BITMAP *main_robot;
    ALLEGRO_BITMAP *robotFire;
    ALLEGRO_BITMAP *robotInvincible;
    ALLEGRO_BITMAP *robotInvincibleFire;
    ALLEGRO_BITMAP *robotInvincibleTop;
    ALLEGRO_BITMAP *robotDie;
    ALLEGRO_BITMAP *christmas_hat;

    // Sounds
    ALLEGRO_SAMPLE *sound_flame;
    ALLEGRO_SAMPLE *sound_hitground;

    // Particles
    std::vector<particle> rocketPart;
    std::vector<particle> smokePart;
};

#endif // ROBOT_H
