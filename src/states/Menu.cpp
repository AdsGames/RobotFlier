#include "Menu.h"

#include <fstream>

// Construct state
void MenuScene::init() {
  // Init vars
  startMove       = false;
  startClicked    = false;
  mouse_rocket_up = false;
  mouseMove       = asw::input::mouse.position.y;

  // Screen on
  mini_screen = MINISTATE_MENU;

  // Load intro image
  // Random menu
  const auto background =
      std::format("assets/images/backgrounds/background_{}.png",
                  asw::random::between(0, 3));
  img_menu = asw::assets::loadTexture(background);

  start = asw::assets::loadTexture("assets/images/gui/start.png");
  highscores_button =
      asw::assets::loadTexture("assets/images/gui/highscores.png");
  mouse        = asw::assets::loadTexture("assets/images/gui/mouse.png");
  mouse_rocket = asw::assets::loadTexture("assets/images/gui/mouse_rocket.png");
  title        = asw::assets::loadTexture("assets/images/gui/title.png");
  options      = asw::assets::loadTexture("assets/images/gui/options.png");

  ui_sound[1] = asw::assets::loadTexture("assets/images/gui/ui_sound_on.png");
  ui_sound[0] = asw::assets::loadTexture("assets/images/gui/ui_sound_off.png");

  ui_music[1] = asw::assets::loadTexture("assets/images/gui/ui_music_on.png");
  ui_music[0] = asw::assets::loadTexture("assets/images/gui/ui_music_off.png");

  ui_window[1] =
      asw::assets::loadTexture("assets/images/gui/ui_window_windowed.png");
  ui_window[0] =
      asw::assets::loadTexture("assets/images/gui/ui_window_fullscreen.png");

  ui_particle[0] =
      asw::assets::loadTexture("assets/images/gui/ui_particle_circle.png");
  ui_particle[1] =
      asw::assets::loadTexture("assets/images/gui/ui_particle_square.png");
  ui_particle[2] =
      asw::assets::loadTexture("assets/images/gui/ui_particle_pixel.png");
  ui_particle[3] =
      asw::assets::loadTexture("assets/images/gui/ui_particle_off.png");

  ui_control[0] =
      asw::assets::loadTexture("assets/images/gui/ui_control_xbox.png");
  ui_control[1] =
      asw::assets::loadTexture("assets/images/gui/ui_control_keyboard.png");
  ui_control[2] =
      asw::assets::loadTexture("assets/images/gui/ui_control_auto.png");

  ui_screenshake[0] =
      asw::assets::loadTexture("assets/images/gui/ui_screenshake_none.png");
  ui_screenshake[1] =
      asw::assets::loadTexture("assets/images/gui/ui_screenshake_low.png");
  ui_screenshake[2] =
      asw::assets::loadTexture("assets/images/gui/ui_screenshake_medium.png");
  ui_screenshake[3] =
      asw::assets::loadTexture("assets/images/gui/ui_screenshake_high.png");

  ui_options = asw::assets::loadTexture("assets/images/gui/ui_options.png");
  ui_options_small =
      asw::assets::loadTexture("assets/images/gui/ui_options_small.png");
  ui_back    = asw::assets::loadTexture("assets/images/gui/ui_back.png");
  credits    = asw::assets::loadTexture("assets/images/gui/credits.png");
  ui_credits = asw::assets::loadTexture("assets/images/gui/ui_credits.png");
  highscores_table =
      asw::assets::loadTexture("assets/images/gui/highscores_table.png");
  ui_help    = asw::assets::loadTexture("assets/images/gui/ui_help.png");
  helpScreen = asw::assets::loadTexture("assets/images/gui/helpScreen.png");
  ui_exit    = asw::assets::loadTexture("assets/images/gui/ui_exit.png");
  xbox_start = asw::assets::loadTexture("assets/images/gui/xbox_start.png");
  ui_screenshot_notification = asw::assets::loadTexture(
      "assets/images/gui/ui_screenshot_notification.png");
  ui_controls = asw::assets::loadTexture("assets/images/gui/ui_controls.png");
  controls    = asw::assets::loadTexture("assets/images/gui/controls.png");

  // Load that menu music
  music_mainmenu = asw::assets::loadMusic("assets/audio/music_mainmenu.ogg");

  // Read settings from file
  read_settings();

  // Init animation vars
  animation_pos = 0;

  // Load scores
  highscores = ScoreTable("scores.dat");

  // Play music
  if (settings[SETTING_MUSIC] == 1) {
    asw::sound::playMusic(music_mainmenu);
  }
}

