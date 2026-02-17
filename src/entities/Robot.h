/*
 * Robot
 * Spacetoaster!
 * A.D.S. Games
 * 12/01/2017
 */
#pragma once

#include <iostream>
#include <vector>

#include "../constants/globals.h"
#include "./Particle.h"

class Robot {
 public:
  Robot();
  Robot(const asw::Vec2<float>& position);

  void loadResources();
  void logic(float deltaTime);
  void draw();
  void drawOverlay();

  // Getters
  int  getHealth() const;
  void addHealth(int amount);

  const asw::Quad<float>& getTransform() const { return transform; }

  bool isOnGround() const;
  bool isAlive() const;
  bool isKeyPressed() const;

  // Invincibility
  bool isInvincible() const;
  int  getInvincibleTimer() const;
  void setInvincibleTimer(int time);

  // Magnetic
  bool isMagnetic() const;
  int  getMagneticTimer() const;
  void setMagneticTimer(int time);

 private:
  // Transform
  asw::Quad<float> transform;

  // Robot specific
  float gravity;
  float speed;
  bool  alive;
  int   invincibleTimer;
  int   magneticTimer;
  bool  rocket;
  bool  onGround;
  int   health;

  // Wait for keypress
  bool keyPressed;

  // Images
  asw::Texture mainRobot;
  asw::Texture robotFire;
  asw::Texture robotInvincible;
  asw::Texture robotInvincibleFire;
  asw::Texture robotInvincibleTop;
  asw::Texture robotDie;
  asw::Texture christmasHat;

  // Sounds
  asw::Sample soundFlame;
  asw::Sample soundHitground;

  // Particles
  std::vector<Particle> rocketPart;
  std::vector<Particle> smokePart;
};
