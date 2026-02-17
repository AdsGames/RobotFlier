#include "Menu.h"

#include <fstream>

// Construct state
void MenuScene::init() {
  using namespace asw::assets;
  using namespace asw::random;

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
      std::format("assets/images/backgrounds/background_{}.png", between(0, 3));
  img_menu.setTexture(loadTexture(background));

  start.setTexture(loadTexture("assets/images/gui/start.png"));
  start.transform.position.y = 400;

  highscores_button.setTexture(loadTexture("assets/images/gui/highscores.png"));
  highscores_button.transform.position.y = 30;

  title.setTexture(loadTexture("assets/images/gui/title.png"));
  title.transform.position.x = 20;

  options.setTexture(loadTexture("assets/images/gui/options.png"));

  ui_sound[1].setTexture(loadTexture("assets/images/gui/ui_sound_on.png"));
  ui_sound[0].setTexture(loadTexture("assets/images/gui/ui_sound_off.png"));

  ui_sound[0].transform.position = asw::Vec2<float>(120, 180);
  ui_sound[1].transform.position = asw::Vec2<float>(120, 180);

  ui_music[1].setTexture(loadTexture("assets/images/gui/ui_music_on.png"));
  ui_music[0].setTexture(loadTexture("assets/images/gui/ui_music_off.png"));

  ui_music[0].transform.position = asw::Vec2<float>(280, 180);
  ui_music[1].transform.position = asw::Vec2<float>(280, 180);

  ui_window[1].setTexture(
      loadTexture("assets/images/gui/ui_window_windowed.png"));
  ui_window[0].setTexture(
      loadTexture("assets/images/gui/ui_window_fullscreen.png"));

  ui_window[0].transform.position = asw::Vec2<float>(120, 407);
  ui_window[1].transform.position = asw::Vec2<float>(120, 407);

  ui_particle[0].setTexture(
      loadTexture("assets/images/gui/ui_particle_circle.png"));
  ui_particle[1].setTexture(
      loadTexture("assets/images/gui/ui_particle_square.png"));
  ui_particle[2].setTexture(
      loadTexture("assets/images/gui/ui_particle_pixel.png"));
  ui_particle[3].setTexture(
      loadTexture("assets/images/gui/ui_particle_off.png"));

  ui_particle[0].transform.position = asw::Vec2<float>(280, 407);
  ui_particle[1].transform.position = asw::Vec2<float>(280, 407);
  ui_particle[2].transform.position = asw::Vec2<float>(280, 407);
  ui_particle[3].transform.position = asw::Vec2<float>(280, 407);

  ui_control[0].setTexture(
      loadTexture("assets/images/gui/ui_control_xbox.png"));
  ui_control[1].setTexture(
      loadTexture("assets/images/gui/ui_control_keyboard.png"));
  ui_control[2].setTexture(
      loadTexture("assets/images/gui/ui_control_auto.png"));

  ui_control[0].transform.position = asw::Vec2<float>(120, 295);
  ui_control[1].transform.position = asw::Vec2<float>(120, 295);
  ui_control[2].transform.position = asw::Vec2<float>(120, 295);

  ui_screenshake[0].setTexture(
      loadTexture("assets/images/gui/ui_screenshake_none.png"));
  ui_screenshake[1].setTexture(
      loadTexture("assets/images/gui/ui_screenshake_low.png"));
  ui_screenshake[2].setTexture(
      loadTexture("assets/images/gui/ui_screenshake_medium.png"));
  ui_screenshake[3].setTexture(
      loadTexture("assets/images/gui/ui_screenshake_high.png"));

  ui_screenshake[0].transform.position = asw::Vec2<float>(280, 295);
  ui_screenshake[1].transform.position = asw::Vec2<float>(280, 295);
  ui_screenshake[2].transform.position = asw::Vec2<float>(280, 295);
  ui_screenshake[3].transform.position = asw::Vec2<float>(280, 295);

  ui_back.setTexture(loadTexture("assets/images/gui/ui_back.png"));
  ui_back.transform.position = asw::Vec2<float>(540, 407);

  credits.setTexture(loadTexture("assets/images/gui/credits.png"));

  highscores_table.setTexture(
      loadTexture("assets/images/gui/highscores_table.png"));
  highscores_table.transform.position = asw::Vec2<float>(200, 50);

  ui_help.setTexture(loadTexture("assets/images/gui/ui_help.png"));
  ui_help.transform.position.x = 697;

  ui_controls.setTexture(loadTexture("assets/images/gui/ui_controls.png"));
  ui_controls.transform.position.x = 645;

  ui_credits.setTexture(loadTexture("assets/images/gui/ui_credits.png"));
  ui_credits.transform.position.x = 541;

  ui_options.setTexture(loadTexture("assets/images/gui/ui_options.png"));
  ui_options.transform.position.x = 749;

  helpScreen.setTexture(loadTexture("assets/images/gui/helpScreen.png"));

  ui_exit.setTexture(loadTexture("assets/images/gui/ui_exit.png"));
  ui_exit.transform.position = asw::Vec2<float>(540, 180);

  xbox_start.setTexture(loadTexture("assets/images/gui/xbox_start.png"));
  xbox_start.transform.position.y = 430;

  controls.setTexture(loadTexture("assets/images/gui/controls.png"));

  // Load that menu music
  music_mainmenu = loadMusic("assets/audio/music_mainmenu.ogg");

  // Read settings from file
  read_settings();

  // Load scores
  highscores = ScoreTable("scores.dat");

  // Play music
  asw::sound::playMusic(music_mainmenu);
}

