#include "menu.h"

// Construct state
menu::menu(){
  // Init vars
  startMove = false;
  startClicked = false;
  mouse_rocket_up = false;

  // Screen on
  mini_screen = MINISTATE_MENU;

  // Buffer
  buffer = al_create_bitmap( SCREEN_W, SCREEN_H);

  // Load intro image
  // Random menu
  img_menu = load_bitmap_ex( "images/backgrounds/background_" + convertIntToString(random( 0, 3)) + ".png");
  start = load_bitmap_ex( "images/gui/start.png");
  highscores_button = load_bitmap_ex( "images/gui/highscores.png");
  mouse = load_bitmap_ex( "images/gui/mouse.png");
  mouse_rocket = load_bitmap_ex( "images/gui/mouse_rocket.png");
  title = load_bitmap_ex( "images/gui/title.png");
  options = load_bitmap_ex( "images/gui/options.png");

  ui_sound[1] = load_bitmap_ex( "images/gui/ui_sound_on.png");
  ui_sound[0] = load_bitmap_ex( "images/gui/ui_sound_off.png");

  ui_music[1] = load_bitmap_ex( "images/gui/ui_music_on.png");
  ui_music[0] = load_bitmap_ex( "images/gui/ui_music_off.png");

  ui_window[1] = load_bitmap_ex( "images/gui/ui_window_windowed.png");
  ui_window[0] = load_bitmap_ex( "images/gui/ui_window_fullscreen.png");

  ui_particle[0] = load_bitmap_ex("images/gui/ui_particle_circle.png");
  ui_particle[1] = load_bitmap_ex("images/gui/ui_particle_square.png");
  ui_particle[2] = load_bitmap_ex("images/gui/ui_particle_pixel.png");
  ui_particle[3] = load_bitmap_ex("images/gui/ui_particle_off.png");

  ui_control[0] = load_bitmap_ex("images/gui/ui_control_xbox.png");
  ui_control[1] = load_bitmap_ex("images/gui/ui_control_keyboard.png");
  ui_control[2] = load_bitmap_ex("images/gui/ui_control_auto.png");

  ui_screenshake[0] = load_bitmap_ex("images/gui/ui_screenshake_none.png");
  ui_screenshake[1] = load_bitmap_ex("images/gui/ui_screenshake_low.png");
  ui_screenshake[2] = load_bitmap_ex("images/gui/ui_screenshake_medium.png");
  ui_screenshake[3] = load_bitmap_ex("images/gui/ui_screenshake_high.png");

  ui_options = load_bitmap_ex( "images/gui/ui_options.png");
  ui_options_small = load_bitmap_ex( "images/gui/ui_options_small.png");
  ui_back = load_bitmap_ex( "images/gui/ui_back.png");
  credits = load_bitmap_ex("images/gui/credits.png");
  ui_credits = load_bitmap_ex("images/gui/ui_credits.png");
  highscores_table = load_bitmap_ex("images/gui/highscores_table.png");
  ui_help = load_bitmap_ex("images/gui/ui_help.png");
  helpScreen = load_bitmap_ex("images/gui/helpScreen.png");
  ui_exit = load_bitmap_ex("images/gui/ui_exit.png");
  xbox_start = load_bitmap_ex("images/gui/xbox_start.png");
  ui_screenshot_notification = load_bitmap_ex("images/gui/ui_screenshot_notification.png");
  ui_controls = load_bitmap_ex("images/gui/ui_controls.png");
  controls = load_bitmap_ex("images/gui/controls.png");

  // Load that menu music
  music_mainmenu = load_sample_ex("audio/music_mainmenu.ogg");

  // Read settings from file
  read_settings();

  // Init animation vars
  animation_pos = 0;

  // Hide mouse
  al_hide_mouse_cursor( display);

  // Load scores
  updateScores( scores);

  // Play music
  if( settings[SETTING_MUSIC] == 1)
    al_play_sample( music_mainmenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &currentMusic);
}

