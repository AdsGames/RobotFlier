#include "Robot.h"

#include <afk/random/RandomGenerator.h>
#include <afk/scene/Scene.h>
#include <afk/services/Services.h>

#include "../constants/globals.h"

// Gravity const
const float GRAVITY = 1.0f;

// Constructor
Robot::Robot(afk::Scene& scene, const float x, float y)
    : GameObject(scene, x, y, 1) {
  // Init vars
  speed = 0;
  width = 70;
  height = 70;
  invincibleTimer = 0;
  magneticTimer = 0;

  health = 100;

  rocket = false;
  onGround = false;
  alive = true;
  keyPressed = false;

  // Images
  mainRobot = scene.assets.getImage("robot");
  robotFire = scene.assets.getImage("robotfire");
  robotInvincible = scene.assets.getImage("robotInvincible");
  robotInvincibleFire = scene.assets.getImage("robotInvincibleFire");
  robotInvincibleTop = scene.assets.getImage("robotInvincibleTop");
  robotDie = scene.assets.getImage("robotDie");
  christmasHat = scene.assets.getImage("christmas_hat");

  // Sounds
  soundFlame = scene.assets.getAudio("flame");
  soundHitground = scene.assets.getAudio("hitground");
}

// Update
void Robot::update() {
  // Check if you are dead!
  if (health < 1) {
    alive = false;
    health = 0;
  }

  // Power up timers
  if (invincibleTimer > 0)
    invincibleTimer--;

  if (magneticTimer > 0)
    magneticTimer--;

  // Update robots y position
  if (keyPressed)
    y += GRAVITY - speed;

  // Death smoke
  if (scene.config.get<int>("particleType", 0) != 3 && !alive) {
    for (int i = 0; i < 800; i++) {
      if (afk::Random::randomInt(0, 10) == 0) {
        int randnum = afk::Random::randomInt(0, 255);
        afk::Particle newParticle(
            x + 20, y + 20, afk::color::rgb(randnum, randnum, randnum),
            afk::Random::randomInt(-4, -1), afk::Random::randomInt(-5, -3), 1,
            (afk::ParticleType)scene.config.get<int>("particleType", 0));
        smokePart.push_back(newParticle);
      }
    }
  }

  for (unsigned int i = 0; i < smokePart.size(); i++) {
    smokePart.at(i).update();

    if (afk::Random::randomInt(0, 10) == 0) {
      smokePart.erase(smokePart.begin() + i);
    }
  }

  // Rocket particles
  if (scene.config.get<int>("particleType", 0) != 3 && rocket) {
    for (int i = 0; i < 800; i++) {
      if (afk::Random::randomInt(0, 10) == 0) {
        afk::color::Color part_color =
            afk::color::rgb(255, afk::Random::randomInt(0, 255), 0);

        if (scene.config.get<bool>("christmas", false)) {
          int red_or_green = afk::Random::randomInt(0, 1);
          part_color =
              afk::color::rgb(255 * red_or_green, 255 - red_or_green * 255, 0);
        }

        afk::Particle newParticle1(
            x + 21, y + 55, part_color, afk::Random::randomInt(-2, 2),
            afk::Random::randomInt(1, 5), 1,
            (afk::ParticleType)scene.config.get<int>("particleType", 0));
        afk::Particle newParticle2(
            x + 52, y + 55, part_color, afk::Random::randomInt(-2, 2),
            afk::Random::randomInt(0, 4), 1,
            (afk::ParticleType)scene.config.get<int>("particleType", 0));
        rocketPart.push_back(newParticle1);
        rocketPart.push_back(newParticle2);
      }
    }
  }

  for (unsigned int i = 0; i < rocketPart.size(); i++) {
    rocketPart.at(i).update();

    if (afk::Random::randomInt(0, 2) == 0) {
      rocketPart.erase(rocketPart.begin() + i);
    }
  }

  // Moving controls
  if (alive) {
    // Controls movement up and down
    if ((scene.input.keyDown(afk::Keys::W) ||
         scene.input.keyDown(afk::Keys::UP) ||
         scene.input.mouseDown(afk::MouseButtons::LEFT)) ||
        scene.input.joyDown(afk::JoystickButtons::A) ||
        scene.input.joyDown(afk::JoystickButtons::BUMPER_LEFT)) {
      keyPressed = true;

      if (afk::Random::randomInt(0, 3) == 1) {
        soundFlame.play({.gain = 0.01f});
      }

      if (speed < 8) {
        rocket = true;
        speed += 0.6;
      }
    }
    // If no keys pressed
    else if (keyPressed) {
      rocket = false;

      if (speed > -8) {
        speed -= 0.6;
      }
    }
  }

  // Dying animation
  if (!alive) {
    if (y < 550 && !onGround) {
      y += 10;
      speed = 0;
      // clear_keybuf();
    } else if (y >= 550) {
      y = 550;
      onGround = true;
      // clear_keybuf();
    }
  }

  // Touching top or bottom
  if (y < 0) {
    y = 0;
    speed = 0;
  }

  if (y > 550 && alive) {
    speed = 14;

    if (invincibleTimer <= 0) {
      health -= 5;
      soundHitground.play();
      screenshake = 30;
    }
  }
}

// Draw
void Robot::draw() {
  // Draw robot sprite
  if (alive) {
    // Invincible
    if (invincibleTimer > 0) {
      if (!rocket || scene.config.get<int>("particleType", 0) != 3)
        robotInvincible.draw(x, y);
      else if (rocket && scene.config.get<int>("particleType", 0) == 3)
        robotInvincibleFire.draw(x, y);
    }
    // Standard
    else {
      if (!rocket || scene.config.get<int>("particleType", 0) != 3)
        mainRobot.draw(x, y);
      else if (rocket && scene.config.get<int>("particleType", 0) == 3)
        robotFire.draw(x, y);
    }

    // Xmas mode!
    if (scene.config.get<bool>("christmas", false)) {
      christmasHat.draw(x + 20, y - 12);
    }
  }
  // Death image
  else {
    robotDie.draw(x, y);
  }

  // Draw particles
  for (auto& part : rocketPart) {
    part.draw();
  }

  for (auto& part : smokePart) {
    part.draw();
  }

  if (alive && invincibleTimer > 0)
    robotInvincibleTop.draw(x, y);
}

// Getters
int Robot::getHealth() const {
  return health;
}

void Robot::addHealth(int amount) {
  health += amount;
}

bool Robot::isOnGround() const {
  return onGround;
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