// Writes the settings to file
void MenuScene::write_settings() {
  std::ofstream settings_file("assets/data/settings.dat");

  for (int i = 0; i < 7; i++) {
    settings_file << settings[i] << " ";
  }

  settings_file.close();

  // Read settings to apply changes
  read_settings();
}

// Reads the data from file
void MenuScene::read_settings() {
  std::ifstream read("assets/data/settings.dat");

  if (!read.is_open()) {
    // Set defaults
    settings[SETTING_SOUND]         = 1;
    settings[SETTING_MUSIC]         = 1;
    settings[SETTING_FULLSCREEN]    = 0;
    settings[SETTING_SCREENSHAKE]   = 2;
    settings[SETTING_PARTICLE_TYPE] = 0;
    settings[SETTING_CONTROLMODE]   = 0;

    write_settings();
    return;
  }

  for (int i = 0; i < 7; i++) {
    read >> settings[i];
  }

  read.close();

  if (settings[SETTING_SOUND] == 0) {
    asw::sound::setSfxVolume(0);
  } else if (settings[SETTING_SOUND] == 1) {
    asw::sound::setSfxVolume(1);
  }

  if (settings[SETTING_MUSIC] == 0) {
    asw::sound::setMusicVolume(0);
    asw::sound::stopMusic();
  } else if (settings[SETTING_MUSIC] == 1) {
    asw::sound::setMusicVolume(1);
    if (!asw::sound::isMusicPlaying()) {
      asw::sound::playMusic(music_mainmenu);
    }
  }

  if (settings[SETTING_FULLSCREEN]) {
    asw::display::setFullscreen(true);
  } else {
    asw::display::setFullscreen(false);
  }
}

