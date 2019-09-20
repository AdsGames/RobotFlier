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
#include "input/keyListener.h"
#include "input/mouseListener.h"
#include "input/joystickListener.h"
#include "tools.h"
#include "globals.h"

class Robot {
  public:
    Robot();
    Robot(float x, float y);
    ~Robot();

    void loadResources();
    void logic();
    void draw();
    void drawOverlay();

    // Getters
    int getHealth() const;
    void addHealth(int amount);

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
    void setInvincibleTimer(int time);

    // Magnetic
    bool isMagnetic() const;
    int getMagneticTimer() const;
    void setMagneticTimer(int time);

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
    ALLEGRO_BITMAP *mainRobot;
    ALLEGRO_BITMAP *robotFire;
    ALLEGRO_BITMAP *robotInvincible;
    ALLEGRO_BITMAP *robotInvincibleFire;
    ALLEGRO_BITMAP *robotInvincibleTop;
    ALLEGRO_BITMAP *robotDie;
    ALLEGRO_BITMAP *christmasHat;

    // Sounds
    ALLEGRO_SAMPLE *soundFlame;
    ALLEGRO_SAMPLE *soundHitground;

    // Particles
    std::vector<Particle> rocketPart;
    std::vector<Particle> smokePart;
};

#endif // ROBOT_H
