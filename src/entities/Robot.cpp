#include "Robot.h"

#include <afk/entities/ParticleEmitter.h>
#include <afk/random/RandomGenerator.h>
#include <afk/scene/Scene.h>

#include "../constants/globals.h"
#include "Energy.h"

// Gravity const
const float GRAVITY_SPEED = 0.03f;
const float BOUNCE_SPEED = -0.40f;
const float THRUST_SPEED = -0.06f;

// Constructor
Robot::Robot(afk::Scene& scene, const float x, float y)
    : Sprite(scene, "robot", x, y, 1),
      speed(0),
      alive(true),
      invincibleTimer(0),
      magneticTimer(0),
      rocket(false),
      dead(false),
      health(100),
      keyPressed(false) {
  // Set size
  setSize(70, 70);

  // Xmas mode!
  Sprite& xmasHat = scene.add<Sprite>(scene, "christmas_hat", 20, 12, z + 1);
  if (!scene.config.get<bool>("christmas", false)) {
    xmasHat.setVisible(false);
  }
  xmasHat.setParent(id);

  // Add particle emitters
  afk::ParticleEmitter& emitterRocket1 =
      scene.add<afk::ParticleEmitter>(scene, 20, height - 20, z - 1, 10);
  emitterRocket1.disable();
  emitterRocket1Id = emitterRocket1.id;
  emitterRocket1.setParent(id);

  afk::ParticleEmitter& emitterRocket2 =
      scene.add<afk::ParticleEmitter>(scene, 50, height - 20, z - 1, 10);
  emitterRocket2.disable();
  emitterRocket2Id = emitterRocket2.id;
  emitterRocket2.setParent(id);

  afk::ParticleEmitter& emitterSmoke =
      scene.add<afk::ParticleEmitter>(scene, 45, 5, z + 1, 100);
  emitterSmoke.setSize(5, 5);
  emitterSmoke.disable();
  emitterSmokeId = emitterSmoke.id;
  emitterSmoke.setParent(id);

  // Create "realistic" smoke particles
  for (int i = 0; i < 100; i++) {
    afk::Particle particle(scene, 0, 0, 0, afk::ParticleType::IMAGE);
    particle.setLifespan(afk::Random::randomInt(800, 1500));
    particle.setTexture("fuzzball");
    particle.setSize(16.0f, 20.0f);
    particle.setVelocity(afk::Random::randomFloat(-2.0f, -3.0f), -15.0f);
    emitterSmoke.addParticle(particle);
  }

  // Create "realistic" particles
  for (int i = 0; i < 100; i++) {
    afk::Particle particle(scene, 0, 0, 0, afk::ParticleType::SQUARE);
    particle.setSize(2);
    particle.setColor(afk::color::rgb(255, 255, 0), afk::color::rgb(128, 0, 0));
    particle.setVelocity(afk::Random::randomFloat(-25.0, 25.0),
                         afk::Random::randomFloat(100, 150));
    particle.setLifespan(afk::Random::randomInt(30, 80));
    emitterRocket1.addParticle(particle);
    emitterRocket2.addParticle(particle);
  }
}

// Update
void Robot::update(Uint32 delta) {
  // Get emitters
  afk::ParticleEmitter& emitterRocket1 =
      scene.get<afk::ParticleEmitter>(emitterRocket1Id);
  afk::ParticleEmitter& emitterRocket2 =
      scene.get<afk::ParticleEmitter>(emitterRocket2Id);
  afk::ParticleEmitter& emitterSmoke =
      scene.get<afk::ParticleEmitter>(emitterSmokeId);

  // Moving controls
  if (alive) {
    // Check if you are dead!
    if (health <= 0) {
      alive = false;
      health = 0;
    }

    // Power up timers
    if (invincibleTimer > 0) {
      invincibleTimer -= delta;
    }

    if (magneticTimer > 0) {
      magneticTimer -= delta;
    }

    // Update robots y position
    if (keyPressed) {
      speed += GRAVITY_SPEED;
      y += speed * delta;
    }

    // Enable or disable emitters
    if (rocket) {
      emitterRocket1.enable();
      emitterRocket2.enable();
    } else {
      emitterRocket1.disable();
      emitterRocket2.disable();
    }

    // Start the game
    if (scene.input.keyPressed(afk::Keys::W) ||
        scene.input.keyPressed(afk::Keys::UP)) {
      keyPressed = true;
    }

    // Controls movement up and down
    if ((scene.input.keyDown(afk::Keys::W) ||
         scene.input.keyDown(afk::Keys::UP) ||
         scene.input.mouseDown(afk::MouseButtons::LEFT)) ||
        scene.input.joyDown(afk::JoystickButtons::A) ||
        scene.input.joyDown(afk::JoystickButtons::BUMPER_LEFT)) {
      if (afk::Random::randomInt(0, 3) == 1) {
        scene.audio.playSound("flame", 0.05f);
      }

      rocket = true;
      speed += THRUST_SPEED;

    } else if (keyPressed) {
      // If no keys pressed
      rocket = false;
    }

    // Touching top or bottom
    if (y < 0) {
      y = 0;
      speed = 0;
    }

    if (y > 550) {
      speed = BOUNCE_SPEED;
      if (invincibleTimer <= 0) {
        health -= 5;
        scene.audio.playSound("hitground");
        screenshake = 30;
      }
    }

    // Set textures
    if (invincibleTimer > 0) {
      // Invincible
      if (!rocket) {
        setTexture("robotInvincible");
      } else if (rocket) {
        setTexture("robotInvincibleFire");
      }
    } else {
      // Standard
      if (!rocket) {
        setTexture("robot");
      } else if (rocket) {
        setTexture("robotfire");
      }
    }
  }

  // Dying animation
  if (!alive) {
    // Death image
    setTexture("robotDie");
    emitterSmoke.enable();
    if (y >= 550 && !dead) {
      scene.audio.playSound("bomb");
      dead = true;
      y = 550;
      speed = 0;
    }
  }
}

// On collide
void Robot::onCollide(GameObject& other) {
  try {
    dynamic_cast<Energy&>(other);
    addHealth(1);

    score += 5;
    stats[STAT_ENERGY] += 1;

    if (getHealth() < 100) {
      addHealth(1);
    }
  } catch (...) {
    // Nope
  }
}

// Getters
int Robot::getHealth() const {
  return health;
}

void Robot::addHealth(int amount) {
  health += amount;
  if (health > 100) {
    health = 100;
  }
}

bool Robot::isDead() const {
  return dead;
}

bool Robot::isAlive() const {
  return alive;
}

bool Robot::isKeyPressed() const {
  return keyPressed;
}

// Invincibility
bool Robot::isInvincible() const {
  return invincibleTimer > 0;
}

int Robot::getInvincibleTimer() const {
  return invincibleTimer;
}

void Robot::setInvincibleTimer(int time) {
  invincibleTimer += time;
}

// Magnetic
bool Robot::isMagnetic() const {
  return magneticTimer > 0;
}

int Robot::getMagneticTimer() const {
  return magneticTimer;
}

void Robot::setMagneticTimer(int time) {
  magneticTimer += time;
}
