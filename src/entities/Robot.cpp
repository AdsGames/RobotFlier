#include "robot.h"

// Constructor
Robot::Robot()
    : Robot({ 0.0f, 0.0f })
{
}

// Constructor
Robot::Robot(const asw::Vec2<float>& position)
{
    // Transform
    transform.size = { 70, 70 };
    transform.position = position;

    // Emitters
    asw::ParticleConfig config_rocket;
    config_rocket.lifetimeMin = 0.2F;
    config_rocket.lifetimeMax = 0.5F;
    config_rocket.speedMin = 1.0F;
    config_rocket.speedMax = 10.0F;
    config_rocket.colorStart = { 255, 200, 50, 255 };
    config_rocket.colorEnd = { 255, 50, 0, 0 };
    config_rocket.sizeStart = 6.0F;
    config_rocket.sizeEnd = 1.0F;
    config_rocket.gravity = { 0.0F, 0.2F };

    emitter_left = asw::ParticleEmitter(config_rocket);
    emitter_left.start();

    emitter_right = asw::ParticleEmitter(config_rocket);
    emitter_right.start();

    // Smoke emitter
    asw::ParticleConfig config_smoke;
    config_smoke.lifetimeMin = 1.0F;
    config_smoke.lifetimeMax = 20.0F;
    config_smoke.speedMin = 0.5F;
    config_smoke.speedMax = 1.5F;
    config_smoke.colorStart = { 255, 255, 255, 200 };
    config_smoke.colorEnd = { 255, 255, 255, 0 };
    config_smoke.sizeStart = 5.0F;
    config_smoke.sizeEnd = 20.0F;
    config_smoke.gravity = { 0.0F, -0.02F };

    emitter_smoke = asw::ParticleEmitter(config_smoke, 512);
    emitter_smoke.start();

    // Images
    mainRobot = asw::assets::loadTexture("assets/images/robot/robot.png");
    robotFire = asw::assets::loadTexture("assets/images/robot/robotfire.png");
    robotInvincible = asw::assets::loadTexture("assets/images/robot/robotInvincible.png");
    robotInvincibleFire = asw::assets::loadTexture("assets/images/robot/robotInvincibleFire.png");
    robotInvincibleTop = asw::assets::loadTexture("assets/images/robot/robotInvincibleTop.png");
    robotDie = asw::assets::loadTexture("assets/images/robot/robotDie.png");
    christmasHat = asw::assets::loadTexture("assets/images/robot/christmas_hat.png");

    // Sounds
    soundFlame = asw::assets::loadSample("assets/audio/sound_flame.wav");
    soundHitground = asw::assets::loadSample("assets/audio/sound_hitground.wav");
}

// Update
void Robot::logic(float deltaTime)
{
    // Check if you are dead!
    if (health < 1) {
        alive = false;
        health = 0;
    }

    // Power up timers
    if (invincibleTimer > 0) {
        invincibleTimer -= deltaTime;
    }

    if (magneticTimer > 0) {
        magneticTimer -= deltaTime;
    }

    // Update robots y position
    if (keyPressed) {
        transform.position.y += (gravity - speed) * (deltaTime * 62.5F);
    }

    // Emitters
    emitter_smoke.transform.position = transform.position + asw::Vec2<float>(35, 35);
    emitter_left.transform.position = transform.position + asw::Vec2<float>(21, 55);
    emitter_right.transform.position = transform.position + asw::Vec2<float>(52, 55);

    emitter_smoke.update(deltaTime);
    emitter_left.update(deltaTime);
    emitter_right.update(deltaTime);

    // Death smoke
    if (settings.particlesEnabled() && !alive) {
        emitter_smoke.emit(100);
        emitter_smoke.setEmissionRate(100.0F);
    }

    // Rocket particles
    if (settings.particlesEnabled() && rocket) {
        emitter_left.setEmissionRate(50.0F);
        emitter_right.setEmissionRate(50.0F);
    } else {
        emitter_left.setEmissionRate(0.0F);
        emitter_right.setEmissionRate(0.0F);
    }

    // Moving controls
    if (alive) {
        // Controls movement up and down
        if ((asw::input::getKey(asw::input::Key::W) || asw::input::getKey(asw::input::Key::Up)
                || asw::input::getMouseButton(asw::input::MouseButton::Left))
            || asw::input::getControllerButton(0, asw::input::ControllerButton::A)
            || asw::input::getControllerButton(0, asw::input::ControllerButton::LeftPaddle1)) {
            keyPressed = true;

            if (asw::random::chance(0.2F)) {
                asw::sound::play(soundFlame, 0.01F);
            }

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
            onGround = true;
        }
    }

    // Touching top or bottom
    if (transform.position.y < 0) {
        transform.position.y = 0;
        speed = 0;
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
void Robot::draw()
{
    // Draw robot sprite
    if (alive) {
        if (!rocket || settings.particlesEnabled()) {
            if (invincibleTimer > 0) {
                asw::draw::sprite(robotInvincible, transform.position);
            } else {
                asw::draw::sprite(mainRobot, transform.position);
            }
        } else if (rocket && !settings.particlesEnabled()) {
            if (invincibleTimer > 0) {
                asw::draw::sprite(robotInvincibleFire, transform.position);
            } else {
                asw::draw::sprite(robotFire, transform.position);
            }
        }

        // Xmas mode!
        if (settings.christmas) {
            asw::draw::sprite(christmasHat, transform.position + asw::Vec2<float>(20, -12));
        }
    }
    // Death image
    else {
        asw::draw::sprite(robotDie, transform.position);
    }

    // Draw particles
    emitter_smoke.draw();
    emitter_left.draw();
    emitter_right.draw();
}

// Draw overlay
void Robot::drawOverlay()
{
    if (alive && invincibleTimer > 0) {
        asw::draw::sprite(robotInvincibleTop, transform.position);
    }
}

// Getters
int Robot::getHealth() const
{
    return health;
}
void Robot::addHealth(int amount)
{
    health += amount;
}

bool Robot::isOnGround() const
{
    return onGround;
}
bool Robot::isAlive() const
{
    return alive;
}
bool Robot::hasBegun() const
{
    return keyPressed;
}

// Invincibility
bool Robot::isInvincible() const
{
    return invincibleTimer > 0;
}
float Robot::getInvincibleTimer() const
{
    return invincibleTimer;
}
void Robot::setInvincibleTimer(float time)
{
    invincibleTimer += time;
}

// Magnetic
bool Robot::isMagnetic() const
{
    return magneticTimer > 0;
}
float Robot::getMagneticTimer() const
{
    return magneticTimer;
}
void Robot::setMagneticTimer(float time)
{
    magneticTimer += time;
}
