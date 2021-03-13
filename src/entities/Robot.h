/*
 * Robot
 * Spacetoaster!
 * A.D.S. Games
 * 12/01/2017
 */
#ifndef SRC_ENTITIES_ROBOT_H_
#define SRC_ENTITIES_ROBOT_H_

#include <afk/entities/GameObject.h>
#include <afk/entities/Particle.h>

#include <vector>

class Robot : public afk::Sprite {
 public:
  explicit Robot(afk::Scene& scene, float x = 0.0f, float y = 0.0f);

  void update(Uint32 delta) override;

  // Getters
  int getHealth() const;
  void addHealth(int amount);

  bool isDead() const;
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
  bool dead;
  int health;

  // Wait for keypress
  bool keyPressed;

  // Particles
  ObjId emitterRocket1Id;
  ObjId emitterRocket2Id;
  ObjId emitterSmokeId;
};

#endif  // SRC_ENTITIES_ROBOT_H_