// Destructor
menu::~menu(){
  // Stops music
  al_stop_sample( &currentMusic);

  // Destroy samples
  al_destroy_sample( music_mainmenu);

  // Destroy images
  al_destroy_bitmap( buffer);
  al_destroy_bitmap( img_menu);
  al_destroy_bitmap( options);
  al_destroy_bitmap( helpScreen);
  al_destroy_bitmap( controls);
  al_destroy_bitmap( credits);
  al_destroy_bitmap( highscores_table);
  al_destroy_bitmap( start);
  al_destroy_bitmap( title);
  al_destroy_bitmap( highscores_button);
  al_destroy_bitmap( mouse);
  al_destroy_bitmap( mouse_rocket);
  al_destroy_bitmap( xbox_start);
  al_destroy_bitmap( ui_sound[0]);
  al_destroy_bitmap( ui_sound[1]);
  al_destroy_bitmap( ui_music[0]);
  al_destroy_bitmap( ui_music[1]);
  al_destroy_bitmap( ui_screenshake[0]);
  al_destroy_bitmap( ui_screenshake[1]);
  al_destroy_bitmap( ui_screenshake[2]);
  al_destroy_bitmap( ui_screenshake[3]);
  al_destroy_bitmap( ui_window[0]);
  al_destroy_bitmap( ui_window[1]);
  al_destroy_bitmap( ui_particle[0]);
  al_destroy_bitmap( ui_particle[1]);
  al_destroy_bitmap( ui_particle[2]);
  al_destroy_bitmap( ui_particle[3]);
  al_destroy_bitmap( ui_control[0]);
  al_destroy_bitmap( ui_control[1]);
  al_destroy_bitmap( ui_control[2]);
  al_destroy_bitmap( ui_options);
  al_destroy_bitmap( ui_options_small);
  al_destroy_bitmap( ui_back);
  al_destroy_bitmap( ui_credits);
  al_destroy_bitmap( ui_exit);
  al_destroy_bitmap( ui_help);
  al_destroy_bitmap( ui_screenshot_notification);
  al_destroy_bitmap( ui_controls);
}

//Writes the settings to file
void menu::write_settings(){
  std::ofstream settings_file("data/settings.dat");
  for (int i = 0; i < 7; i++)
    settings_file << settings[i] << " ";
  settings_file.close();
}

//Reads the data from file
void menu::read_settings(){
  std::ifstream read("data/settings.dat");
  for (int i = 0; i < 7; i++)
    read >> settings[i];
  read.close();
}

