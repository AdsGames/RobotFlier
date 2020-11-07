#include "Robot.h"

#include "../constants/globals.h"
#include "../engine/random/RandomGenerator.h"
#include "../engine/scene/Scene.h"

// Gravity const
const float GRAVITY = 1.0f;

// Constructor
Robot::Robot(Scene& scene, const float x, float y)
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
  mainRobot = scene.getAsset().getImage("robot");
  robotFire = scene.getAsset().getImage("robotfire");
  robotInvincible = scene.getAsset().getImage("robotInvincible");
  robotInvincibleFire = scene.getAsset().getImage("robotInvincibleFire");
  robotInvincibleTop = scene.getAsset().getImage("robotInvincibleTop");
  robotDie = scene.getAsset().getImage("robotDie");
  christmasHat = scene.getAsset().getImage("christmas_hat");

  // Sounds
  soundFlame = scene.getAsset().getAudio("flame");
  soundHitground = scene.getAsset().getAudio("hitground");
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
  if (scene.getSettings().get<int>("particleType", 0) != 3 && !alive) {
    for (int i = 0; i < 800; i++) {
      if (RandomGenerator::randomInt(0, 10) == 0) {
        int randnum = RandomGenerator::randomInt(0, 255);
        Particle newParticle(x + 20, y + 20,
                             al_map_rgb(randnum, randnum, randnum),
                             RandomGenerator::randomInt(-4, -1),
                             RandomGenerator::randomInt(-5, -3), 1,
                             scene.getSettings().get<int>("particleType", 0));
        smokePart.push_back(newParticle);
      }
    }
  }

  for (unsigned int i = 0; i < smokePart.size(); i++) {
    smokePart.at(i).update();

    if (RandomGenerator::randomInt(0, 10) == 0) {
      smokePart.erase(smokePart.begin() + i);
    }
  }

  // Rocket particles
  if (scene.getSettings().get<int>("particleType", 0) != 3 && rocket) {
    for (int i = 0; i < 800; i++) {
      if (RandomGenerator::randomInt(0, 10) == 0) {
        ALLEGRO_COLOR part_color =
            al_map_rgb(255, RandomGenerator::randomInt(0, 255), 0);

        if (scene.getSettings().get<bool>("christmas", false)) {
          int red_or_green = RandomGenerator::randomInt(0, 1);
          part_color =
              al_map_rgb(255 * red_or_green, 255 - red_or_green * 255, 0);
        }

        Particle newParticle1(x + 21, y + 55, part_color,
                              RandomGenerator::randomInt(-2, 2),
                              RandomGenerator::randomInt(1, 5), 1,
                              scene.getSettings().get<int>("particleType", 0));
        Particle newParticle2(x + 52, y + 55, part_color,
                              RandomGenerator::randomInt(-2, 2),
                              RandomGenerator::randomInt(0, 4), 1,
                              scene.getSettings().get<int>("particleType", 0));
        rocketPart.push_back(newParticle1);
        rocketPart.push_back(newParticle2);
      }
    }
  }

  for (unsigned int i = 0; i < rocketPart.size(); i++) {
    rocketPart.at(i).update();

    if (RandomGenerator::randomInt(0, 2) == 0) {
      rocketPart.erase(rocketPart.begin() + i);
    }
  }

  // Moving controls
  if (alive) {
    // Controls movement up and down
    if ((scene.getInput().keyboard().key[ALLEGRO_KEY_W] ||
         scene.getInput().keyboard().key[ALLEGRO_KEY_UP] ||
         scene.getInput().mouse().button[1]) ||
        scene.getInput().joystick().button[JOY_XBOX_A] ||
        scene.getInput().joystick().button[JOY_XBOX_BUMPER_LEFT]) {
      keyPressed = true;

      if (RandomGenerator::randomInt(0, 3) == 1) {
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
      if (!rocket || scene.getSettings().get<int>("particleType", 0) != 3)
        robotInvincible.draw(x, y);
      else if (rocket && scene.getSettings().get<int>("particleType", 0) == 3)
        robotInvincibleFire.draw(x, y);
    }
    // Standard
    else {
      if (!rocket || scene.getSettings().get<int>("particleType", 0) != 3)
        mainRobot.draw(x, y);
      else if (rocket && scene.getSettings().get<int>("particleType", 0) == 3)
        robotFire.draw(x, y);
    }

    // Xmas mode!
    if (scene.getSettings().get<bool>("christmas", false)) {
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
