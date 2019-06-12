#include "game.h"

// Constructor
game::game() {
  // From globals
  score = 0;
  screenshake = 0;

  // Game related
  scroll = 0;
  motion = 5;
  themeNumber = 0;
  screenshake_x = 0;
  screenshake_y = 0;
  arrow_animation = 0.0f;
  paused = false;

  // End game menu
  edittext = "Player";
  iter = edittext.end();

  // Reset stats
  for (int i = 0; i < 4; i++)
    stats[i] = 0;

  // Sounds
  sound_bomb = load_sample_ex ("audio/sound_bomb.wav");
  sound_orb = load_sample_ex ("audio/sound_orb.wav");
  sound_asteroid = load_sample_ex ("audio/sound_asteroid.wav");
  sound_magnet = load_sample_ex ("audio/sound_magnet.wav");
  sound_star = load_sample_ex ("audio/sound_star.wav");
  sound_snap = load_sample_ex ("audio/sound_snap.wav");

  // Music
  music_death = load_sample_ex ("audio/music_death.ogg");
  music_ingame = load_sample_ex ("audio/music_ingame.ogg");

  // Images
  // Gui
  pauseMenu = load_bitmap_ex ("images/gui/pauseMenu.png");
  ui_game_end = load_bitmap_ex ("images/gui/ui_game_end.png");
  ui_a = load_bitmap_ex ("images/gui/ui_a.png");
  ui_b = load_bitmap_ex ("images/gui/ui_b.png");
  ui_up = load_bitmap_ex ("images/gui/ui_up.png");
  debug = load_bitmap_ex ("images/gui/debug.png");

  // Background
  space = load_bitmap_ex ("images/backgrounds/space.png");

  // Nullfiy bitmaps not loaded yet
  screenshot = nullptr;
  asteroidImage = nullptr;
  parallaxBack = nullptr;
  groundOverlay = nullptr;
  groundUnderlay = nullptr;


  // Objects
  cometImage = load_bitmap_ex ("images/objects/comet.png");
  powerStar = load_bitmap_ex ("images/objects/powerStar.png");
  powerMagnet[0] = load_bitmap_ex ("images/objects/powerMagnet.png");
  powerMagnet[1] = load_bitmap_ex ("images/objects/powerMagnetTwo.png");
  powerMagnet[2] = load_bitmap_ex ("images/objects/powerMagnetThree.png");
  powerMagnet[3] = load_bitmap_ex ("images/objects/powerMagnetFour.png");

  if (settings[SETTING_CHRISTMAS]) {
    energyImage = load_bitmap_ex ("images/objects/energy_christmas.png");
    bombImage = load_bitmap_ex ("images/objects/bomb_christmas.png");
  }
  else {
    energyImage = load_bitmap_ex ("images/objects/energy.png");
    bombImage = load_bitmap_ex ("images/objects/bomb.png");
  }

  // Sets the level to 1
  changeTheme (0);

  // Mouse
  al_hide_mouse_cursor (display);

  // Init hectar
  hectar = robot (80, 300);
  hectar.load_resources();

  // Play music
  if (settings[SETTING_MUSIC] == 1)
    al_play_sample (music_ingame, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &currentMusic);
}

// Destructor
game::~game() {
  // Clear objects
  energys.clear();
  debries.clear();
  powerups.clear();

  // Destroy samples
  al_destroy_sample (sound_orb);
  al_destroy_sample (sound_bomb);
  al_destroy_sample (sound_asteroid);
  al_destroy_sample (sound_magnet);
  al_destroy_sample (sound_star);
  al_destroy_sample (sound_snap);

  // Destroy bitmaps
  //destroy_bitmap( buffer);
  al_destroy_bitmap (screenshot);
  al_destroy_bitmap (space);
  al_destroy_bitmap (parallaxBack);
  al_destroy_bitmap (groundOverlay);
  al_destroy_bitmap (groundUnderlay);
  al_destroy_bitmap (debug);
  al_destroy_bitmap (pauseMenu);
  al_destroy_bitmap (ui_game_end);
  al_destroy_bitmap (ui_a);
  al_destroy_bitmap (ui_b);
  al_destroy_bitmap (energyImage);
  al_destroy_bitmap (asteroidImage);
  al_destroy_bitmap (bombImage);
  al_destroy_bitmap (cometImage);
  al_destroy_bitmap (powerStar);
  al_destroy_bitmap (powerMagnet[0]);
  al_destroy_bitmap (powerMagnet[1]);
  al_destroy_bitmap (powerMagnet[2]);
  al_destroy_bitmap (powerMagnet[3]);

  // Stop musics
  al_stop_sample (&currentMusic);
  al_stop_sample (&currentMusic);

  // Destroy music
  al_destroy_sample (music_ingame);
  al_destroy_sample (music_death);
}