// Writes the settings to file
void MenuScene::write_settings() {
  std::ofstream settings_file("data/settings.dat");

  for (int i = 0; i < 7; i++) {
    settings_file << settings[i] << " ";
  }

  settings_file.close();
}

// Reads the data from file
void MenuScene::read_settings() {
  std::ifstream read("data/settings.dat");

  for (int i = 0; i < 7; i++)
    read >> settings[i];

  read.close();
}

// Update loop
void MenuScene::update(float deltaTime) {
  // Menu animations
  if (animation_pos < 100 && !startClicked)
    animation_pos += 4;

  if (animation_pos > 0 && startClicked)
    animation_pos -= 4;

  // Start the game
  if (startClicked && animation_pos <= 0) {
    sceneManager.setNextScene(Scenes::Game);
  }

  // Open submenu or start game
  if (mini_screen == MINISTATE_MENU) {
    // Start game with controller
    if (asw::input::getControllerButtonDown(
            0, asw::input::ControllerButton::Start) ||
        asw::input::getControllerButtonDown(0,
                                            asw::input::ControllerButton::A)) {
      startClicked = true;
    }

    // Buttons
    if (asw::input::getMouseButtonDown(asw::input::MouseButton::Left)) {
      // Start game
      if (collision(asw::input::mouse.position.x, asw::input::mouse.position.x,
                    40, 40 + (start->w), asw::input::mouse.position.y,
                    asw::input::mouse.position.y, 410, 410 + (start->h))) {
        startClicked = true;
      }
      // Scores
      else if (collision(
                   asw::input::mouse.position.x, asw::input::mouse.position.x,
                   660, 660 + (highscores_button->w),
                   asw::input::mouse.position.y, asw::input::mouse.position.y,
                   30, 30 + (highscores_button->h))) {
        mini_screen = MINISTATE_SCORES;
      }
      // Credits menu
      else if (collision(asw::input::mouse.position.x,
                         asw::input::mouse.position.x, 542, 644,
                         asw::input::mouse.position.y,
                         asw::input::mouse.position.y, 548, 600)) {
        mini_screen = MINISTATE_CREDITS;
      }
      // Controls menu
      else if (collision(asw::input::mouse.position.x,
                         asw::input::mouse.position.x, 644, 696,
                         asw::input::mouse.position.y,
                         asw::input::mouse.position.y, 548, 600)) {
        mini_screen = MINISTATE_CONTROLS;
      }
      // Help screen
      else if (collision(asw::input::mouse.position.x,
                         asw::input::mouse.position.x, 696, 749,
                         asw::input::mouse.position.y,
                         asw::input::mouse.position.y, 548, 600)) {
        mini_screen = MINISTATE_TUTORIAL;
      }
      // Options menu
      else if (collision(asw::input::mouse.position.x,
                         asw::input::mouse.position.x, 749, 800,
                         asw::input::mouse.position.y,
                         asw::input::mouse.position.y, 548, 600)) {
        mini_screen = MINISTATE_OPTIONS;
      }
    }
  }
  // Exit menus
  else if (mini_screen == MINISTATE_TUTORIAL ||
           mini_screen == MINISTATE_CREDITS ||
           mini_screen == MINISTATE_CONTROLS ||
           mini_screen == MINISTATE_SCORES) {
    if (asw::input::keyboard.anyPressed ||
        asw::input::getMouseButtonDown(asw::input::MouseButton::Left) ||
        asw::input::controller[0].anyPressed) {
      mini_screen = MINISTATE_MENU;
      draw();
    }
  }
  // Options
  else if (mini_screen == MINISTATE_OPTIONS &&
           asw::input::getMouseButtonDown(asw::input::MouseButton::Left)) {
    // Particles toggle
    if (collision(280, 360, asw::input::mouse.position.x,
                  asw::input::mouse.position.x, 400, 480,
                  asw::input::mouse.position.y, asw::input::mouse.position.y)) {
      settings[SETTING_PARTICLE_TYPE] =
          (settings[SETTING_PARTICLE_TYPE] + 1) % 4;
    }
    // Sound button toggle
    else if (collision(120, 200, asw::input::mouse.position.x,
                       asw::input::mouse.position.x, 180, 260,
                       asw::input::mouse.position.y,
                       asw::input::mouse.position.y)) {
      settings[SETTING_SOUND] = (settings[SETTING_SOUND] + 1) % 2;
    }
    // Music button toggle
    else if (collision(280, 360, asw::input::mouse.position.x,
                       asw::input::mouse.position.x, 180, 260,
                       asw::input::mouse.position.y,
                       asw::input::mouse.position.y)) {
      settings[SETTING_MUSIC] = (settings[SETTING_MUSIC] + 1) % 2;

      if (settings[SETTING_MUSIC] == 0) {
        asw::sound::stopMusic();
      } else {
        asw::sound::playMusic(music_mainmenu);
      }

    }
    // Fullscreen toggle
    else if (collision(120, 200, asw::input::mouse.position.x,
                       asw::input::mouse.position.x, 400, 480,
                       asw::input::mouse.position.y,
                       asw::input::mouse.position.y)) {
      settings[SETTING_FULLSCREEN] = (settings[SETTING_FULLSCREEN] + 1) % 2;

      if (settings[SETTING_FULLSCREEN]) {
        asw::display::setFullscreen(true);
      } else {
        asw::display::setFullscreen(false);
      }
    }
    // Screen shake
    else if (collision(280, 360, asw::input::mouse.position.x,
                       asw::input::mouse.position.x, 290, 370,
                       asw::input::mouse.position.y,
                       asw::input::mouse.position.y)) {
      settings[SETTING_SCREENSHAKE] = (settings[SETTING_SCREENSHAKE] + 1) % 4;
    }
    // Control Toggle
    else if (collision(120, 200, asw::input::mouse.position.x,
                       asw::input::mouse.position.x, 290, 370,
                       asw::input::mouse.position.y,
                       asw::input::mouse.position.y)) {
      settings[SETTING_CONTROLMODE] = ((settings[SETTING_CONTROLMODE] + 1) % 3);
    }
    // Power off
    else if (collision(540, 620, asw::input::mouse.position.x,
                       asw::input::mouse.position.x, 180, 260,
                       asw::input::mouse.position.y,
                       asw::input::mouse.position.y)) {
      write_settings();
      asw::core::exit = true;
    }
    // Exit menu
    else if (collision(540, 620, asw::input::mouse.position.x,
                       asw::input::mouse.position.x, 407, 487,
                       asw::input::mouse.position.y,
                       asw::input::mouse.position.y)) {
      mini_screen = MINISTATE_MENU;
      write_settings();
    }
  }

  // Update mouse particles
  if (settings[SETTING_PARTICLE_TYPE] != 3 && mouse_rocket_up) {
    for (int i = 0; i < 500; i++) {
      if (asw::random::between(1, 10) == 1) {
        auto part_color = asw::Color(255, asw::random::between(0, 255), 0);

        if (settings[SETTING_CHRISTMAS]) {
          int red_or_green = asw::random::between(0, 1) * 255;
          part_color       = asw::Color(red_or_green, 255 - red_or_green, 0);
        }

        Particle newParticle(
            asw::input::mouse.position.x, asw::input::mouse.position.y + 16,
            part_color, asw::random::between(-2, 2),
            asw::random::between(8, 20), 1, settings[SETTING_PARTICLE_TYPE]);
        mousePart.push_back(newParticle);
      }
    }
  }

  for (auto& p : mousePart) {
    p.update(deltaTime);
  }

  auto [first, last] = std::ranges::remove_if(mousePart, [](const auto&) {
    return asw::random::between(0, 10) == 0;
  });
  mousePart.erase(first, last);

  // Close game
  if (asw::input::getKeyDown(asw::input::Key::Escape)) {
    asw::core::exit = true;
  }

  // Check if mouse is going up
  mouse_rocket_up = (asw::input::mouse.position.y < mouseMove);
  mouseMove       = asw::input::mouse.position.y;
}

