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
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Load intro image
  img_menu = load_bitmap_ex( "images/backgrounds/menu.png");
  start = load_bitmap_ex( "images/gui/start.png");
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

  // Read settings from file
  read_settings();

  // Init animation vars
  animation_start_x = -400;
  animation_title_y = -100;
  animation_credits_y = 600;

  // Hide mouse
  show_mouse( NULL);
}

// Destructor
menu::~menu(){

}

// Update loop
void menu::update(){
  // Start the game
  if( startClicked && animation_start_x < -399){
    // Go to game
    set_next_state( STATE_GAME);
  }

  // Start game with controller
  if( settings[SETTING_CONTROLMODE] == 3 || joystick_enabled){
    if( joy[0].button[7].b){
      startClicked = true;
    }
  }

  // Open submenu or start game
  if( mini_screen == MINISTATE_MENU && mouseListener::buttonPressed[1]){
    // Start game
    if( ( mouse_x > 40 && mouse_x < 260 && mouse_y > 410 && mouse_y < 510) || joy[0].button[1].b){
      startClicked = true;
    }
    // Scores
    else if( mouse_x > 600 && mouse_x < 760 && mouse_y > 20 && mouse_y < 120){
      updateScores();
      mini_screen = MINISTATE_SCORES;
    }
    // Credits menu
    else if( collision( mouse_x, mouse_x,542 ,644, mouse_y,mouse_y, 548,600)){
      mini_screen = MINISTATE_CREDITS;
    }
    // Help screen
    else if( collision( mouse_x, mouse_x, 698,748, mouse_y,mouse_y, 548,600)){
      mini_screen = MINISTATE_TUTORIAL;
    }
    // Options menu
    else if( collision( mouse_x,mouse_x, 748, 800, mouse_y, mouse_y, 548, 600)){
      mini_screen = MINISTATE_OPTIONS;
    }
    // Controls menu
    else if( collision( mouse_x, mouse_x,645 ,697, mouse_y,mouse_y, 548 ,600)){
      mini_screen = MINISTATE_CONTROLS;
    }
  }
  // Exit menus
  else if( mini_screen == MINISTATE_TUTORIAL || mini_screen == MINISTATE_CREDITS || mini_screen == MINISTATE_CONTROLS || mini_screen == MINISTATE_SCORES ){
    if( (keyboard_keypressed() && settings[SETTING_CONTROLMODE] != 3)  || (mouseListener::buttonPressed[1] && settings[SETTING_CONTROLMODE] != 3) || (joy_buttonpressed() && settings[SETTING_CONTROLMODE] != 2)){
			mini_screen = MINISTATE_MENU;
			draw();
    }
  }
  // Options
  else if( mini_screen == MINISTATE_OPTIONS && mouseListener::buttonPressed[1]){
    // Particles toggle
    if( collision( 280, 360, mouse_x, mouse_x, 400, 480, mouse_y, mouse_y)){
      settings[SETTING_PARTICLE_TYPE] = (settings[SETTING_PARTICLE_TYPE] + 1) % 4;
    }
    // Sound button toggle
    else if( collision( 120, 200, mouse_x, mouse_x, 180, 260, mouse_y, mouse_y)){
      settings[SETTING_SOUND] = (settings[SETTING_SOUND] + 1) % 2;
    }
    // Music button toggle
    else if( collision( 280, 360, mouse_x, mouse_x, 180, 260, mouse_y, mouse_y)){
      settings[SETTING_MUSIC] = (settings[SETTING_MUSIC] + 1) % 2;
    }
    // Fullscreen toggle
    else if( collision( 120, 200, mouse_x, mouse_x, 400, 480, mouse_y, mouse_y)){
      settings[SETTING_FULLSCREEN] = (settings[SETTING_FULLSCREEN] + 1) % 2;
      if( settings[SETTING_FULLSCREEN])
        set_gfx_mode( GFX_AUTODETECT_FULLSCREEN, 800, 600, 0, 0);
      else
        set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
    }
    //Screen shake
    else if( collision( 280, 360, mouse_x, mouse_x, 290, 370, mouse_y, mouse_y)){
      settings[SETTING_SCREENSHAKE] = (settings[SETTING_SCREENSHAKE] + 1) % 4;
    }
    // Control Toggle
    else if( collision( 120, 200, mouse_x, mouse_x, 290, 370, mouse_y, mouse_y)){
      settings[SETTING_CONTROLMODE] = ((settings[SETTING_CONTROLMODE] + 1) % 3);
    }
    // Power off
    else if( collision( 540, 620, mouse_x, mouse_x, 180, 260, mouse_y, mouse_y)){
      write_settings();
      set_next_state( STATE_EXIT);
    }
    // Exit menu
    else if( collision(540,620,mouse_x,mouse_x,407,487,mouse_y,mouse_y)){
      mini_screen = MINISTATE_MENU;
      write_settings();
    }
  }


  // Update mouse particles
  if( settings[SETTING_PARTICLE_TYPE] != 3 && mouse_rocket_up){
    for( int i = 0; i < 500; i++){
      if( random( 1, 10) == 1){
        int part_color = makecol( 255, random(0,255), 0);
        if( settings[SETTING_CHRISTMAS]){
          int red_or_green = random( 0, 1) * 255;
          part_color = makecol( red_or_green, 255 - red_or_green, 0);
        }
        particle newParticle( mouse_x + 10, mouse_y + 16, part_color, random( -2, 2), random( 4, 8), 1, settings[SETTING_PARTICLE_TYPE]);
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
  if( key[KEY_ESC])
    set_next_state( STATE_EXIT);

  // Check if mouse is going up
  mouse_rocket_up = (mouse_y < mouseMove);
  mouseMove = mouse_y;
}

// Draw to screen
void menu::draw(){
  //Menu animations
  if( animation_start_x < 1 && !startClicked)
    animation_start_x += 20;
  if( animation_start_x > -399 && startClicked)
    animation_start_x -= 20;
  if( animation_title_y < 20 && !startClicked)
    animation_title_y += 10;
  if( animation_title_y > -119 && startClicked)
    animation_title_y -= 10;
  if( animation_credits_y > 548 && !startClicked)
    animation_credits_y -= 4;
  if( animation_credits_y < 600 && startClicked)
    animation_credits_y += 4;

  //Draw backdrop
  clear_to_color( buffer, 0xFFFFFF);

  // Menu Background
  draw_sprite( buffer, img_menu, 0, 0);

  // Start button
  draw_sprite( buffer, start, animation_start_x, 400);

  // Joystick Mode
  if( joystick_enabled){
    draw_sprite( buffer, xbox_start, animation_start_x + 225, 430);
  }

  // Nice title image
  draw_sprite( buffer, title, 20, animation_title_y);

  // Bottom Right Buttons
  draw_sprite( buffer, ui_credits, 541, animation_credits_y);
  draw_sprite( buffer, ui_controls, 645, animation_credits_y);
  draw_sprite( buffer, ui_help, 697, animation_credits_y);
  draw_sprite( buffer, ui_options, 749, animation_credits_y);

  //Draw scores
  if( mini_screen == MINISTATE_SCORES){
    // Highscore background
    draw_sprite( buffer, highscores_table, 200, 50);

    // Title
    textout_centre_ex( buffer, orbitron, "Highscores", 400, 75, makecol(0,0,0), -1);

    // Read the top 10 scores
    for( int i = 0; i < 10; i++){
      textout_ex(buffer, orbitron, scores[i][0].c_str(), 225, (i * 40) + 120, makecol(0,0,0), -1);
      textout_right_ex( buffer, orbitron, scores[i][1].c_str(), 575, (i * 40) + 120, makecol(0,0,0), -1);
    }
  }
  // Tutorial screen
  else if( mini_screen == MINISTATE_TUTORIAL){
  	draw_sprite( buffer, helpScreen, 0, 0);
  }
  // Credits screen
  else if( mini_screen == MINISTATE_CREDITS){
    draw_sprite( buffer, credits, 0, 0);
  }
  // Credits screen
  else if( mini_screen == MINISTATE_CONTROLS){
  	draw_sprite( buffer, controls, 0, 0);
  }
  // Option Menu drawing(page and ingame)
  else if( mini_screen == MINISTATE_OPTIONS){
    // Background
    draw_sprite( buffer, options, 0, 0);

    // Buttons
    draw_sprite( buffer, ui_particle[settings[SETTING_PARTICLE_TYPE]], 280, 407);
    draw_sprite( buffer, ui_sound[settings[SETTING_SOUND]], 120, 180);
    draw_sprite( buffer, ui_music[settings[SETTING_MUSIC]], 280, 180);
    draw_sprite( buffer, ui_window[settings[SETTING_FULLSCREEN]], 120, 407);
    draw_sprite( buffer, ui_screenshake[settings[SETTING_SCREENSHAKE]], 280, 295);
    draw_sprite( buffer, ui_control[settings[SETTING_CONTROLMODE]], 120, 295);

    // Button Text
    textprintf_ex( buffer, orbitron, 110, 146, makecol( 255, 250, 250),-1,"Sounds   Music           Exit");
    textprintf_ex( buffer, orbitron, 108, 375, makecol(255,250,250), -1, "Window Particles         Back");
    textprintf_ex( buffer, orbitron, 120, 260, makecol( 255, 250, 250), -1, "Input  Screen shake");

    // Exit and back
    draw_sprite( buffer, ui_exit, 540, 180);
    draw_sprite( buffer, ui_back, 540, 407);
  }

  // Draw mouse particles
  if( settings[SETTING_PARTICLE_TYPE] == 3){
    if( mouse_rocket_up){
      draw_sprite( buffer, mouse_rocket, mouse_x, mouse_y);
    }
  }
  else{
    for( unsigned int i = 0; i < mousePart.size(); i++){
      mousePart.at(i).draw( buffer);
    }
  }
  draw_sprite( buffer, mouse, mouse_x, mouse_y);

  // Buffer to screen
  draw_sprite( screen, buffer, 0, 0);
}
