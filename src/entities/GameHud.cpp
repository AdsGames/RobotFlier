#include "GameHud.h"

#include <algorithm>
#include <fstream>

#include "../constants/globals.h"
#include "../engine/common/stringFns.h"
#include "../entities/Robot.h"

// Constructor
GameHud::GameHud(Scene& scene, const ObjId robotId)
    : GameObject(scene), robot_id(robotId) {
  // Images
  // Gui
  debug = scene.getAsset().getImage("debug");

  // Fonts
  orbitron_12 = scene.getAsset().getFont("orbitron_12");
  orbitron_18 = scene.getAsset().getFont("orbitron_18");
  orbitron_24 = scene.getAsset().getFont("orbitron_24");
  orbitron_30 = scene.getAsset().getFont("orbitron_30");

  // Objects
  powerStar = scene.getAsset().getImage("powerStar");
  powerMagnet = scene.getAsset().getImage("powerMagnet");
}

// Draw to screen
void GameHud::draw() {
  // Get Robot
  const Robot& robot = scene.get<Robot>(robot_id);

  // Draw HUD
  // Info
  orbitron_30.draw(10, 10, stringFns::format("Score:%i", score),
                   al_map_rgb(255, 255, 255));
  orbitron_30.draw(10, 38, stringFns::format("Health:%i", robot.getHealth()),
                   al_map_rgb(255, 255, 255));
  al_draw_filled_rectangle(10, 68, 10 + (robot.getHealth() * 1.7), 78,
                           al_map_rgb(255 - robot.getHealth() * 2.5,
                                      0 + robot.getHealth() * 2.5, 0));

  // Power up timers
  if (robot.isInvincible()) {
    al_draw_filled_circle(45, 105, 20, al_map_rgb(255, 255, 255));
    powerStar.draw(20, 80);
    orbitron_24.draw(44, 94, std::to_string(robot.getInvincibleTimer() / 5),
                     al_map_rgb(255, 255, 255), ALLEGRO_ALIGN_CENTER);
    orbitron_24.draw(45, 96, std::to_string(robot.getInvincibleTimer() / 5),
                     al_map_rgb(255, 0, 0), ALLEGRO_ALIGN_CENTER);
  }

  if (robot.isMagnetic()) {
    al_draw_filled_circle(175, 105, 20, al_map_rgb(255, 255, 255));
    powerMagnet.draw(175, 150, 80);
    orbitron_24.draw(174, 94, std::to_string(robot.getMagneticTimer() / 5),
                     al_map_rgb(255, 255, 255), ALLEGRO_ALIGN_CENTER);
    orbitron_24.draw(175, 96, std::to_string(robot.getMagneticTimer() / 5),
                     al_map_rgb(255, 0, 0), ALLEGRO_ALIGN_CENTER);
  }

  // Draw the debug window
  if (scene.getSettings().get<bool>("debug", false)) {
    debug.draw(0, 0, 0);

    // Column 1
    orbitron_12.draw(5, 25, stringFns::format("Motion:%4.2f", motion),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(5, 35, stringFns::format("Robot X:%4.2f", robot.getX()),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(5, 45, stringFns::format("Robot Y:%4.2f", robot.getY()),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(5, 55, stringFns::format("Motion:%4.2f", motion),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(
        5, 65, stringFns::format("Invincible:%i", robot.getInvincibleTimer()),
        al_map_rgb(255, 255, 255));

    // Column 2
    orbitron_12.draw(120, 25, stringFns::format("Score:%i", score),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(120, 35,
                     stringFns::format("Magnetic:%i", robot.getMagneticTimer()),
                     al_map_rgb(255, 255, 255));
    orbitron_12.draw(
        120, 45, stringFns::format("Mouse X:%i", scene.getInput().mouse().x),
        al_map_rgb(255, 255, 255));
    orbitron_12.draw(
        120, 55, stringFns::format("Mouse Y:%i", scene.getInput().mouse().y),
        al_map_rgb(255, 255, 255));
    orbitron_12.draw(
        120, 65,
        stringFns::format("Particles On:%i",
                          scene.getSettings().get<int>("particleType", 0)),
        al_map_rgb(255, 255, 255));

    // Column 3
    // orbitron_12.draw(245, 25,
    //                  stringFns::format("LowScore:%i",
    //                  highscores.getScore(9)), al_map_rgb(255, 255, 255));
    // orbitron_12.draw(245, 35, stringFns::format("Theme:%i", themenumber),
    //                  al_map_rgb(255, 255, 255));
    // orbitron_12.draw(245, 45, stringFns::format("Energys:%i", num_energy),
    //                  al_map_rgb(255, 255, 255));
    // orbitron_12.draw(245, 55, stringFns::format("Debris:%i", num_debris),
    //                  al_map_rgb(255, 255, 255));
    // orbitron_12.draw(245, 65, stringFns::format("Powerups:%i", num_powerup),
    //                  al_map_rgb(255, 255, 255));

    // Column 4
    orbitron_12.draw(
        360, 25,
        stringFns::format("Last key:%i",
                          scene.getInput().keyboard().lastKeyPressed),
        al_map_rgb(255, 255, 255));
    // orbitron_12.draw(
    //     360, 35,
    //     stringFns::format("Has highscore:%i", score >
    //     highscores.getScore(9)), al_map_rgb(255, 255, 255));

    // FPS
    orbitron_18.draw(SCREEN_W - 100, 25, stringFns::format("FPS:%i", fps),
                     al_map_rgb(255, 255, 255));
  }
}