// Draw to screen
void MenuScene::draw() {
  // Menu Background
  asw::draw::sprite(img_menu, asw::Vec2<float>(0, 0));

  // Start button
  asw::draw::sprite(start,
                    asw::Vec2<float>((animation_pos * 3.2) - (start->w), 400));

  // Highscores button
  asw::draw::sprite(highscores_button,
                    asw::Vec2<float>(SCREEN_W - (animation_pos * 1.4), 30));

  // Joystick Mode
  if (settings[SETTING_CONTROLMODE] != 1 && joystick_enabled) {
    asw::draw::sprite(
        xbox_start,
        asw::Vec2<float>((animation_pos * 3.2) - (start->w) + 220, 430));
  }

  // Nice title image
  asw::draw::sprite(title,
                    asw::Vec2<float>(20, (animation_pos * 1.2) - (title->h)));

  // Bottom Right Buttons
  asw::draw::sprite(
      ui_credits, asw::Vec2<float>(
                      541, SCREEN_H - (animation_pos * (ui_credits->h)) / 100));
  asw::draw::sprite(
      ui_controls,
      asw::Vec2<float>(645,
                       SCREEN_H - (animation_pos * (ui_controls->h)) / 100));
  asw::draw::sprite(
      ui_help,
      asw::Vec2<float>(697, SCREEN_H - (animation_pos * (ui_help->h)) / 100));
  asw::draw::sprite(
      ui_options, asw::Vec2<float>(
                      749, SCREEN_H - (animation_pos * (ui_options->h)) / 100));

  // Draw scores
  if (mini_screen == MINISTATE_SCORES) {
    // Highscore background
    asw::draw::sprite(highscores_table, asw::Vec2<float>(200, 50));

    // Title
    asw::draw::textCenter(orbitron_36, "Highscores", asw::Vec2<float>(400, 75),
                          asw::Color(0, 0, 0));

    // Read the top 10 scores
    for (int i = 0; i < 10; i++) {
      asw::draw::text(orbitron_24, std::to_string(highscores.getScore(i)),
                      asw::Vec2<float>(225, (i * 40) + 130),
                      asw::Color(0, 0, 0));
      asw::draw::textRight(orbitron_18, highscores.getName(i),
                           asw::Vec2<float>(575, (i * 40) + 132),
                           asw::Color(0, 0, 0));
    }
  }
  // Tutorial screen
  else if (mini_screen == MINISTATE_TUTORIAL) {
    asw::draw::sprite(helpScreen, asw::Vec2<float>(0, 0));
  }
  // Credits screen
  else if (mini_screen == MINISTATE_CREDITS) {
    asw::draw::sprite(credits, asw::Vec2<float>(0, 0));
  }
  // Credits screen
  else if (mini_screen == MINISTATE_CONTROLS) {
    asw::draw::sprite(controls, asw::Vec2<float>(0, 0));
  }
  // Option Menu drawing(page and ingame)
  else if (mini_screen == MINISTATE_OPTIONS) {
    // Background
    asw::draw::sprite(options, asw::Vec2<float>(0, 0));

    // Buttons
    asw::draw::sprite(ui_particle[settings[SETTING_PARTICLE_TYPE]],
                      asw::Vec2<float>(280, 407));
    asw::draw::sprite(ui_sound[settings[SETTING_SOUND]],
                      asw::Vec2<float>(120, 180));
    asw::draw::sprite(ui_music[settings[SETTING_MUSIC]],
                      asw::Vec2<float>(280, 180));
    asw::draw::sprite(ui_window[settings[SETTING_FULLSCREEN]],
                      asw::Vec2<float>(120, 407));
    asw::draw::sprite(ui_screenshake[settings[SETTING_SCREENSHAKE]],
                      asw::Vec2<float>(280, 295));
    asw::draw::sprite(ui_control[settings[SETTING_CONTROLMODE]],
                      asw::Vec2<float>(120, 295));

    // Button Text
    asw::draw::text(orbitron_24,
                    "Sounds         Music                            Exit",
                    asw::Vec2<float>(110, 154), asw::Color(255, 250, 250));
    asw::draw::text(orbitron_24, "Input      Screen Shake",
                    asw::Vec2<float>(126, 268), asw::Color(255, 250, 250));
    asw::draw::text(orbitron_24,
                    "Window       Particles                        Back",
                    asw::Vec2<float>(108, 382), asw::Color(255, 250, 250));

    // Exit and back
    asw::draw::sprite(ui_exit, asw::Vec2<float>(540, 180));
    asw::draw::sprite(ui_back, asw::Vec2<float>(540, 407));
  }

  // Debug
  if (settings[SETTING_DEBUG]) {
    // Joystick testing
    if (joystick_enabled) {
      for (auto i = 0; i < asw::input::controller[0].down.size(); i++) {
        asw::draw::text(orbitron_12,
                        std::format("Joystick {}: {}", i,
                                    asw::input::controller[0].down[i]),
                        asw::Vec2<float>(120, 25 + (20 * i)),
                        asw::Color(255, 255, 255));
      }
    }

    // FPS
    asw::draw::text(orbitron_12, std::format("FPS:{}", fps),
                    asw::Vec2<float>(SCREEN_W - 100, 20),
                    asw::Color(255, 255, 255));
  }

  // Draw rocket if no particles
  if (settings[SETTING_PARTICLE_TYPE] == 3 && mouse_rocket_up) {
    asw::draw::sprite(mouse_rocket,
                      asw::Vec2<float>(asw::input::mouse.position.x - 10,
                                       asw::input::mouse.position.y));
  }

  // Draw mouse particles
  for (unsigned int i = 0; i < mousePart.size(); i++) {
    mousePart.at(i).draw();
  }
}
