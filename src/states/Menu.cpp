#include "Menu.h"

#include "../constants/globals.h"
#include "../constants/settings.h"
#include "../engine/Input/JoystickListener.h"
#include "../engine/Input/KeyListener.h"
#include "../engine/Input/MouseListener.h"

// Construct state
menu::menu() {
  // Init vars
  startMove = false;
  startClicked = false;
  mouse_rocket_up = false;
  mouseMove = MouseListener::mouse_y;

  // Screen on
  mini_screen = MINISTATE_MENU;

  // Buffer
  buffer = al_create_bitmap(SCREEN_W, SCREEN_H);

  // Load intro image
  // Random menu
  img_menu = load_bitmap_ex("images/backgrounds/background_" +
                            std::to_string(random(0, 3)) + ".png");
  start = load_bitmap_ex("images/gui/start.png");
  highscores_button = load_bitmap_ex("images/gui/highscores.png");
  mouse = load_bitmap_ex("images/gui/mouse.png");
  mouse_rocket = load_bitmap_ex("images/gui/mouse_rocket.png");
  title = load_bitmap_ex("images/gui/title.png");
  options = load_bitmap_ex("images/gui/options.png");

  ui_sound[1] = load_bitmap_ex("images/gui/ui_sound_on.png");
  ui_sound[0] = load_bitmap_ex("images/gui/ui_sound_off.png");

  ui_music[1] = load_bitmap_ex("images/gui/ui_music_on.png");
  ui_music[0] = load_bitmap_ex("images/gui/ui_music_off.png");

  ui_window[1] = load_bitmap_ex("images/gui/ui_window_windowed.png");
  ui_window[0] = load_bitmap_ex("images/gui/ui_window_fullscreen.png");

  ui_particle[0] = load_bitmap_ex("images/gui/ui_particle_pixel.png");
  ui_particle[1] = load_bitmap_ex("images/gui/ui_particle_square.png");
  ui_particle[2] = load_bitmap_ex("images/gui/ui_particle_circle.png");
  ui_particle[3] = load_bitmap_ex("images/gui/ui_particle_off.png");

  ui_control[0] = load_bitmap_ex("images/gui/ui_control_xbox.png");
  ui_control[1] = load_bitmap_ex("images/gui/ui_control_keyboard.png");
  ui_control[2] = load_bitmap_ex("images/gui/ui_control_auto.png");

  ui_screenshake[0] = load_bitmap_ex("images/gui/ui_screenshake_none.png");
  ui_screenshake[1] = load_bitmap_ex("images/gui/ui_screenshake_low.png");
  ui_screenshake[2] = load_bitmap_ex("images/gui/ui_screenshake_medium.png");
  ui_screenshake[3] = load_bitmap_ex("images/gui/ui_screenshake_high.png");

  ui_options = load_bitmap_ex("images/gui/ui_options.png");
  ui_options_small = load_bitmap_ex("images/gui/ui_options_small.png");
  ui_back = load_bitmap_ex("images/gui/ui_back.png");
  credits = load_bitmap_ex("images/gui/credits.png");
  ui_credits = load_bitmap_ex("images/gui/ui_credits.png");
  highscores_table = load_bitmap_ex("images/gui/highscores_table.png");
  ui_help = load_bitmap_ex("images/gui/ui_help.png");
  helpScreen = load_bitmap_ex("images/gui/helpScreen.png");
  ui_exit = load_bitmap_ex("images/gui/ui_exit.png");
  xbox_start = load_bitmap_ex("images/gui/xbox_start.png");
  ui_screenshot_notification =
      load_bitmap_ex("images/gui/ui_screenshot_notification.png");
  ui_controls = load_bitmap_ex("images/gui/ui_controls.png");
  controls = load_bitmap_ex("images/gui/controls.png");

  // Load that menu music
  music_mainmenu = load_sample_ex("audio/music_mainmenu.ogg");

  // Init animation vars
  animation_pos = 0;

  // Hide mouse
  // al_hide_mouse_cursor(display);

  // Play music
  if (settings.get<bool>("music", true) == 1) {
    al_play_sample(music_mainmenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP,
                   &currentMusic);
  }
}