// Update loop
void MenuScene::update(float deltaTime) {
  using namespace asw::easing;

  animation_ticker += startClicked ? -deltaTime : deltaTime;
  auto t = std::clamp(animation_ticker / ANIMATION_DURATION, 0.0F, 1.0F);
  auto ease_func = startClicked ? easeInExpo : easeOutElastic;

  // Animation
  title.transform.position.y       = ease(-100.0F, 20.0F, t, ease_func);
  ui_credits.transform.position.y  = ease(S_H_F, S_H_F - 52.0F, t, ease_func);
  ui_controls.transform.position.y = ease(S_H_F, S_H_F - 52.0F, t, ease_func);
  ui_help.transform.position.y     = ease(S_H_F, S_H_F - 52.0F, t, ease_func);
  ui_options.transform.position.y  = ease(S_H_F, S_H_F - 52.0F, t, ease_func);
  start.transform.position.x       = ease(-400.0F, 40.0F, t, ease_func);
  xbox_start.transform.position.x  = ease(-400.0F, 40.0F, t, ease_func);
  highscores_button.transform.position.x =
      ease(S_W_F, S_W_F - 138.0F, t, ease_func);

  // Start the game
  if (startClicked && t <= 0.01F) {
    sceneManager.setNextScene(Scenes::Game);
  }

  // Open submenu or start game
  if (mini_screen == MINISTATE_MENU) {
    // Start game with controller
    if (asw::input::getControllerButtonDown(
            0, asw::input::ControllerButton::Start) ||
        asw::input::getControllerButtonDown(0,
                                            asw::input::ControllerButton::A)) {
      startClicked     = true;
      animation_ticker = ANIMATION_DURATION;
    }

    // Buttons
    if (asw::input::getMouseButtonDown(asw::input::MouseButton::Left)) {
      // Start game
      if (start.transform.contains(asw::input::mouse.position)) {
        startClicked     = true;
        animation_ticker = ANIMATION_DURATION;
      }
      // Scores
      else if (highscores_button.transform.contains(
                   asw::input::mouse.position)) {
        mini_screen = MINISTATE_SCORES;
      }
      // Credits menu
      else if (ui_credits.transform.contains(asw::input::mouse.position)) {
        mini_screen = MINISTATE_CREDITS;
      }
      // Controls menu
      else if (ui_controls.transform.contains(asw::input::mouse.position)) {
        mini_screen = MINISTATE_CONTROLS;
      }
      // Help screen
      else if (ui_help.transform.contains(asw::input::mouse.position)) {
        mini_screen = MINISTATE_TUTORIAL;
      }
      // Options menu
      else if (ui_options.transform.contains(asw::input::mouse.position)) {
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
    }
  }
  // Options
  else if (mini_screen == MINISTATE_OPTIONS &&
           asw::input::getMouseButtonDown(asw::input::MouseButton::Left)) {
    // Particles toggle
    if (ui_particle[0].transform.contains(asw::input::mouse.position)) {
      settings[SETTING_PARTICLE_TYPE] =
          (settings[SETTING_PARTICLE_TYPE] + 1) % 4;
      write_settings();
    }
    // Sound button toggle
    else if (ui_sound[0].transform.contains(asw::input::mouse.position)) {
      settings[SETTING_SOUND] = (settings[SETTING_SOUND] + 1) % 2;
      write_settings();
    }
    // Music button toggle
    else if (ui_music[0].transform.contains(asw::input::mouse.position)) {
      settings[SETTING_MUSIC] = (settings[SETTING_MUSIC] + 1) % 2;
      write_settings();
    }
    // Fullscreen toggle
    else if (ui_window[0].transform.contains(asw::input::mouse.position)) {
      settings[SETTING_FULLSCREEN] = (settings[SETTING_FULLSCREEN] + 1) % 2;
      write_settings();
    }
    // Screen shake
    else if (ui_screenshake[0].transform.contains(asw::input::mouse.position)) {
      settings[SETTING_SCREENSHAKE] = (settings[SETTING_SCREENSHAKE] + 1) % 4;
      write_settings();
    }
    // Control Toggle
    else if (ui_control[0].transform.contains(asw::input::mouse.position)) {
      settings[SETTING_CONTROLMODE] = ((settings[SETTING_CONTROLMODE] + 1) % 3);
      write_settings();
    }
    // Power off
    else if (ui_exit.transform.contains(asw::input::mouse.position)) {
      asw::core::exit = true;
    }
    // Exit menu
    else if (ui_back.transform.contains(asw::input::mouse.position)) {
      mini_screen = MINISTATE_MENU;
    }
  }

  // Update mouse particles
  if (settings[SETTING_PARTICLE_TYPE] != 3 && mouse_rocket_up) {
    for (int i = 0; i < 500; i++) {
      if (!asw::random::chance(10)) {
        continue;
      }

      auto part_color = asw::Color(255, asw::random::between(0, 255), 0);

      if (settings[SETTING_CHRISTMAS]) {
        int red_or_green = asw::random::between(0, 1) * 255;
        part_color       = asw::Color(red_or_green, 255 - red_or_green, 0);
      }

      mousePart.emplace_back(
          asw::input::mouse.position.x, asw::input::mouse.position.y + 16,
          part_color, asw::random::between(-2, 2), asw::random::between(8, 20),
          1, settings[SETTING_PARTICLE_TYPE]);
    }
  }

  for (auto& p : mousePart) {
    p.update(deltaTime);
  }

  std::erase_if(mousePart,
                [](const auto&) { return asw::random::between(0, 10) == 0; });

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
  img_menu.draw();

  // Start button
  start.draw();

  // Highscores button
  highscores_button.draw();

  // Joystick Mode
  if (settings[SETTING_CONTROLMODE] != 1 && joystick_enabled) {
    xbox_start.draw();
  }

  // Nice title image
  title.draw();

  // Bottom Right Buttons
  ui_credits.draw();
  ui_controls.draw();
  ui_help.draw();
  ui_options.draw();

  // Draw scores
  if (mini_screen == MINISTATE_SCORES) {
    // Highscore background
    highscores_table.draw();

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
    helpScreen.draw();
  }
  // Credits screen
  else if (mini_screen == MINISTATE_CREDITS) {
    credits.draw();
  }
  // Credits screen
  else if (mini_screen == MINISTATE_CONTROLS) {
    controls.draw();
  }
  // Option Menu drawing(page and ingame)
  else if (mini_screen == MINISTATE_OPTIONS) {
    // Background
    options.draw();

    // Buttons
    ui_particle[settings[SETTING_PARTICLE_TYPE]].draw();
    ui_sound[settings[SETTING_SOUND]].draw();
    ui_music[settings[SETTING_MUSIC]].draw();
    ui_window[settings[SETTING_FULLSCREEN]].draw();
    ui_screenshake[settings[SETTING_SCREENSHAKE]].draw();
    ui_control[settings[SETTING_CONTROLMODE]].draw();

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
    ui_exit.draw();
    ui_back.draw();
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

  // Draw mouse particles
  for (unsigned int i = 0; i < mousePart.size(); i++) {
    mousePart.at(i).draw();
  }
}