// Update loop
void menu::update(){
  //Menu animations
  if( animation_pos < 100 && !startClicked)
    animation_pos += 4;
  if( animation_pos > 0 && startClicked)
    animation_pos -= 4;

  // Start the game
  if( startClicked && animation_pos <= 0)
    set_next_state( STATE_GAME);

  // Open submenu or start game
  if( mini_screen == MINISTATE_MENU){
    // Start game with controller
    if( joystickListener::buttonPressed[JOY_XBOX_START] || joystickListener::buttonPressed[JOY_XBOX_A]){
      startClicked = true;
    }
    // Buttons
    if( mouseListener::mouse_pressed & 1){
      // Start game
      if( collision( mouseListener::mouse_x, mouseListener::mouse_x, 40, 40 + al_get_bitmap_width(start), mouseListener::mouse_y, mouseListener::mouse_y, 410, 410 + al_get_bitmap_height(start))){
        startClicked = true;
      }
      // Scores
      else if( collision( mouseListener::mouse_x, mouseListener::mouse_x, 660, 660 + al_get_bitmap_width(highscores_button), mouseListener::mouse_y, mouseListener::mouse_y, 30, 30 + al_get_bitmap_height(highscores_button))){
        updateScores( scores);
        mini_screen = MINISTATE_SCORES;
      }
      // Credits menu
      else if( collision( mouseListener::mouse_x, mouseListener::mouse_x, 542, 644, mouseListener::mouse_y, mouseListener::mouse_y, 548, 600)){
        mini_screen = MINISTATE_CREDITS;
      }
      // Controls menu
      else if( collision( mouseListener::mouse_x, mouseListener::mouse_x, 644, 696, mouseListener::mouse_y, mouseListener::mouse_y, 548 ,600)){
        mini_screen = MINISTATE_CONTROLS;
      }
      // Help screen
      else if( collision( mouseListener::mouse_x, mouseListener::mouse_x, 696, 749, mouseListener::mouse_y, mouseListener::mouse_y, 548, 600)){
        mini_screen = MINISTATE_TUTORIAL;
      }
      // Options menu
      else if( collision( mouseListener::mouse_x, mouseListener::mouse_x, 749, 800, mouseListener::mouse_y, mouseListener::mouse_y, 548, 600)){
        mini_screen = MINISTATE_OPTIONS;
      }
    }
  }
  // Exit menus
  else if( mini_screen == MINISTATE_TUTORIAL || mini_screen == MINISTATE_CREDITS || mini_screen == MINISTATE_CONTROLS || mini_screen == MINISTATE_SCORES ){
    if( keyListener::lastKeyPressed != -1  || mouseListener::mouse_pressed & 1 || joystickListener::lastButtonPressed != -1){
			mini_screen = MINISTATE_MENU;
			draw();
    }
  }
  // Options
  else if( mini_screen == MINISTATE_OPTIONS && mouseListener::mouse_pressed & 1){
    // Particles toggle
    if( collision( 280, 360, mouseListener::mouse_x, mouseListener::mouse_x, 400, 480, mouseListener::mouse_y, mouseListener::mouse_y)){
      settings[SETTING_PARTICLE_TYPE] = (settings[SETTING_PARTICLE_TYPE] + 1) % 4;
    }
    // Sound button toggle
    else if( collision( 120, 200, mouseListener::mouse_x, mouseListener::mouse_x, 180, 260, mouseListener::mouse_y, mouseListener::mouse_y)){
      settings[SETTING_SOUND] = (settings[SETTING_SOUND] + 1) % 2;
    }
    // Music button toggle
    else if( collision( 280, 360, mouseListener::mouse_x, mouseListener::mouse_x, 180, 260, mouseListener::mouse_y, mouseListener::mouse_y)){
      settings[SETTING_MUSIC] = (settings[SETTING_MUSIC] + 1) % 2;
      if( settings[SETTING_MUSIC] == 0)
        al_stop_sample( &currentMusic);
      else
        al_play_sample( music_mainmenu, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &currentMusic);

    }
    // Fullscreen toggle
    else if( collision( 120, 200, mouseListener::mouse_x, mouseListener::mouse_x, 400, 480, mouseListener::mouse_y, mouseListener::mouse_y)){
      settings[SETTING_FULLSCREEN] = (settings[SETTING_FULLSCREEN] + 1) % 2;

      if( settings[SETTING_FULLSCREEN]){
        // Fullscreen stuff
        al_destroy_display( display);
        al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
        display = al_create_display( SCREEN_W, SCREEN_H);

        ALLEGRO_DISPLAY_MODE disp_data;
        al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
        float sx = disp_data.width / (float)SCREEN_W;
        float sy = disp_data.height / (float)SCREEN_H;

        ALLEGRO_TRANSFORM trans;
        al_identity_transform(&trans);
        al_scale_transform(&trans, sx, sy);
        al_use_transform(&trans);
        al_hide_mouse_cursor( display);
      }
      else{
        al_destroy_display( display);
        al_set_new_display_flags(ALLEGRO_WINDOWED);
        display = al_create_display( SCREEN_W, SCREEN_H);
        al_hide_mouse_cursor( display);
      }
    }
    //Screen shake
    else if( collision( 280, 360, mouseListener::mouse_x, mouseListener::mouse_x, 290, 370, mouseListener::mouse_y, mouseListener::mouse_y)){
      settings[SETTING_SCREENSHAKE] = (settings[SETTING_SCREENSHAKE] + 1) % 4;
    }
    // Control Toggle
    else if( collision( 120, 200, mouseListener::mouse_x, mouseListener::mouse_x, 290, 370, mouseListener::mouse_y, mouseListener::mouse_y)){
      settings[SETTING_CONTROLMODE] = ((settings[SETTING_CONTROLMODE] + 1) % 3);
    }
    // Power off
    else if( collision( 540, 620, mouseListener::mouse_x, mouseListener::mouse_x, 180, 260, mouseListener::mouse_y, mouseListener::mouse_y)){
      write_settings();
      set_next_state( STATE_EXIT);
    }
    // Exit menu
    else if( collision( 540, 620, mouseListener::mouse_x, mouseListener::mouse_x, 407, 487, mouseListener::mouse_y, mouseListener::mouse_y)){
      mini_screen = MINISTATE_MENU;
      write_settings();
    }
  }

  // Update mouse particles
  if( settings[SETTING_PARTICLE_TYPE] != 3 && mouse_rocket_up){
    for( int i = 0; i < 500; i++){
      if( random( 1, 10) == 1){
        ALLEGRO_COLOR part_color = al_map_rgb( 255, random(0,255), 0);
        if( settings[SETTING_CHRISTMAS]){
          int red_or_green = random( 0, 1) * 255;
          part_color = al_map_rgb( red_or_green, 255 - red_or_green, 0);
        }
        particle newParticle( mouseListener::mouse_x, mouseListener::mouse_y + 16, part_color, random( -2, 2), random( 8, 20), 1, settings[SETTING_PARTICLE_TYPE]);
        mousePart.push_back( newParticle);
      }
    }
  }
  for( unsigned int i = 0; i < mousePart.size(); i++){
    mousePart.at(i).logic();
    if( random( 0, 10) == 0)
      mousePart.erase( mousePart.begin() + i);
  }

  // Close game
  if( keyListener::key[ALLEGRO_KEY_ESCAPE])
    set_next_state( STATE_EXIT);

  // Check if mouse is going up
  mouse_rocket_up = ( mouseListener::mouse_y < mouseMove);
  mouseMove = mouseListener::mouse_y;
}

