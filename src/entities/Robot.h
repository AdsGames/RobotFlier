/*
 * Robot
 * Spacetoaster!
 * A.D.S. Games
 * 12/01/2017
 */
#ifndef ENTITIES_ROBOT_H
#define ENTITIES_ROBOT_H

#include <vector>

#include "../engine/audio/Sound.h"
#include "../engine/entities/GameObject.h"
#include "../engine/particles/Particle.h"
#include "../engine/textures/Texture.h"

class Robot : public GameObject {
 public:
  Robot(Scene& scene, float x = 0.0f, float y = 0.0f);

  virtual void update() override;
  virtual void draw() override;

  // Getters
  int getHealth() const;
  void addHealth(int amount);

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
  float speed;
  bool alive;
  int invincibleTimer, magneticTimer;
  bool rocket;
  bool onGround;
  int health;

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
