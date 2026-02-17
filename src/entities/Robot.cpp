#include "Robot.h"

// Constructor
Robot::Robot() : Robot({0.0f, 0.0f}) {}

// Constructor
Robot::Robot(const asw::Vec2<float>& position) {
  // NULLIFY
  mainRobot           = nullptr;
  robotFire           = nullptr;
  robotInvincible     = nullptr;
  robotInvincibleFire = nullptr;
  robotInvincibleTop  = nullptr;
  robotDie            = nullptr;
  christmasHat        = nullptr;
  soundFlame          = nullptr;
  soundHitground      = nullptr;

  // Init vars
  gravity = 1.6F;

  speed              = 0;
  transform.position = position;
  transform.size     = {70, 70};
  invincibleTimer    = 0;
  magneticTimer      = 0;

  health = 100;

  rocket     = false;
  onGround   = false;
  alive      = true;
  keyPressed = false;
}

// Load images
void Robot::loadResources() {
  // Images
  mainRobot = asw::assets::loadTexture("assets/images/robot/robot.png");
  robotFire = asw::assets::loadTexture("assets/images/robot/robotfire.png");
  robotInvincible =
      asw::assets::loadTexture("assets/images/robot/robotInvincible.png");
  robotInvincibleFire =
      asw::assets::loadTexture("assets/images/robot/robotInvincibleFire.png");
  robotInvincibleTop =
      asw::assets::loadTexture("assets/images/robot/robotInvincibleTop.png");
  robotDie = asw::assets::loadTexture("assets/images/robot/robotDie.png");
  christmasHat =
      asw::assets::loadTexture("assets/images/robot/christmas_hat.png");

  // Sounds
  soundFlame     = asw::assets::loadSample("assets/audio/sound_flame.wav");
  soundHitground = asw::assets::loadSample("assets/audio/sound_hitground.wav");
}

// Update
void Robot::logic(float deltaTime) {
  // Check if you are dead!
  if (health < 1) {
    alive  = false;
    health = 0;
  }

  // Power up timers
  if (invincibleTimer > 0) {
    invincibleTimer--;
  }

  if (magneticTimer > 0) {
    magneticTimer--;
  }

  // Update robots y position
  if (keyPressed) {
    transform.position.y += (gravity - speed) * (deltaTime / 16.0F);
  }

  // Death smoke
  if (settings[SETTING_PARTICLE_TYPE] != 3 && !alive) {
    for (int i = 0; i < 800; i++) {
      if (asw::random::between(0, 10) == 0) {
        int      randnum = asw::random::between(0, 255);
        Particle newParticle(
            transform.position.x + 20, transform.position.y + 20,
            asw::Color(randnum, randnum, randnum), asw::random::between(-4, -1),
            asw::random::between(-5, -3), 1, settings[SETTING_PARTICLE_TYPE]);
        smokePart.push_back(newParticle);
      }
    }
  }

  for (unsigned int i = 0; i < smokePart.size(); i++) {
    smokePart.at(i).update(deltaTime);

    if (asw::random::between(0, 10) == 0) {
      smokePart.erase(smokePart.begin() + i);
    }
  }

  // Rocket particles
  if (settings[SETTING_PARTICLE_TYPE] != 3 && rocket) {
    for (int i = 0; i < 800; i++) {
      if (asw::random::between(0, 10) == 0) {
        auto part_color = asw::Color(255, asw::random::between(0, 255), 0);

        if (settings[SETTING_CHRISTMAS]) {
          int red_or_green = asw::random::between(0, 1);
          part_color =
              asw::Color(255 * red_or_green, 255 - red_or_green * 255, 0);
        }

        Particle newParticle1(
            transform.position.x + 21, transform.position.y + 55, part_color,
            asw::random::between(-2, 2), asw::random::between(1, 5), 1,
            settings[SETTING_PARTICLE_TYPE]);
        Particle newParticle2(
            transform.position.x + 52, transform.position.y + 55, part_color,
            asw::random::between(-2, 2), asw::random::between(0, 4), 1,
            settings[SETTING_PARTICLE_TYPE]);
        rocketPart.push_back(newParticle1);
        rocketPart.push_back(newParticle2);
      }
    }
  }

  for (unsigned int i = 0; i < rocketPart.size(); i++) {
    rocketPart.at(i).update(deltaTime);

    if (asw::random::between(0, 2) == 0) {
      rocketPart.erase(rocketPart.begin() + i);
    }
  }

  // Moving controls
  if (alive) {
    // Controls movement up and down
    if ((asw::input::getKey(asw::input::Key::W) ||
         asw::input::getKey(asw::input::Key::Up) ||
         asw::input::getMouseButton(asw::input::MouseButton::Left)) ||
        asw::input::getControllerButton(0, asw::input::ControllerButton::A) ||
        asw::input::getControllerButton(
            0, asw::input::ControllerButton::LeftPaddle1)) {
      keyPressed = true;

      if (asw::random::between(0, 3) == 1)
        asw::sound::play(soundFlame, 0.05F);

      if (speed < 8) {
        rocket = true;
        speed += 0.6F;
      }
    }
    // If no keys pressed
    else if (keyPressed) {
      rocket = false;

      if (speed > -8) {
        speed -= 0.6F;
      }
    }
  }

  // Dying animation
  if (!alive) {
    if (transform.position.y < 550 && !onGround) {
      transform.position.y += 10;
      speed = 0;
    } else if (transform.position.y >= 550) {
      transform.position.y = 550;
      onGround             = true;
    }
  }

  // Touching top or bottom
  if (transform.position.y < 0) {
    transform.position.y = 0;
    speed                = 0;
  }

  if (transform.position.y > 550 && alive) {
    speed = 14;

    if (invincibleTimer <= 0) {
      health -= 5;
      asw::sound::play(soundHitground);
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
      if (!rocket || settings[SETTING_PARTICLE_TYPE] != 3) {
        asw::draw::sprite(robotInvincible, transform.position);
      } else if (rocket && settings[SETTING_PARTICLE_TYPE] == 3) {
        asw::draw::sprite(robotInvincibleFire, transform.position);
      }
    }
    // Standard
    else {
      if (!rocket || settings[SETTING_PARTICLE_TYPE] != 3) {
        asw::draw::sprite(mainRobot, transform.position);
      } else if (rocket && settings[SETTING_PARTICLE_TYPE] == 3) {
        asw::draw::sprite(robotFire, transform.position);
      }
    }

    // Xmas mode!
    if (settings[SETTING_CHRISTMAS]) {
      asw::draw::sprite(christmasHat,
                        transform.position + asw::Vec2<float>(20, -12));
    }
  }
  // Death image
  else {
    asw::draw::sprite(robotDie, transform.position);
  }

  // Draw particles
  for (auto& part : rocketPart)
    part.draw();

  for (auto& part : smokePart)
    part.draw();
}

// Draw overlay
void Robot::drawOverlay() {
  if (alive && invincibleTimer > 0)
    asw::draw::sprite(robotInvincibleTop, transform.position);
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