// Destructor
menu::~menu() {
  // Stops music
  al_stop_sample(&currentMusic);

  // Destroy samples
  al_destroy_sample(music_mainmenu);

  // Destroy images
  al_destroy_bitmap(buffer);
  al_destroy_bitmap(img_menu);
  al_destroy_bitmap(options);
  al_destroy_bitmap(helpScreen);
  al_destroy_bitmap(controls);
  al_destroy_bitmap(credits);
  al_destroy_bitmap(highscores_table);
  al_destroy_bitmap(start);
  al_destroy_bitmap(title);
  al_destroy_bitmap(highscores_button);
  al_destroy_bitmap(mouse);
  al_destroy_bitmap(mouse_rocket);
  al_destroy_bitmap(xbox_start);
  al_destroy_bitmap(ui_sound[0]);
  al_destroy_bitmap(ui_sound[1]);
  al_destroy_bitmap(ui_music[0]);
  al_destroy_bitmap(ui_music[1]);
  al_destroy_bitmap(ui_screenshake[0]);
  al_destroy_bitmap(ui_screenshake[1]);
  al_destroy_bitmap(ui_screenshake[2]);
  al_destroy_bitmap(ui_screenshake[3]);
  al_destroy_bitmap(ui_window[0]);
  al_destroy_bitmap(ui_window[1]);
  al_destroy_bitmap(ui_particle[0]);
  al_destroy_bitmap(ui_particle[1]);
  al_destroy_bitmap(ui_particle[2]);
  al_destroy_bitmap(ui_particle[3]);
  al_destroy_bitmap(ui_control[0]);
  al_destroy_bitmap(ui_control[1]);
  al_destroy_bitmap(ui_control[2]);
  al_destroy_bitmap(ui_options);
  al_destroy_bitmap(ui_options_small);
  al_destroy_bitmap(ui_back);
  al_destroy_bitmap(ui_credits);
  al_destroy_bitmap(ui_exit);
  al_destroy_bitmap(ui_help);
  al_destroy_bitmap(ui_screenshot_notification);
  al_destroy_bitmap(ui_controls);
}

