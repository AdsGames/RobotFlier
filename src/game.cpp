#include "game.h"

// Constructor
game::game(){
  // From globals
  score = 0;
  screenshake = 0;

  // Game related
  scroll = 0;
  motion = 5;
  themeNumber = 0;
  screenshake_x = 0;
  screenshake_y = 0;
  paused = false;

  // End game menu
  edittext = "Player";
  iter = edittext.end();

  // Reset stats
  for( int i = 0; i < 4; i++)
    stats[i] = 0;

  // Create buffer
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Sounds
  sound_bomb = load_sample_ex( "audio/sound_bomb.wav");
  sound_orb = load_sample_ex("audio/sound_orb.wav");
  sound_asteroid = load_sample_ex( "audio/sound_asteroid.wav");
  sound_magnet = load_sample_ex( "audio/sound_magnet.wav");
  sound_star = load_sample_ex( "audio/sound_star.wav");
  sound_snap = load_sample_ex( "audio/sound_snap.wav");

  // Music
  music_death = logg_load_ex( "audio/music_death.ogg");
  music_ingame = logg_load_ex( "audio/music_ingame.ogg");

  // Images
  // Gui
  pauseMenu = load_bitmap_ex( "images/gui/pauseMenu.png");
  ui_game_end = load_bitmap_ex( "images/gui/ui_game_end.png");
  ui_a = load_bitmap_ex("images/gui/ui_a.png");
  ui_b = load_bitmap_ex("images/gui/ui_b.png");
  debug = load_bitmap_ex( "images/gui/debug.png");

  // Background/paralax
  space = load_bitmap_ex( "images/backgrounds/space.png");
  groundOverlay = NULL;
  groundUnderlay = NULL;

  // Objects
  cometImage = load_bitmap_ex("images/objects/comet.png");
  powerStar = load_bitmap_ex("images/objects/powerStar.png");
  powerMagnet[0] = load_bitmap_ex("images/objects/powerMagnet.png");
  powerMagnet[1] = load_bitmap_ex("images/objects/powerMagnetTwo.png");
  powerMagnet[2] = load_bitmap_ex("images/objects/powerMagnetThree.png");
  powerMagnet[3] = load_bitmap_ex("images/objects/powerMagnetFour.png");
  if( settings[SETTING_CHRISTMAS]){
    energyImage = load_bitmap_ex("images/objects/energy_christmas.png");
    bombImage = load_bitmap_ex("images/objects/bomb_christmas.png");
  }
  else{
    energyImage = load_bitmap_ex("images/objects/energy.png");
    bombImage = load_bitmap_ex("images/objects/bomb.png");
  }

  // Sets the level to 1
  changeTheme( 0);

  // Mouse
  enable_hardware_cursor();
  select_mouse_cursor( MOUSE_CURSOR_ARROW);
  show_mouse( NULL);

  // Init hectar
  hectar = robot( 80, 300);

  // Play music
  if( settings[SETTING_MUSIC] == 1)
    play_sample( music_ingame, 255, 128, 1000, 1);
}

// Destructor
game::~game(){
  // Stop musics
  stop_sample( music_death);
  stop_sample( music_ingame);
}

// Themes
void game::changeTheme( int NewThemeNumber){
	std::string themeName;

	if( NewThemeNumber == 0)
		themeName = "moon";
	else if( NewThemeNumber == 1)
		themeName = "mars";
	else if( NewThemeNumber == 2)
		themeName = "sun";
	else if( NewThemeNumber == 3)
		themeName = "dark";
	themeNumber = NewThemeNumber;

  // Other theme images
  groundOverlay = load_bitmap_ex( "images/ground/groundOverlay_" + themeName + ".png");
  groundUnderlay = load_bitmap_ex( "images/ground/groundUnderlay_" + themeName + ".png");
  space2 = load_bitmap_ex( "images/ground/paralax_" + themeName + ".png");

  if( settings[SETTING_CHRISTMAS])
    asteroidImage = load_bitmap_ex("images/objects/asteroid_christmas.png");
  else
    asteroidImage = load_bitmap_ex( "images/objects/asteroid_" + themeName + ".png");
}