// Themes
void game::changeTheme (int NewThemeNumber) {
  std::string themeName;

  if (NewThemeNumber == 0)
    themeName = "moon";
  else if (NewThemeNumber == 1)
    themeName = "mars";
  else if (NewThemeNumber == 2)
    themeName = "sun";
  else if (NewThemeNumber == 3)
    themeName = "dark";

  themeNumber = NewThemeNumber;

  // Other theme images
  groundOverlay = load_bitmap_ex ("images/ground/groundOverlay_" + themeName + ".png");
  groundUnderlay = load_bitmap_ex ("images/ground/groundUnderlay_" + themeName + ".png");
  parallaxBack = load_bitmap_ex ("images/ground/paralax_" + themeName + ".png");

  if (settings[SETTING_CHRISTMAS])
    asteroidImage = load_bitmap_ex ("images/objects/asteroid_christmas.png");
  else
    asteroidImage = load_bitmap_ex ("images/objects/asteroid_" + themeName + ".png");
}

// Update logic of game
void game::update() {
  // Actual game stuff
  if (!paused) {
    // Check if hectar has died between logic();
    bool hectarHasDied = hectar.isAlive();

    // Update robot
    hectar.logic();

    // If its different he died play music
    if (hectarHasDied != hectar.isAlive()) {
      al_stop_sample (&currentMusic);

      if (settings[SETTING_MUSIC] == 1)
        al_play_sample (music_death, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &currentMusic);
    }

    // Add to distance travelled
    stats[STAT_DISTANCE] += motion;

    // Changes speed
    if (hectar.isAlive() && hectar.isKeyPressed())
      motion = ((score / 36) + 6);
    else
      motion *= 0.95;

    // Arrow animation
    if (!hectar.isKeyPressed())
      arrow_animation += 0.15;

    // No negative scores
    if (score < 0)
      score = 0;

    // Scrolls background
    scroll -= motion;

    if (scroll / 6 + SCREEN_W <= 0)
      scroll = 0;

    // Change theme
    if (score > 199 && themeNumber == 0)
      changeTheme (1);
    else if (score > 399 && themeNumber == 1)
      changeTheme (2);
    else if (score > 600 && themeNumber == 2)
      changeTheme (3);

    // Energy
    for (unsigned int i = 0; i < energys.size(); i++) {
      energys.at (i).logic (motion, &hectar);

      // Magnet
      if (hectar.isMagnetic())
        energys.at (i).move_towards (hectar.getX() + hectar.getWidth() / 2, hectar.getY() + hectar.getHeight() / 2, (float)hectar.getMagneticTimer());

      if (energys.at (i).offScreen() || energys.at (i).dead()) {
        energys.erase (energys.begin() + i);
        i--;
      }
    }

    // Debries
    for (unsigned int i = 0; i < debries.size(); i++) {
      debries.at (i).logic (motion, &hectar);

      if (debries.at (i).offScreen()) {
        debries.erase (debries.begin() + i);
        i--;
      }
    }

    // Powerups
    for (unsigned int i = 0; i < powerups.size(); i++) {
      powerups.at (i).logic (motion, &hectar);

      if (powerups.at (i).offScreen() || powerups.at (i).dead()) {
        powerups.erase (powerups.begin() + i);
        i--;
      }
    }

    // Spawning
    if (hectar.isAlive() && hectar.isKeyPressed()) {
      // Energy ball spawning
      if (random (0, 50) == 0 || (settings[SETTING_MEGA] && random (0, 20))) {
        energy newEnergyBall (energyImage, sound_orb, SCREEN_W, random (30, 550));
        energys.push_back (newEnergyBall);
      }

      // Asteroids spawning
      if ((score >= 100 && random (0, 50) == 0) || (settings[SETTING_MEGA] && random (0, 20))) {
        debrie newAsteroid (asteroidImage, sound_asteroid, SCREEN_W, random (30, 400), 5, 1.0f, 0.0f, random (4, 20));
        debries.push_back (newAsteroid);
      }

      // Bomb spawning
      if ((score >= 200 && random (0, 80) == 0) || (settings[SETTING_MEGA] && random (0, 20))) {
        debrie newBomb (bombImage, sound_bomb, SCREEN_W, random (30, 550), 10, 1.0f, 0.01f);
        debries.push_back (newBomb);
      }

      // Comets spawning
      if ((score >= 300 && random (0, 200) == 0) || (settings[SETTING_MEGA] && random (0, 20))) {
        debrie newComet (cometImage, sound_asteroid, SCREEN_W, random (30, 550), 5, 1.4f, 0.01f);
        debries.push_back (newComet);
      }

      // Powerup spawning
      if (score >= 100 && random (0, 3000) == 0) {
        powerup newPowerup (powerStar, sound_star, SCREEN_W, random (30, 600), 500, 1);
        powerups.push_back (newPowerup);
      }

      if (score >= 100 && random (0, 500) == 0) {
        powerup newPowerup (powerMagnet[0], sound_magnet, SCREEN_W, random (30, 600), 500, 10);
        powerups.push_back (newPowerup);
      }

      if (score >= 200 && random (0, 1000) == 0) {
        powerup newPowerup (powerMagnet[1], sound_magnet, SCREEN_W, random (30, 600), 750, 11);
        powerups.push_back (newPowerup);
      }

      if (score >= 300 && random (0, 2000) == 0) {
        powerup newPowerup (powerMagnet[2], sound_magnet, SCREEN_W, random (30, 600), 1000, 12);
        powerups.push_back (newPowerup);
      }

      if (score >= 500 && random (0, 3000) == 0) {
        powerup newPowerup (powerMagnet[3], sound_magnet, SCREEN_W, random (30, 600), 1500, 13);
        powerups.push_back (newPowerup);
      }
    }

    // Lose scripts
    if (hectar.isOnGround()) {
      //Name input
      if (check_highscore (scores, score) && keyListener::lastKeyPressed != -1) {
        // Last key pressed
        int newkey = keyListener::lastKeyPressed;

        // Letters
        if (newkey >= ALLEGRO_KEY_A && newkey <= ALLEGRO_KEY_Z && edittext.length() < 14) {
          iter = edittext.insert (iter, newkey + 96 - (keyListener::key[ALLEGRO_KEY_LSHIFT] * 32));
          ++iter;
        }
        // Numbers
        else if (newkey >= ALLEGRO_KEY_0 && newkey <= ALLEGRO_KEY_9 && edittext.length() < 14) {
          iter = edittext.insert (iter, newkey + 21);
          ++iter;
        }
        // Some other, "special" key was pressed, handle it here
        else if (newkey == ALLEGRO_KEY_BACKSPACE && iter != edittext.begin()) {
          --iter;
          iter = edittext.erase (iter);
        }
        else if (newkey == ALLEGRO_KEY_RIGHT && iter != edittext.end()) {
          ++iter;
        }
        else if (newkey == ALLEGRO_KEY_LEFT && iter != edittext.begin()) {
          --iter;
        }
      }

      if (keyListener::key[ALLEGRO_KEY_ENTER] || joystickListener::buttonPressed[JOY_XBOX_START] || joystickListener::buttonPressed[JOY_XBOX_A]) {
        addScore (scores, score, edittext);
        set_next_state (STATE_MENU);
      }
    }
  }

  // Screenshot
  if (keyListener::keyPressed[ALLEGRO_KEY_F11] || joystickListener::buttonPressed[3]) {
    // Count screenshots
    int screenshotNumber;

    // Get current number
    std::ifstream read ("screenshots/screenshot.dat");
    read >> screenshotNumber;
    read.close();

    // State new number
    std::ofstream write ("screenshots/screenshot.dat");
    write << screenshotNumber + 1;
    write.close();

    // Save to file
    al_save_bitmap ((std::string("screenshots/screenshot_") + std::to_string (screenshotNumber).c_str() + ".png").c_str(), al_get_backbuffer (display));

    // Snap sound
    al_play_sample (sound_snap, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
  }

  //Screen shake
  if (screenshake > 0 && settings[SETTING_SCREENSHAKE] != 0) {
    screenshake_x = screenshake_y = random (- (screenshake * settings[SETTING_SCREENSHAKE] + 100 * settings[SETTING_SUPERSHAKE]), screenshake * settings[SETTING_SCREENSHAKE] + 100 * settings[SETTING_SUPERSHAKE]);
    screenshake--;
  }

  if (screenshake <= 0 || !hectar.isAlive())
    screenshake_x = screenshake_y = 0;

  // Random test stuff for devs
  if (settings[SETTING_DEBUG]) {
    if (keyListener::key[ALLEGRO_KEY_R])
      score += 10;

    if (keyListener::key[ALLEGRO_KEY_E] || joystickListener::button[2])
      hectar.addHealth (1);

    if (keyListener::key[ALLEGRO_KEY_T])
      hectar.addHealth (-100);
  }

  // Pause loop code
  if (keyListener::keyPressed[ALLEGRO_KEY_ESCAPE] || mouseListener::mouse_pressed & 2 || keyListener::keyPressed[ALLEGRO_KEY_SPACE] || joystickListener::buttonPressed[JOY_XBOX_START]) {
    if (paused) {
      paused = false;
      al_hide_mouse_cursor (display);
    }
    else if (hectar.isAlive()) {
      paused = true;
      al_show_mouse_cursor (display);
    }
  }


  // Pause Menu Scripts
  if (paused) {
    // Quit game
    if (mouseListener::mouse_pressed & 1 && collision (220, 280, mouseListener::mouse_x, mouseListener::mouse_x, 435, 460, mouseListener::mouse_y, mouseListener::mouse_y))
      set_next_state (STATE_EXIT);

    // Menu
    if (mouseListener::mouse_pressed & 1 && collision (300, 430, mouseListener::mouse_x, mouseListener::mouse_x, 435, 460, mouseListener::mouse_y, mouseListener::mouse_y))
      set_next_state (STATE_MENU);

    // Resume
    if (mouseListener::mouse_pressed & 1 && collision (470, 540, mouseListener::mouse_x, mouseListener::mouse_x, 435, 460, mouseListener::mouse_y, mouseListener::mouse_y))
      paused = false;
  }
}

// Draw to screen
void game::draw() {
  // Draw backgrounds and Ground Overlay
  al_draw_bitmap (space, scroll / 6, 0, 0);
  al_draw_bitmap (space, scroll / 6 + SCREEN_W, 0, 0);

  // Draw HUD
  // Info
  al_draw_textf (orbitron_30, al_map_rgb (255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Score:%i", score);
  al_draw_textf (orbitron_30, al_map_rgb (255, 255, 255), 10, 38, ALLEGRO_ALIGN_LEFT, "Health:%i", hectar.getHealth());
  al_draw_filled_rectangle (10, 68, 10 + (hectar.getHealth() * 1.7), 78, al_map_rgb (255 - hectar.getHealth() * 2.5, 0 + hectar.getHealth() * 2.5, 0));

  // Power up timers
  if (hectar.isInvincible()) {
    al_draw_filled_circle (45, 105, 20, al_map_rgb (255, 255, 255));
    al_draw_bitmap (powerStar, 20, 80, 0);
    al_draw_textf (orbitron_24, al_map_rgb (255, 255, 255), 44, 94, ALLEGRO_ALIGN_CENTER, "%i", hectar.getInvincibleTimer() / 5);
    al_draw_textf (orbitron_24, al_map_rgb (255, 0,   0), 45, 96, ALLEGRO_ALIGN_CENTER, "%i", hectar.getInvincibleTimer() / 5);
  }

  if (hectar.isMagnetic()) {
    al_draw_filled_circle (175, 105, 20, al_map_rgb (255, 255, 255));
    al_draw_bitmap (powerMagnet[0], 150, 80, 0);
    al_draw_textf (orbitron_24, al_map_rgb (255, 255, 255), 174, 94, ALLEGRO_ALIGN_CENTER, "%i", hectar.getMagneticTimer() / 5);
    al_draw_textf (orbitron_24, al_map_rgb (255, 0,   0), 175, 96, ALLEGRO_ALIGN_CENTER, "%i", hectar.getMagneticTimer() / 5);
  }

  // Draw the debug window
  if (settings[SETTING_DEBUG]) {
    al_draw_bitmap (debug, 0, 0, 0);

    // Column 1
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 5, 25, ALLEGRO_ALIGN_LEFT, "Motion:%4.2f", motion);
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 5, 35, ALLEGRO_ALIGN_LEFT, "Robot X:%4.2f", hectar.getX());
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 5, 45, ALLEGRO_ALIGN_LEFT, "Robot Y:%4.2f", hectar.getY());
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 5, 55, ALLEGRO_ALIGN_LEFT, "Motion:%4.2f", motion);
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 5, 65, ALLEGRO_ALIGN_LEFT, "Invincible:%i", hectar.getInvincibleTimer());

    // Column 2
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 120, 25, ALLEGRO_ALIGN_LEFT, "Score:%i", score);
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 120, 35, ALLEGRO_ALIGN_LEFT, "Magnetic:%i", hectar.getMagneticTimer());
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 120, 45, ALLEGRO_ALIGN_LEFT, "Mouse X:%i", mouseListener::mouse_x);
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 120, 55, ALLEGRO_ALIGN_LEFT, "Mouse Y:%i", mouseListener::mouse_y);
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 120, 65, ALLEGRO_ALIGN_LEFT, "Particles On:%i", settings[SETTING_PARTICLE_TYPE]);

    // Column 3
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 245, 25, ALLEGRO_ALIGN_LEFT, "LowScore:%i", atoi (scores[9][1].c_str()));
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 245, 35, ALLEGRO_ALIGN_LEFT, "Theme:%i", themeNumber);
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 245, 45, ALLEGRO_ALIGN_LEFT, "Energys:%i", energys.size());
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 245, 55, ALLEGRO_ALIGN_LEFT, "Debris:%i", debries.size());
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 245, 65, ALLEGRO_ALIGN_LEFT, "Powerups:%i", powerups.size());

    // Column 4
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 360, 25, ALLEGRO_ALIGN_LEFT, "Last key:%i", keyListener::lastKeyPressed);
    al_draw_textf (orbitron_12, al_map_rgb (255, 255, 255), 360, 35, ALLEGRO_ALIGN_LEFT, "Has highscore:%i", check_highscore (scores, score));

    // FPS
    al_draw_textf (orbitron_18, al_map_rgb (255, 255, 255), SCREEN_W - 100, 25, ALLEGRO_ALIGN_LEFT, "FPS:%i", fps);
  }

  // Mountain Paralax
  al_draw_bitmap (parallaxBack, (scroll / 3) % SCREEN_W, 0, 0);
  al_draw_bitmap (parallaxBack, (scroll / 3) % SCREEN_W + SCREEN_W, 0, 0);

  // Ground
  al_draw_bitmap (groundUnderlay, scroll % SCREEN_W, SCREEN_H - 40, 0);
  al_draw_bitmap (groundUnderlay, scroll % SCREEN_W + SCREEN_W, SCREEN_H - 40, 0);

  // Energy
  for (unsigned int i = 0; i < energys.size(); i++)
    energys.at (i).draw();

  // Powerups
  for (unsigned int i = 0; i < powerups.size(); i++)
    powerups.at (i).draw();

  // Draw robot
  hectar.draw();

  // Start arrow
  if (!hectar.isKeyPressed()) {
    if (joystick_enabled)
      al_draw_bitmap (ui_a, hectar.getX() + 15, hectar.getY() - 60 - sin (arrow_animation) * 10, 0);
    else
      al_draw_bitmap (ui_up, hectar.getX() + 15, hectar.getY() - 70 - sin (arrow_animation) * 10, 0);
  }

  // Debris
  for (unsigned int i = 0; i < debries.size(); i++)
    debries.at (i).draw();

  // Ground underlay
  al_draw_bitmap (groundOverlay, scroll % SCREEN_W, SCREEN_H - 20, 0);
  al_draw_bitmap (groundOverlay, scroll % SCREEN_W + SCREEN_W, SCREEN_H - 20, 0);

  // Robot above asteroids
  hectar.draw_overlay();

  // Lose scripts
  if (hectar.isOnGround()) {
    al_draw_bitmap (ui_game_end, 0, 0, 0);
    al_draw_textf (orbitron_18, al_map_rgb (0, 0, 0), 130, 125, ALLEGRO_ALIGN_LEFT, "Final Score: %i", score);
    al_draw_textf (orbitron_18, al_map_rgb (0, 0, 0), 130, 165, ALLEGRO_ALIGN_LEFT, "Distance Flown: %i ft", stats[STAT_DISTANCE] / 10);
    al_draw_textf (orbitron_18, al_map_rgb (0, 0, 0), 130, 205, ALLEGRO_ALIGN_LEFT, "Energy Collected: %i", stats[STAT_ENERGY]);
    al_draw_textf (orbitron_18, al_map_rgb (0, 0, 0), 130, 245, ALLEGRO_ALIGN_LEFT, "Powerups Received: %i", stats[STAT_POWERUPS]);
    al_draw_textf (orbitron_18, al_map_rgb (0, 0, 0), 130, 285, ALLEGRO_ALIGN_LEFT, "Debris Collided: %i", stats[STAT_DEBRIS]);

    if (check_highscore (scores, score)) {
      // Input rectangle
      al_draw_filled_rectangle (120, 388, al_get_text_width (orbitron_24, edittext.c_str()) + 138, 432, al_map_rgb (0, 0, 0));
      al_draw_filled_rectangle (122, 390, al_get_text_width (orbitron_24, edittext.c_str()) + 136, 430, al_map_rgb (255, 255, 255));

      // Textbox lable
      al_draw_textf (orbitron_18, al_map_rgb (0, 0, 0), 129, 370, ALLEGRO_ALIGN_LEFT, "Enter your name:");

      // Output the string to the screen
      al_draw_textf (orbitron_24, al_map_rgb (0, 0, 0), 129, 400, ALLEGRO_ALIGN_LEFT, "%s", edittext.c_str());

      // Draw the caret
      al_draw_line (al_get_text_width (orbitron_24, edittext.substr (0, std::distance (edittext.begin(), iter)).c_str()) + 130, 392,
                    al_get_text_width (orbitron_24, edittext.substr (0, std::distance (edittext.begin(), iter)).c_str()) + 130, 428, al_map_rgb (0, 0, 0), 2);

      // Draw the congrats message
      al_draw_text (orbitron_18, al_map_rgb (0, 255, 0), 150, 330, ALLEGRO_ALIGN_LEFT, "New highscore!");
      al_draw_text (orbitron_24, al_map_rgb (0, 0, 0), 150, 450, ALLEGRO_ALIGN_LEFT, "Press Enter/   to continue");
      al_draw_bitmap (ui_b, 370, 450, 0);
    }
    else {
      al_draw_text (orbitron_24, al_map_rgb (0, 0, 0), 150, 395, ALLEGRO_ALIGN_LEFT, "Press Enter/   to continue");
      al_draw_bitmap (ui_b, 370, 395, 0);
    }
  }

  // Pause Menu Scripts
  if (paused) {
    // Menu
    al_draw_bitmap (pauseMenu, 130, 140, 0);

    // Stats
    al_draw_textf (orbitron_18, al_map_rgb (255, 255, 255), 220, 250, ALLEGRO_ALIGN_LEFT, "Distance Flown: %i ft", stats[STAT_DISTANCE] / 10);
    al_draw_textf (orbitron_18, al_map_rgb (255, 255, 255), 220, 280, ALLEGRO_ALIGN_LEFT, "Energy Collected: %i", stats[STAT_ENERGY]);
    al_draw_textf (orbitron_18, al_map_rgb (255, 255, 255), 220, 310, ALLEGRO_ALIGN_LEFT, "Powerups Received: %i", stats[STAT_POWERUPS]);
    al_draw_textf (orbitron_18, al_map_rgb (255, 255, 255), 220, 340, ALLEGRO_ALIGN_LEFT, "Debris Collided: %i", stats[STAT_DEBRIS]);

    // Buttons
    al_draw_text (orbitron_18, al_map_rgb (0, 0, 0), 220, 445, ALLEGRO_ALIGN_LEFT, "Quit");
    al_draw_text (orbitron_18, al_map_rgb (0, 0, 0), 300, 445, ALLEGRO_ALIGN_LEFT, "Main Menu");
    al_draw_text (orbitron_18, al_map_rgb (0, 0, 0), 470, 445, ALLEGRO_ALIGN_LEFT, "Resume");
  }
}
