/*
 * Robot
 * Spacetoaster!
 * A.D.S. Games
 * 12/01/2017
 */
#ifndef ENTITIES_ROBOT_H
#define ENTITIES_ROBOT_H

#include <vector>

#include "../engine/Audio/Sound.h"
#include "../engine/Particles/Particle.h"
#include "../engine/Textures/Texture.h"

class Robot {
 public:
  Robot(float x = 0.0f, float y = 0.0f);

  void logic();
  void draw();
  void drawOverlay();
  void loadResources();

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
  Texture mainRobot;
  Texture robotFire;
  Texture robotInvincible;
  Texture robotInvincibleFire;
  Texture robotInvincibleTop;
  Texture robotDie;
  Texture christmasHat;

  // Sounds
  Sound soundFlame;
  Sound soundHitground;

  // Particles
  std::vector<Particle> rocketPart;
  std::vector<Particle> smokePart;
};

#endif  // ENTITIES_ROBOT_H