// Update logic of game
void game::update(){
  // Actual game stuff
  if( !paused){
    // Check if hectar has died between logic();
    bool hectarHasDied = hectar.isAlive();

    // Update robot
    hectar.logic();

    // If its different he died play music
    if( hectarHasDied != hectar.isAlive()){
      stop_sample( music_ingame);
      if( settings[SETTING_MUSIC] == 1)
        play_sample( music_death, 255, 128, 1000, 1);
    }

    // Add to distance travelled
    stats[STAT_DISTANCE] += motion;

    // Changes speed
    if( hectar.isAlive())
      motion = ((score/36) + 6);
    else
      motion *= 0.95;

    // No negative scores
    if( score < 0)
      score = 0;

    // Scrolls background
    scroll -= motion;
    if( scroll/6 + SCREEN_W <= 0)
      scroll = 0;

    // Change theme
    if( score > 199 && themeNumber == 0)
      changeTheme(1);
    else if( score > 399 && themeNumber == 1)
      changeTheme(2);
    else if( score > 600 && themeNumber == 2)
      changeTheme(3);

    // Energy
    for( unsigned int i = 0; i < energys.size(); i++){
      energys.at(i).logic( motion, &hectar);
      // Magnet
      if( hectar.isMagnetic())
        energys.at(i).move_towards( hectar.getX() + hectar.getWidth()/2, hectar.getY() + hectar.getHeight()/2, (float)hectar.getMagneticTimer());
      if( energys.at(i).offScreen() || energys.at(i).dead()){
        energys.erase(energys.begin() + i);
        i--;
      }
    }

    // Debries
    for( unsigned int i = 0; i < debries.size(); i++){
      debries.at(i).logic( motion, &hectar);
      if( debries.at(i).offScreen()){
        debries.erase(debries.begin() + i);
        i--;
      }
    }

    // Powerups
    for( unsigned int i = 0; i < powerups.size(); i++){
      powerups.at(i).logic( motion, &hectar);
      if( powerups.at(i).offScreen() || powerups.at(i).dead()){
        powerups.erase(powerups.begin() + i);
        i--;
      }
    }

    // Spawning
    if( hectar.isAlive()){
      // Energy ball spawning
      if( random(0,50) == 0 || (settings[SETTING_MEGA] && random(0, 20))){
        energy newEnergyBall( energyImage, sound_orb, SCREEN_W, random(30,550));
        energys.push_back( newEnergyBall);
      }
      // Asteroids spawning
      if( (score >= 100 && random(0,50) == 0) || (settings[SETTING_MEGA] && random(0, 20))){
        debrie newAsteroid( asteroidImage, sound_asteroid, SCREEN_W, random(30,550), 5, 1, random(4,20));
        debries.push_back( newAsteroid);
      }
      // Bomb spawning
      if( (score >= 200 && random(0,80) == 0) || (settings[SETTING_MEGA] && random(0, 20))){
        debrie newBomb( bombImage, sound_bomb, SCREEN_W, random(30,550), 10, 1.6f);
        debries.push_back( newBomb);
      }
      // Comets spawning
      if( (score >= 300 && random(0,200) == 0) || (settings[SETTING_MEGA] && random(0, 20))){
        debrie newComet( cometImage, sound_asteroid, SCREEN_W, random(30,550), 5, 2.0f);
        debries.push_back( newComet);
      }

      // Powerup spawning
      if( score >= 100 && random(0,3000) == 0){
        powerup newPowerup( powerStar, sound_star, SCREEN_W, random(30,600), 500, 1);
        powerups.push_back( newPowerup);
      }
      if( score >= 100 && random(0,500) == 0){
        powerup newPowerup( powerMagnet[0], sound_magnet, SCREEN_W, random(30,600), 500, 10);
        powerups.push_back( newPowerup);
      }
      if( score >= 200 && random(0,1000) == 0){
        powerup newPowerup( powerMagnet[1], sound_magnet, SCREEN_W, random(30,600), 750, 11);
        powerups.push_back( newPowerup);
      }
      if( score >= 300 && random(0,2000) == 0){
        powerup newPowerup( powerMagnet[2], sound_magnet, SCREEN_W, random(30,600), 1000, 12);
        powerups.push_back( newPowerup);
      }
      if( score >= 500 && random(0,3000) == 0){
        powerup newPowerup( powerMagnet[3], sound_magnet, SCREEN_W, random(30,600), 1500, 13);
        powerups.push_back( newPowerup);
      }
    }

    // Lose scripts
    if( hectar.isOnGround()){
      //Name input
      if( check_highscore( scores, score) && keyListener::lastKeyPressed != -1){
        // Last key pressed
        int newkey = keyListener::lastKeyPressed;

        // Letters
        if( newkey >= KEY_A && newkey <= KEY_Z && edittext.length() < 14){
          iter = edittext.insert(iter, newkey + 96 - ((bool)key[KEY_LSHIFT] * 32));
          iter++;
        }
        // Numbers
        else if( newkey >= KEY_0 && newkey <= KEY_9 && edittext.length() < 14){
          iter = edittext.insert(iter, newkey + 21);
          iter++;
        }
        // Some other, "special" key was pressed, handle it here
        else if( newkey == KEY_DEL && iter != edittext.end()){
          iter = edittext.erase(iter);
        }
        else if( newkey == KEY_BACKSPACE && iter != edittext.begin()){
          iter--;
          iter = edittext.erase(iter);
        }
        else if( newkey == KEY_RIGHT && iter != edittext.end()){
          iter++;
        }
        else if( newkey == KEY_LEFT && iter != edittext.begin()){
          iter--;
        }
      }
      if( key[KEY_ENTER] || (joystick_enabled && joy[0].button[1].b && settings[SETTING_CONTROLMODE] != 1)){
        addScore( scores, score, edittext);
        set_next_state( STATE_MENU);
      }
    }
  }

  // Screenshot
  if( keyListener::keyPressed[KEY_F11] || (joystick_enabled && joy[0].button[3].b && settings[SETTING_CONTROLMODE] != 1)){
    // Count screenshots
  	int screenshotNumber;

  	// Get current number
  	std::ifstream read("screenshots/screenshot.dat");
	  read >> screenshotNumber;
  	read.close();

  	// State new number
  	std::ofstream write("screenshots/screenshot.dat");
	  write << screenshotNumber + 1;
	  write.close();

	  // Save to file
    save_png((std::string("screenshots/screenshot_") + convertIntToString(screenshotNumber).c_str() + std::string(".png")).c_str(), buffer, NULL);

    // Snap sound
    play_sample( sound_snap, 255, 128, 1000, 0);
  }

  //Screen shake
  if( screenshake > 0 && settings[SETTING_SCREENSHAKE] != 0){
    screenshake_x = screenshake_y = random( -(screenshake * settings[SETTING_SCREENSHAKE] + 100 * settings[SETTING_SUPERSHAKE]), screenshake * settings[SETTING_SCREENSHAKE] + 100 * settings[SETTING_SUPERSHAKE]);
    screenshake--;
  }
  if( screenshake <= 0 || !hectar.isAlive())
    screenshake_x = screenshake_y = 0;

  // Random test stuff for devs
  if( settings[SETTING_DEBUG]){
    if(key[KEY_R])score += 10;
    if(key[KEY_E] || joy[0].button[2].b)hectar.addHealth(1);
    if(key[KEY_T])hectar.addHealth(-100);
  }

  // Pause loop code
  if( keyListener::keyPressed[KEY_ESC] || mouseListener::buttonPressed[2] || keyListener::keyPressed[KEY_SPACE] || ((joy[0].button[6].b || joy[0].button[7].b) && joystick_enabled && settings[SETTING_CONTROLMODE] != 1)){
    if( paused){
      paused = false;
      show_mouse( NULL);
    }
    else if( hectar.isAlive()){
      paused = true;
      show_mouse( screen);
    }
  }


  // Pause Menu Scripts
  if( paused){
    // Quit game
    if( mouseListener::buttonPressed[1] && collision( 220, 280, mouse_x, mouse_x, 435, 460, mouse_y, mouse_y))
      set_next_state( STATE_EXIT);

    // Menu
    if( mouseListener::buttonPressed[1] && collision( 300, 430, mouse_x, mouse_x, 435, 460, mouse_y, mouse_y))
      set_next_state( STATE_MENU);

    // Resume
    if( mouseListener::buttonPressed[1] && collision( 470, 540, mouse_x, mouse_x, 435, 460, mouse_y, mouse_y))
      paused = false;
  }
}

