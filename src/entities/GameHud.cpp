#include "GameHud.h"

#include <algorithm>
#include <fstream>

#include <afk/common/str.h>
#include <afk/services/Services.h>

#include "../constants/globals.h"
#include "../entities/Robot.h"

// Constructor
GameHud::GameHud(afk::Scene& scene, const ObjId robotId)
    : GameObject(scene), robot_id(robotId) {
  // Images
  // Gui
  debug = scene.assets.getImage("debug");

  // Fonts
  orbitron_12 = scene.assets.getFont("orbitron_12");
  orbitron_18 = scene.assets.getFont("orbitron_18");
  orbitron_24 = scene.assets.getFont("orbitron_24");
  orbitron_30 = scene.assets.getFont("orbitron_30");

  // Objects
  powerStar = scene.assets.getImage("powerStar");
  powerMagnet = scene.assets.getImage("powerMagnet");
}

// Draw to screen
void GameHud::draw() {
  // Get Robot
  const Robot& robot = scene.get<Robot>(robot_id);

  // Draw HUD
  // Info
  orbitron_30.draw(10, 10, afk::str::format("Score:%i", score),
                   afk::color::rgb(255, 255, 255));
  orbitron_30.draw(10, 38, afk::str::format("Health:%i", robot.getHealth()),
                   afk::color::rgb(255, 255, 255));
  afk::primitives::rectfill(10, 68, (robot.getHealth() * 1.7), 10,
                            afk::color::rgb(255 - robot.getHealth() * 2.5,
                                            0 + robot.getHealth() * 2.5, 0));

  // Power up timers
  if (robot.isInvincible()) {
    afk::primitives::circle(45, 105, 20, afk::color::rgb(255, 255, 255));
    powerStar.draw(20, 80);
    orbitron_24.draw(44, 94, std::to_string(robot.getInvincibleTimer() / 5),
                     afk::color::rgb(255, 255, 255),
                     afk::FontAlign::ALIGN_CENTER);
    orbitron_24.draw(45, 96, std::to_string(robot.getInvincibleTimer() / 5),
                     afk::color::rgb(255, 0, 0), afk::FontAlign::ALIGN_CENTER);
  }

  if (robot.isMagnetic()) {
    afk::primitives::circle(175, 105, 20, afk::color::rgb(255, 255, 255));
    powerMagnet.draw(175, 150);
    orbitron_24.draw(174, 94, std::to_string(robot.getMagneticTimer() / 5),
                     afk::color::rgb(255, 255, 255),
                     afk::FontAlign::ALIGN_CENTER);
    orbitron_24.draw(175, 96, std::to_string(robot.getMagneticTimer() / 5),
                     afk::color::rgb(255, 0, 0), afk::FontAlign::ALIGN_CENTER);
  }

  // Draw the debug window
  if (scene.config.get<bool>("debug", false)) {
    debug.draw(0, 0);

    // Column 1
    orbitron_12.draw(5, 25, afk::str::format("Motion:%4.2f", motion),
                     afk::color::rgb(255, 255, 255));
    orbitron_12.draw(5, 35, afk::str::format("Robot X:%4.2f", robot.getX()),
                     afk::color::rgb(255, 255, 255));
    orbitron_12.draw(5, 45, afk::str::format("Robot Y:%4.2f", robot.getY()),
                     afk::color::rgb(255, 255, 255));
    orbitron_12.draw(5, 55, afk::str::format("Motion:%4.2f", motion),
                     afk::color::rgb(255, 255, 255));
    orbitron_12.draw(
        5, 65, afk::str::format("Invincible:%i", robot.getInvincibleTimer()),
        afk::color::rgb(255, 255, 255));

    // Column 2
    orbitron_12.draw(120, 25, afk::str::format("Score:%i", score),
                     afk::color::rgb(255, 255, 255));
    orbitron_12.draw(120, 35,
                     afk::str::format("Magnetic:%i", robot.getMagneticTimer()),
                     afk::color::rgb(255, 255, 255));
    orbitron_12.draw(120, 45,
                     afk::str::format("Mouse X:%i", scene.input.mouseX()),
                     afk::color::rgb(255, 255, 255));
    orbitron_12.draw(120, 55,
                     afk::str::format("Mouse Y:%i", scene.input.mouseY()),
                     afk::color::rgb(255, 255, 255));
    orbitron_12.draw(120, 65,
                     afk::str::format("Particles On:%i",
                                      scene.config.get<int>("particleType", 0)),
                     afk::color::rgb(255, 255, 255));

    // Column 3
    // orbitron_12.draw(245, 25,
    //                  afk::str::format("LowScore:%i",
    //                  highscores.getScore(9)), afk::color::rgb(255, 255,
    //                  255));
    // orbitron_12.draw(245, 35, afk::str::format("Theme:%i", themenumber),
    //                  afk::color::rgb(255, 255, 255));
    // orbitron_12.draw(245, 45, afk::str::format("Energys:%i", num_energy),
    //                  afk::color::rgb(255, 255, 255));
    // orbitron_12.draw(245, 55, afk::str::format("Debris:%i", num_debris),
    //                  afk::color::rgb(255, 255, 255));
    // orbitron_12.draw(245, 65, afk::str::format("Powerups:%i", num_powerup),
    //                  afk::color::rgb(255, 255, 255));

    // Column 4
    orbitron_12.draw(
        360, 25, afk::str::format("Last key:%i", scene.input.lastKeyPressed()),
        afk::color::rgb(255, 255, 255));
    // orbitron_12.draw(
    //     360, 35,
    //     afk::str::format("Has highscore:%i", score >
    //     highscores.getScore(9)), afk::color::rgb(255, 255, 255));

    // FPS
    orbitron_18.draw(SCREEN_W - 100, 25,
                     afk::str::format("FPS:%i", scene.display.getFps()),
                     afk::color::rgb(255, 255, 255));
  }
}