// Update loop
void menu::update() {
  // Menu animations
  if (animation_pos < 100 && !startClicked) {
    animation_pos += 4;
  }

  if (animation_pos > 0 && startClicked) {
    animation_pos -= 4;
  }

  // Start the game
  if (startClicked && animation_pos <= 0) {
    set_next_state(STATE_GAME);
  }

  // Open submenu or start game
  if (mini_screen == MINISTATE_MENU) {
    // Start game with controller
    if (JoystickListener::buttonPressed[JOY_XBOX_START] ||
        JoystickListener::buttonPressed[JOY_XBOX_A]) {
      startClicked = true;
    }

    // Buttons
    if (MouseListener::mouse_pressed & 1) {
      // Start game
      if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 40,
                    40 + al_get_bitmap_width(start), MouseListener::mouse_y,
                    MouseListener::mouse_y, 410,
                    410 + al_get_bitmap_height(start))) {
        startClicked = true;
      }
      // Scores
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 660,
                         660 + al_get_bitmap_width(highscores_button),
                         MouseListener::mouse_y, MouseListener::mouse_y, 30,
                         30 + al_get_bitmap_height(highscores_button))) {
        mini_screen = MINISTATE_SCORES;
      }
      // Credits menu
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 542,
                         644, MouseListener::mouse_y, MouseListener::mouse_y,
                         548, 600)) {
        mini_screen = MINISTATE_CREDITS;
      }
      // Controls menu
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 644,
                         696, MouseListener::mouse_y, MouseListener::mouse_y,
                         548, 600)) {
        mini_screen = MINISTATE_CONTROLS;
      }
      // Help screen
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 696,
                         749, MouseListener::mouse_y, MouseListener::mouse_y,
                         548, 600)) {
        mini_screen = MINISTATE_TUTORIAL;
      }
      // Options menu
      else if (collision(MouseListener::mouse_x, MouseListener::mouse_x, 749,
                         800, MouseListener::mouse_y, MouseListener::mouse_y,
                         548, 600)) {
        mini_screen = MINISTATE_OPTIONS;
      }
    }
  }
  // Exit menus
  else if (mini_screen == MINISTATE_TUTORIAL ||
           mini_screen == MINISTATE_CREDITS ||
           mini_screen == MINISTATE_CONTROLS ||
           mini_screen == MINISTATE_SCORES) {
    if (KeyListener::lastKeyPressed != -1 || MouseListener::mouse_pressed & 1 ||
        JoystickListener::lastButtonPressed != -1) {
      mini_screen = MINISTATE_MENU;
      draw();
    }
  }
  // Options
  else if (mini_screen == MINISTATE_OPTIONS &&
           MouseListener::mouse_pressed & 1) {
    // Particles toggle
    if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x, 400,
                  480, MouseListener::mouse_y, MouseListener::mouse_y)) {
      settings.set("particleType",
                   (settings.get<int>("particleType", 0) + 1) % 4);
    }
    // Sound button toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      settings.set("sound", !settings.get<bool>("sound", true));
    }
    // Music button toggle
    else if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      settings.set("music", !settings.get<bool>("music", true));

      if (settings.get<bool>("music", true) == 0)
        al_stop_sample(&currentMusic);
      else
        al_play_sample(music_mainmenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,
                       &currentMusic);

    }
    // Fullscreen toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       400, 480, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      settings.set("fullscreen",
                   (settings.get<bool>("fullscreen", false) + 1) % 2);

      if (settings.get<bool>("fullscreen", false)) {
        // Fullscreen stuff
        // al_destroy_display(display);
        // al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
        // display = al_create_display(SCREEN_W, SCREEN_H);

        // ALLEGRO_DISPLAY_MODE disp_data;
        // al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
        // float sx = disp_data.width / (float)SCREEN_W;
        // float sy = disp_data.height / (float)SCREEN_H;

        // ALLEGRO_TRANSFORM trans;
        // al_identity_transform(&trans);
        // al_scale_transform(&trans, sx, sy);
        // al_use_transform(&trans);
        // al_hide_mouse_cursor(display);
      } else {
        // al_destroy_display(display);
        // al_set_new_display_flags(ALLEGRO_WINDOWED);
        // display = al_create_display(SCREEN_W, SCREEN_H);
        // al_hide_mouse_cursor(display);
      }
    }
    // Screen shake
    else if (collision(280, 360, MouseListener::mouse_x, MouseListener::mouse_x,
                       290, 370, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      settings.set("screenshake",
                   (settings.get<int>("screenshake", 0) + 1) % 4);
    }
    // Control Toggle
    else if (collision(120, 200, MouseListener::mouse_x, MouseListener::mouse_x,
                       290, 370, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      settings.set("controlMode",
                   (settings.get<int>("controlMode", 0) + 1) % 3);
    }
    // Power off
    else if (collision(540, 620, MouseListener::mouse_x, MouseListener::mouse_x,
                       180, 260, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      // write_settings();
      set_next_state(STATE_EXIT);
    }
    // Exit menu
    else if (collision(540, 620, MouseListener::mouse_x, MouseListener::mouse_x,
                       407, 487, MouseListener::mouse_y,
                       MouseListener::mouse_y)) {
      mini_screen = MINISTATE_MENU;
      // write_settings();
    }
  }

  // Update mouse particles
  if (settings.get<int>("particleType", 0) != 3 && mouse_rocket_up) {
    for (int i = 0; i < 500; i++) {
      if (random(1, 10) == 1) {
        ALLEGRO_COLOR part_color = al_map_rgb(255, random(0, 255), 0);

        if (settings.get<bool>("christmas", false)) {
          int red_or_green = random(0, 1) * 255;
          part_color = al_map_rgb(red_or_green, 255 - red_or_green, 0);
        }

        Particle newParticle(MouseListener::mouse_x,
                             MouseListener::mouse_y + 16, part_color,
                             random(-2, 2), random(8, 20), 1,
                             settings.get<int>("particleType", 0));
        mousePart.push_back(newParticle);
      }
    }
  }

  for (unsigned int i = 0; i < mousePart.size(); i++) {
    mousePart.at(i).update();

    if (random(0, 10) == 0)
      mousePart.erase(mousePart.begin() + i);
  }

  // Close game
  if (KeyListener::key[ALLEGRO_KEY_ESCAPE])
    set_next_state(STATE_EXIT);

  // Check if mouse is going up
  mouse_rocket_up = (MouseListener::mouse_y < mouseMove);
  mouseMove = MouseListener::mouse_y;
}

// Draw to screen
void menu::draw() {
  // Menu Background
  al_draw_bitmap(img_menu, 0, 0, 0);

  // Start button
  al_draw_bitmap(start, (animation_pos * 3.2) - al_get_bitmap_width(start), 400,
                 0);

  // Highscores button
  al_draw_bitmap(highscores_button, SCREEN_W - (animation_pos * 1.4), 30, 0);

  // Joystick Mode
  if (settings.get<int>("controlMode", 0) != 1 && joystick_enabled) {
    al_draw_bitmap(xbox_start,
                   (animation_pos * 3.2) - al_get_bitmap_width(start) + 220,
                   430, 0);
  }

  // Nice title image
  al_draw_bitmap(title, 20, (animation_pos * 1.2) - al_get_bitmap_height(title),
                 0);

  // Bottom Right Buttons
  al_draw_bitmap(
      ui_credits, 541,
      SCREEN_H - (animation_pos * al_get_bitmap_height(ui_credits)) / 100, 0);
  al_draw_bitmap(
      ui_controls, 645,
      SCREEN_H - (animation_pos * al_get_bitmap_height(ui_controls)) / 100, 0);
  al_draw_bitmap(
      ui_help, 697,
      SCREEN_H - (animation_pos * al_get_bitmap_height(ui_help)) / 100, 0);
  al_draw_bitmap(
      ui_options, 749,
      SCREEN_H - (animation_pos * al_get_bitmap_height(ui_options)) / 100, 0);

  // Draw scores
  if (mini_screen == MINISTATE_SCORES) {
    // Highscore background
    al_draw_bitmap(highscores_table, 200, 50, 0);

    // Title
    al_draw_text(orbitron_36, al_map_rgb(0, 0, 0), 400, 75,
                 ALLEGRO_ALIGN_CENTRE, "Highscores");

    // Read the top 10 scores
    for (int i = 0; i < 10; i++) {
      al_draw_text(orbitron_24, al_map_rgb(0, 0, 0), 225, (i * 40) + 130,
                   ALLEGRO_ALIGN_LEFT,
                   std::to_string(highscores.getScore(i)).c_str());
      al_draw_text(orbitron_18, al_map_rgb(0, 0, 0), 575, (i * 40) + 132,
                   ALLEGRO_ALIGN_RIGHT, highscores.getName(i).c_str());
    }
  }
  // Tutorial screen
  else if (mini_screen == MINISTATE_TUTORIAL) {
    al_draw_bitmap(helpScreen, 0, 0, 0);
  }
  // Credits screen
  else if (mini_screen == MINISTATE_CREDITS) {
    al_draw_bitmap(credits, 0, 0, 0);
  }
  // Credits screen
  else if (mini_screen == MINISTATE_CONTROLS) {
    al_draw_bitmap(controls, 0, 0, 0);
  }
  // Option Menu drawing(page and ingame)
  else if (mini_screen == MINISTATE_OPTIONS) {
    // Background
    al_draw_bitmap(options, 0, 0, 0);

    // Buttons
    al_draw_bitmap(ui_particle[settings.get<int>("particleType", 0)], 280, 407,
                   0);
    al_draw_bitmap(ui_sound[settings.get<bool>("sound", true)], 120, 180, 0);
    al_draw_bitmap(ui_music[settings.get<bool>("music", true)], 280, 180, 0);
    al_draw_bitmap(ui_window[settings.get<bool>("fullscreen", false)], 120, 407,
                   0);
    al_draw_bitmap(ui_screenshake[settings.get<int>("screenshake", 0)], 280,
                   295, 0);
    al_draw_bitmap(ui_control[settings.get<int>("controlMode", 0)], 120, 295,
                   0);

    // Button Text
    al_draw_text(orbitron_24, al_map_rgb(255, 250, 250), 110, 154,
                 ALLEGRO_ALIGN_LEFT,
                 "Sounds         Music                            Exit");
    al_draw_text(orbitron_24, al_map_rgb(255, 250, 250), 126, 268,
                 ALLEGRO_ALIGN_LEFT, "Input      Screen Shake");
    al_draw_text(orbitron_24, al_map_rgb(255, 250, 250), 108, 382,
                 ALLEGRO_ALIGN_LEFT,
                 "Window       Particles                        Back");

    // Exit and back
    al_draw_bitmap(ui_exit, 540, 180, 0);
    al_draw_bitmap(ui_back, 540, 407, 0);
  }

  // Debug
  if (settings.get<bool>("debug", false)) {
    // Joystick testing
    if (joystick_enabled) {
      for (int i = 0; i < JoystickListener::JOY_MAX_BUTTONS; i++) {
        al_draw_textf(orbitron_12, al_map_rgb(255, 255, 255), 20, 10 * i + 20,
                      ALLEGRO_ALIGN_LEFT, "Joystick B %i : %i", i,
                      JoystickListener::button[i]);
      }
    }

    // FPS
    al_draw_textf(orbitron_12, al_map_rgb(255, 255, 255), SCREEN_W - 100, 20,
                  ALLEGRO_ALIGN_LEFT, "FPS:%i", fps);
  }

  // Draw rocket if no particles
  if (settings.get<int>("particleType", 0) == 3 && mouse_rocket_up) {
    al_draw_bitmap(mouse_rocket, MouseListener::mouse_x - 10,
                   MouseListener::mouse_y, 0);
  }

  // Draw mouse particles
  for (unsigned int i = 0; i < mousePart.size(); i++) {
    mousePart.at(i).draw();
  }

  al_draw_bitmap(mouse, MouseListener::mouse_x - 10, MouseListener::mouse_y, 0);
}