// Draw to screen
void game::draw(){
  // Clear buffer
  clear_to_color( buffer, 0x000000);

  // Draw backgrounds and Ground Overlay
  draw_sprite( buffer, space, scroll/6, 0);
  draw_sprite( buffer, space, scroll/6 + SCREEN_W, 0);

  // Draw HUD
  // Info
  textprintf_ex( buffer, orbitron, 10, 2, makecol(255,255,255), -1, "Score:%i", score);
  rectfill( buffer, 10, 65, 10 + (hectar.getHealth() * 1.7), 75, makecol( 255 - hectar.getHealth() * 2.5, 0 + hectar.getHealth() * 2.5, 0));
  textprintf_ex( buffer, orbitron, 10, 27, makecol(255,255,255), -1, "Health:%i", hectar.getHealth());

  // Power up timers
  if( hectar.isInvincible()){
    circlefill( buffer, 45, 105, 20, makecol(255,255,255));
    draw_sprite( buffer, powerStar, 20, 80);
    textprintf_centre_ex( buffer, orbitron, 44, 88, makecol(255,255,255), -1, "%i", hectar.getInvincibleTimer()/5);
    textprintf_centre_ex( buffer, orbitron, 45, 90, makecol(255,0,0), -1, "%i", hectar.getInvincibleTimer()/5);
  }
  if( hectar.isMagnetic()){
    circlefill( buffer, 175, 105, 20, makecol(255,255,255));
    draw_sprite( buffer, powerMagnet[0], 150, 80);
    textprintf_centre_ex( buffer, orbitron, 174, 88, makecol(255,255,255), -1, "%i", hectar.getMagneticTimer()/5);
    textprintf_centre_ex( buffer, orbitron, 175, 90, makecol(255,0,0), -1, "%i", hectar.getMagneticTimer()/5);
  }

  // Draw the debug window
  if( settings[SETTING_DEBUG]){
    draw_sprite(buffer,debug,0,0);
    textprintf_ex(buffer,font,5,25,makecol(255,250,250),-1,"Motion:%4.2f", motion);
    textprintf_ex(buffer,font,5,35,makecol(255,250,250),-1,"Robot X:%4.2f", hectar.getX());
    textprintf_ex(buffer,font,5,45,makecol(255,250,250),-1,"Robot Y:%4.2f", hectar.getY());
    textprintf_ex(buffer,font,5,55,makecol(255,250,250),-1,"Motion:%4.2f", motion);
    textprintf_ex(buffer,font,5,65,makecol(255,250,250),-1,"Invincible:%i", hectar.getInvincibleTimer());

    textprintf_ex(buffer,font,120,25,makecol(255,250,250),-1,"Score:%i", score);
    textprintf_ex(buffer,font,120,35,makecol(255,250,250),-1,"Magnetic:%i", hectar.getMagneticTimer());
    textprintf_ex(buffer,font,120,45,makecol(255,250,250),-1,"Mouse X:%i", mouse_x);
    textprintf_ex(buffer,font,120,55,makecol(255,250,250),-1,"Mouse Y:%i", mouse_y);
    textprintf_ex(buffer,font,120,65,makecol(255,250,250),-1,"Particles On:%i", settings[SETTING_PARTICLE_TYPE]);

    textprintf_ex(buffer,font,245,25,makecol(255,250,250),-1,"Lowest score:%i", atoi(scores[9][1].c_str()));
    textprintf_ex(buffer,font,245,35,makecol(255,250,250),-1,"Theme:%i", themeNumber);
    textprintf_ex(buffer,font,245,45,makecol(255,250,250),-1,"Energys:%i", energys.size());
    textprintf_ex(buffer,font,245,55,makecol(255,250,250),-1,"Debris:%i", debries.size());
    textprintf_ex(buffer,font,245,65,makecol(255,250,250),-1,"Powerups:%i", powerups.size());

    textprintf_ex(buffer,font,360,25,makecol(255,250,250),-1,"Last key:%i", keyListener::lastKeyPressed);
    textprintf_ex(buffer,font,360,35,makecol(255,250,250),-1,"Has highscore:%i", check_highscore( scores, score));
  }

  // Mountain Paralax
  draw_sprite( buffer, space2, (scroll/3) % SCREEN_W, 0);
  draw_sprite( buffer, space2, (scroll/3) % SCREEN_W + SCREEN_W, 0);

  // Ground
  draw_sprite( buffer, groundOverlay, scroll % SCREEN_W, SCREEN_H - 20);
  draw_sprite( buffer, groundOverlay, scroll % SCREEN_W + SCREEN_W, SCREEN_H - 20);

  // Energy
  for( unsigned int i = 0; i < energys.size(); i++)
    energys.at(i).draw(buffer);

  // Powerups
  for( unsigned int i = 0; i < powerups.size(); i++)
    powerups.at(i).draw(buffer);

  // Draw robot
  hectar.draw( buffer);

  // Asteroids
  for( unsigned int i = 0; i < debries.size(); i++)
    debries.at(i).draw(buffer);

  // Ground underlay
  draw_sprite( buffer, groundUnderlay, scroll % SCREEN_W, SCREEN_H - 40);
  draw_sprite( buffer, groundUnderlay, scroll % SCREEN_W + SCREEN_W, SCREEN_H - 40);

  // Robot above asteroids
  hectar.draw_overlay( buffer);

  // Lose scripts
  if( hectar.isOnGround()){
    draw_sprite( buffer, ui_game_end, 0, 0);
    textprintf_ex( buffer, orbitron, 130, 125, makecol(0,0,0), -1, "Final Score: %i", score);
    textprintf_ex( buffer, orbitron, 130, 165, makecol(0,0,0), -1, "Distance Flown: %i ft", stats[STAT_DISTANCE] / 10);
    textprintf_ex( buffer, orbitron, 130, 205, makecol(0,0,0), -1, "Energy Collected: %i", stats[STAT_ENERGY]);
    textprintf_ex( buffer, orbitron, 130, 245, makecol(0,0,0), -1, "Powerups Received: %i", stats[STAT_POWERUPS]);
    textprintf_ex( buffer, orbitron, 130, 285, makecol(0,0,0), -1, "Debris Collided: %i", stats[STAT_DEBRIS]);

    if( check_highscore( scores, score)){
      // Input rectangle
      rectfill( buffer, 120, 388, text_length(orbitron, edittext.c_str()) + 132, 432, makecol( 0, 0, 0));
      rectfill( buffer, 122, 390, text_length(orbitron, edittext.c_str()) + 130, 430, makecol( 255, 255, 255));

      // Output the string to the screen
      textout_ex( buffer, orbitron, edittext.c_str(), 126, 390, makecol(0,0,0), -1);

      // Draw the caret
      vline( buffer, text_length(orbitron, edittext.substr(0, std::distance( edittext.begin(), iter)).c_str()) + 126, 392, 428, makecol(0,0,0));

      // Draw the congrats message
      textprintf_ex( buffer, orbitron, 150, 330, makecol(0,255,0), -1, "New highscore!");
      textprintf_ex( buffer, orbitron, 150, 450, makecol(0,0,0), -1, "Press Enter/   to continue");
      draw_sprite( buffer, ui_b, 370, 450);
    }
    else{
      textprintf_ex( buffer, orbitron, 150, 395, makecol(0,0,0), -1, "Press Enter/   to continue");
      draw_sprite( buffer, ui_b, 370, 395);
    }
  }

  // Pause Menu Scripts
  if( paused){
    // Menu
    draw_sprite( buffer, pauseMenu, 130, 140);

    // Stats
    textprintf_ex( buffer, orbitron_14, 220, 250, makecol(255,250,250), -1, "Distance Flown: %i ft", stats[STAT_DISTANCE] / 10);
    textprintf_ex( buffer, orbitron_14, 220, 280, makecol(255,250,250), -1, "Energy Collected: %i", stats[STAT_ENERGY]);
    textprintf_ex( buffer, orbitron_14, 220, 310, makecol(255,250,250), -1, "Powerups Received: %i", stats[STAT_POWERUPS]);
    textprintf_ex( buffer, orbitron_14, 220, 340, makecol(255,250,250), -1, "Debris Collided: %i", stats[STAT_DEBRIS]);

    // Buttons
    textprintf_ex( buffer, orbitron_14, 220, 445, makecol(0,0,0), -1, "Quit");
    textprintf_ex( buffer, orbitron_14, 300, 445, makecol(0,0,0), -1, "Main Menu");
    textprintf_ex( buffer, orbitron_14, 470, 445, makecol(0,0,0), -1, "Resume");
  }

  // Draw buffer
  draw_sprite( screen, buffer, screenshake_x, screenshake_y);
}
