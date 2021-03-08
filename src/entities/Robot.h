/*
 * Robot
 * Spacetoaster!
 * A.D.S. Games
 * 12/01/2017
 */
#ifndef ENTITIES_ROBOT_H
#define ENTITIES_ROBOT_H

#include <vector>

#include <afk/assets/Sound.h>
#include <afk/assets/Texture.h>
#include <afk/entities/GameObject.h>
#include <afk/entities/Particle.h>

class Robot : public afk::GameObject {
 public:
  explicit Robot(afk::Scene& scene, float x = 0.0f, float y = 0.0f);

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
  afk::Texture mainRobot;
  afk::Texture robotFire;
  afk::Texture robotInvincible;
  afk::Texture robotInvincibleFire;
  afk::Texture robotInvincibleTop;
  afk::Texture robotDie;
  afk::Texture christmasHat;

  // Sounds
  afk::Sound soundFlame;
  afk::Sound soundHitground;

  // Particles
  std::vector<afk::Particle> rocketPart;
  std::vector<afk::Particle> smokePart;
};

#endif  // ENTITIES_ROBOT_H
