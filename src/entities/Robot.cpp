#include "Robot.h"

#include "../constants/globals.h"
#include "../constants/settings.h"
#include "../engine/Input/JoystickListener.h"
#include "../engine/Input/KeyListener.h"
#include "../engine/Input/MouseListener.h"
#include "../helpers/tools.h"

// Constructor
Robot::Robot() : Robot(0.0f, 0.0f) {}

// Constructor
Robot::Robot(float x, float y) {
  // NULLIFY
  mainRobot = nullptr;
  robotFire = nullptr;
  robotInvincible = nullptr;
  robotInvincibleFire = nullptr;
  robotInvincibleTop = nullptr;
  robotDie = nullptr;
  christmasHat = nullptr;
  soundFlame = nullptr;
  soundHitground = nullptr;

  // Init vars
  gravity = 1.6;

  speed = 0;
  this->x = x;
  this->y = y;
  width = 70;
  height = 70;
  invincibleTimer = 0;
  magneticTimer = 0;

  health = 100;

  rocket = false;
  onGround = false;
  alive = true;
  keyPressed = false;
}

// Destructor
Robot::~Robot() {
  // Clear particles
  rocketPart.clear();
  smokePart.clear();

  // Destroy samples
  al_destroy_sample(soundFlame);
  al_destroy_sample(soundHitground);

  // Destroy images
  al_destroy_bitmap(mainRobot);
  al_destroy_bitmap(robotFire);
  al_destroy_bitmap(robotInvincible);
  al_destroy_bitmap(robotInvincibleFire);
  al_destroy_bitmap(robotInvincibleTop);
  al_destroy_bitmap(robotDie);
  al_destroy_bitmap(christmasHat);
}

// Load images
void Robot::loadResources() {
  // Images
  mainRobot = load_bitmap_ex("images/robot/robot.png");
  robotFire = load_bitmap_ex("images/robot/robotfire.png");
  robotInvincible = load_bitmap_ex("images/robot/robotInvincible.png");
  robotInvincibleFire = load_bitmap_ex("images/robot/robotInvincibleFire.png");
  robotInvincibleTop = load_bitmap_ex("images/robot/robotInvincibleTop.png");
  robotDie = load_bitmap_ex("images/robot/robotDie.png");
  christmasHat = load_bitmap_ex("images/robot/christmas_hat.png");

  // Sounds
  soundFlame = load_sample_ex("audio/sound_flame.wav");
  soundHitground = load_sample_ex("audio/sound_hitground.wav");
}

// Update
void Robot::logic() {
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
    y += gravity - speed;

  // Death smoke
  if (settings.get<int>("particleType", 0) != 3 && !alive) {
    for (int i = 0; i < 800; i++) {
      if (random(0, 10) == 0) {
        int randnum = random(0, 255);
        Particle newParticle(x + 20, y + 20,
                             al_map_rgb(randnum, randnum, randnum),
                             random(-4, -1), random(-5, -3), 1,
                             settings.get<int>("particleType", 0));
        smokePart.push_back(newParticle);
      }
    }
  }

  for (unsigned int i = 0; i < smokePart.size(); i++) {
    smokePart.at(i).update();

    if (random(0, 10) == 0) {
      smokePart.erase(smokePart.begin() + i);
    }
  }

  // Rocket particles
  if (settings.get<int>("particleType", 0) != 3 && rocket) {
    for (int i = 0; i < 800; i++) {
      if (random(0, 10) == 0) {
        ALLEGRO_COLOR part_color = al_map_rgb(255, random(0, 255), 0);

        if (settings.get<bool>("christmas", false)) {
          int red_or_green = random(0, 1);
          part_color =
              al_map_rgb(255 * red_or_green, 255 - red_or_green * 255, 0);
        }

        Particle newParticle1(x + 21, y + 55, part_color, random(-2, 2),
                              random(1, 5), 1,
                              settings.get<int>("particleType", 0));
        Particle newParticle2(x + 52, y + 55, part_color, random(-2, 2),
                              random(0, 4), 1,
                              settings.get<int>("particleType", 0));
        rocketPart.push_back(newParticle1);
        rocketPart.push_back(newParticle2);
      }
    }
  }

  for (unsigned int i = 0; i < rocketPart.size(); i++) {
    rocketPart.at(i).update();

    if (random(0, 2) == 0) {
      rocketPart.erase(rocketPart.begin() + i);
    }
  }

  // Moving controls
  if (alive) {
    // Controls movement up and down
    if ((KeyListener::key[ALLEGRO_KEY_W] || KeyListener::key[ALLEGRO_KEY_UP] ||
         MouseListener::mouse_button & 1) ||
        JoystickListener::button[JOY_XBOX_A] ||
        JoystickListener::button[JOY_XBOX_BUMPER_LEFT]) {
      keyPressed = true;

      if (settings.get<bool>("sound", true) && random(0, 3) == 1)
        al_play_sample(soundFlame, 0.05, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,
                       nullptr);

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

      if (settings.get<bool>("sound", true))
        al_play_sample(soundHitground, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,
                       nullptr);

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
      if (!rocket || settings.get<int>("particleType", 0) != 3)
        al_draw_bitmap(robotInvincible, x, y, 0);
      else if (rocket && settings.get<int>("particleType", 0) == 3)
        al_draw_bitmap(robotInvincibleFire, x, y, 0);
    }
    // Standard
    else {
      if (!rocket || settings.get<int>("particleType", 0) != 3)
        al_draw_bitmap(mainRobot, x, y, 0);
      else if (rocket && settings.get<int>("particleType", 0) == 3)
        al_draw_bitmap(robotFire, x, y, 0);
    }

    // Xmas mode!
    if (settings.get<bool>("christmas", false))
      al_draw_bitmap(christmasHat, x + 20, y - 12, 0);
  }
  // Death image
  else {
    al_draw_bitmap(robotDie, x, y, 0);
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
    al_draw_bitmap(robotInvincibleTop, x, y, 0);
}

// Getters
int Robot::getHealth() const {
  return health;
}
void Robot::addHealth(int amount) {
  health += amount;
}

float Robot::getX() const {
  return x;
}
float Robot::getY() const {
  return y;
}

float Robot::getWidth() const {
  return width;
}
float Robot::getHeight() const {
  return height;
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