// Draw to screen
void menu::draw(){
  // Menu Background
  al_draw_bitmap( img_menu, 0, 0, 0);

  // Start button
  al_draw_bitmap( start, (animation_pos * 3.2) - al_get_bitmap_width(start), 400, 0);

  // Highscores button
  al_draw_bitmap( highscores_button, SCREEN_W - (animation_pos * 1.4), 30, 0);

  // Joystick Mode
  if( settings[SETTING_CONTROLMODE] != 1 && joystick_enabled){
    al_draw_bitmap( xbox_start, (animation_pos * 3.2) - al_get_bitmap_width(start) + 220, 430, 0);
  }

  // Nice title image
  al_draw_bitmap( title, 20, (animation_pos * 1.2) - al_get_bitmap_height(title), 0);

  // Bottom Right Buttons
  al_draw_bitmap( ui_credits,  541, SCREEN_H - (animation_pos * al_get_bitmap_height(ui_credits))/100, 0);
  al_draw_bitmap( ui_controls, 645, SCREEN_H - (animation_pos * al_get_bitmap_height(ui_controls))/100, 0);
  al_draw_bitmap( ui_help,     697, SCREEN_H - (animation_pos * al_get_bitmap_height(ui_help))/100, 0);
  al_draw_bitmap( ui_options,  749, SCREEN_H - (animation_pos * al_get_bitmap_height(ui_options))/100, 0);

  //Draw scores
  if( mini_screen == MINISTATE_SCORES){
    // Highscore background
    al_draw_bitmap( highscores_table, 200, 50, 0);

    // Title
    al_draw_text( orbitron_36, al_map_rgb(0,0,0), 400, 75, ALLEGRO_ALIGN_CENTRE , "Highscores");

    // Read the top 10 scores
    for( int i = 0; i < 10; i++){
      al_draw_text( orbitron_24, al_map_rgb(0,0,0), 225, (i * 40) + 130, ALLEGRO_ALIGN_LEFT, scores[i][0].c_str());
      al_draw_text( orbitron_18, al_map_rgb(0,0,0), 575, (i * 40) + 132, ALLEGRO_ALIGN_RIGHT, scores[i][1].c_str());
    }
  }
  // Tutorial screen
  else if( mini_screen == MINISTATE_TUTORIAL){
  	al_draw_bitmap( helpScreen, 0, 0, 0);
  }
  // Credits screen
  else if( mini_screen == MINISTATE_CREDITS){
    al_draw_bitmap( credits, 0, 0, 0);
  }
  // Credits screen
  else if( mini_screen == MINISTATE_CONTROLS){
  	al_draw_bitmap( controls, 0, 0, 0);
  }
  // Option Menu drawing(page and ingame)
  else if( mini_screen == MINISTATE_OPTIONS){
    // Background
    al_draw_bitmap( options, 0, 0, 0);

    // Buttons
    al_draw_bitmap( ui_particle[settings[SETTING_PARTICLE_TYPE]], 280, 407, 0);
    al_draw_bitmap( ui_sound[settings[SETTING_SOUND]], 120, 180, 0);
    al_draw_bitmap( ui_music[settings[SETTING_MUSIC]], 280, 180, 0);
    al_draw_bitmap( ui_window[settings[SETTING_FULLSCREEN]], 120, 407, 0);
    al_draw_bitmap( ui_screenshake[settings[SETTING_SCREENSHAKE]], 280, 295, 0);
    al_draw_bitmap( ui_control[settings[SETTING_CONTROLMODE]], 120, 295, 0);

    // Button Text
    al_draw_text( orbitron_24, al_map_rgb( 255, 250, 250), 110, 154, ALLEGRO_ALIGN_LEFT , "Sounds         Music                            Exit");
    al_draw_text( orbitron_24, al_map_rgb( 255, 250, 250), 126, 268, ALLEGRO_ALIGN_LEFT , "Input      Screen Shake");
    al_draw_text( orbitron_24, al_map_rgb( 255, 250, 250), 108, 382, ALLEGRO_ALIGN_LEFT , "Window       Particles                        Back");

    // Exit and back
    al_draw_bitmap( ui_exit, 540, 180, 0);
    al_draw_bitmap( ui_back, 540, 407, 0);
  }

  // Debug
  if( settings[SETTING_DEBUG]){
    // Joystick testing
    if( joystick_enabled){
      for( int i = 0; i < JOY_MAX_BUTTONS; i++){
        al_draw_textf( orbitron_12, al_map_rgb( 255, 255, 255), 20, 10 * i + 20, ALLEGRO_ALIGN_LEFT , "Joystick B %i : %i", i, joystickListener::button[i]);
      }
    }
    // FPS
    al_draw_textf( orbitron_12, al_map_rgb( 255, 255, 255), SCREEN_W - 100, 20, ALLEGRO_ALIGN_LEFT , "FPS:%i", fps);
  }

  // Draw rocket if no particles
  if( settings[SETTING_PARTICLE_TYPE] == 3 && mouse_rocket_up)
    al_draw_bitmap( mouse_rocket, mouseListener::mouse_x - 10, mouseListener::mouse_y, 0);

  // Draw mouse particles
  for( unsigned int i = 0; i < mousePart.size(); i++)
    mousePart.at(i).draw();

  al_draw_bitmap( mouse, mouseListener::mouse_x - 10, mouseListener::mouse_y, 0);
}
