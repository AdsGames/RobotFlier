#include "game.h"

// Constructor
game::game(){
  //Set the scores to the scores[i][j] array so the endgame screen can check the array if its the high score or not
  updateScores();

  // Init vars

  gravity = 1.6;
  motion = 5;
  speed = 15;
  scroll = 0;
  groundScroll = 0;
  themeNumber = 0;
  screenshake_x = 0;
  screenshake_y = 0;
  screenshake = 0;
  robot_x = 0;
  robot_y = 0;

  // Decare booleans
  rocket = false;
  paused = false;
  alive = true;
  onGround = false;

  edittext = "Player";
  iter = edittext.end();

  magnetic = false;
  invincible = false;
  score = 0;
  health = 100;
  robot_distance = 0;
  robot_x = 80;
  robot_y = 300;
  magneticStrength = 0;
  invincibleTimer = 0;
  magneticTimer = 0;

  // Sets the level to 1
  changeTheme( 1);

  // Create buffer
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  // Sounds
  sound_bomb = load_sample_ex( "audio/sound_bomb.wav");
  sound_orb = load_sample_ex("audio/sound_orb.wav");
  sound_asteroid = load_sample_ex( "audio/sound_asteroid.wav");
  magnetSound = load_sample_ex( "audio/magnetSound.wav");
  sound_star = load_sample_ex( "audio/sound_star.wav");
  sound_flame = load_sample_ex( "audio/sound_flame.wav");
  sound_hitground = load_sample_ex( "audio/sound_hitground.wav");

  // Images
  robot = load_bitmap_ex("images/robot/robot.png");
  robotFire = load_bitmap_ex("images/robot/robotfire.png");
  robotInvincible = load_bitmap_ex("images/robot/robotInvincible.png");
  robotInvincibleFire = load_bitmap_ex("images/robot/robotInvincibleFire.png");
  robotInvincibleTop = load_bitmap_ex("images/robot/robotInvincibleTop.png");
  robotDie = load_bitmap_ex("images/robot/robotDie.png");
  powerStar = load_bitmap_ex("images/powerStar.png");
  powerMagnet[0] = load_bitmap_ex("images/powerMagnet.png");
  powerMagnet[1] = load_bitmap_ex("images/powerMagnetTwo.png");
  powerMagnet[2] = load_bitmap_ex("images/powerMagnetThree.png");
  powerMagnet[3] = load_bitmap_ex("images/powerMagnetFour.png");
  pauseMenu = load_bitmap_ex( "images/gui/pauseMenu.png");
  cometImage = load_bitmap_ex("images/comet.png");
  ui_game_end = load_bitmap_ex( "images/gui/ui_game_end.png");
  ui_a = load_bitmap_ex("images/gui/ui_a.png");
  ui_b = load_bitmap_ex("images/gui/ui_b.png");
  space = load_bitmap_ex( "images/backgrounds/space.png");
  debug = load_bitmap_ex( "images/gui/debug.png");

  if( settings[SETTING_CHRISTMAS]){
    energyImage = load_bitmap_ex("images/energy_christmas.png");
    bombImage = load_bitmap_ex("images/bomb_christmas.png");
  }
  else{
    energyImage = load_bitmap_ex("images/energy.png");
    bombImage = load_bitmap_ex("images/bomb.png");
  }

  christmas_hat = load_bitmap_ex("images/christmas_hat.png");

  // Mouse
  enable_hardware_cursor();
  select_mouse_cursor( MOUSE_CURSOR_ARROW);
  show_mouse( NULL);
}

// Destructor
game::~game(){

}

// Themes
void game::changeTheme( int NewThemeNumber){
	std::string themeName;
	srand(time(NULL));

	if(NewThemeNumber == 0)
		themeName = "moon";
	else if(NewThemeNumber == 1)
		themeName = "mars";
	else if(NewThemeNumber == 2)
		themeName = "sun";
	else if(NewThemeNumber == 3)
		themeName = "dark";
	themeNumber = NewThemeNumber;

  // Load all ground images
  for( int i = 0; i < 12; i++){
    ground[i] = load_bitmap_ex( "images/ground/ground" + convertInt(i + 1) + "_" + themeName + ".png");
  }

  // Other theme images
  groundOverlay = load_bitmap_ex( "images/ground/groundOverlay_" + themeName + ".png");
  space2 = load_bitmap_ex( "images/ground/paralax_" + themeName + ".png");

  if( settings[SETTING_CHRISTMAS])
    asteroidImage = load_bitmap_ex("images/asteroid_christmas.png");
  else
    asteroidImage = load_bitmap_ex( "images/asteroid_" + themeName + ".png");

  // Setup ground pieces
  for(int i = 0; i < 13; i++){
    groundPieces[i].x = i * 70;
    groundPieces[i].y = 530;
    groundPieces[i].groundImage = ground[random(0,11)];
  }
}

// Update logic of game
void game::update(){
  // Actual game stuff
  if( !paused){
    // Update robots y position
    robot_y += gravity - speed;

    // Changes speed
    motion = ((score/36) + 3);

    // Check if you are dead!
    if( health < 1){
      alive = false;
      health = 0;
    }

    // No negative scores
    if( score < 0)
      score = 0;

    // Scroll ground
    if( !onGround && motion != 0){
      groundScroll -= motion;
    }
    if( groundScroll < -SCREEN_W)
      groundScroll = 0;

    // Scrolls background
    if( (alive && motion != 0) || (!alive && !onGround))
      scroll--;
    if( scroll + SCREEN_W <= 0)
     scroll = 0;

    // Moving controls
    if( alive){
      // Add to distance travelled
      robot_distance += motion;

      //Controls movement up and down
      if( ((key[KEY_W] || key[KEY_UP] || mouse_b & 1) && settings[SETTING_CONTROLMODE] != 3) || ((joy[0].button[0].b || joy[0].button[5].b) && settings[SETTING_CONTROLMODE] != 2)){
        if( settings[SETTING_SOUND] && random( 0, 3) == 1)
          play_sample( sound_flame, 10, 155, 1000, 0);
        if( speed < 8){
          rocket = false;
          speed += 0.6;
        }
      }
      //If no keys pressed
      else{
        rocket = true;
        if( speed > -8){
          speed -= 0.6;
        }
      }
    }

    // Lose scripts
    if( onGround){
      //Name input
      check_highscore();
      if( is_high_score){
        if(keypressed()){
          int  newkey   = readkey();
          char ASCII    = newkey & 0xff;
          char scancode = newkey >> 8;

          // A character key was pressed; add it to the string
          if( ASCII >= 32 && ASCII <= 126 && edittext.length() < 14 && scancode != KEY_SPACE){
            iter = edittext.insert(iter, ASCII);
            iter++;
          }
          // Some other, "special" key was pressed; handle it here
          else{
            if(scancode == KEY_DEL){
              if(iter != edittext.end()){
                iter = edittext.erase(iter);
              }
            }
            if(scancode == KEY_BACKSPACE){
              if(iter != edittext.begin()){
                iter--;
                iter = edittext.erase(iter);
              }
            }
            if(scancode == KEY_RIGHT){
              if(iter != edittext.end()){
                iter++;
              }
            }
            if(scancode == KEY_LEFT){
              if(iter != edittext.begin()){
                iter--;
              }
            }
          }
        }
        if(key[KEY_ENTER] || (joy[0].button[1].b && settings[SETTING_CONTROLMODE] != 2)){
          addScore(edittext);
        }
      }
      else if( key[KEY_ENTER] || (joy[0].button[1].b && settings[SETTING_CONTROLMODE]!=2)){
        addScore(edittext);
        set_next_state( STATE_MENU);
      }
    }

    // Change theme
    if( score > 199 && themeNumber == 0)
      changeTheme(1);
    else if( score > 399 && score < 600 && themeNumber == 1)
      changeTheme(2);
    else if( score > 600 && themeNumber == 2)
      changeTheme(3);

    // Dying animation
    if( !alive){
      if( robot_y < 550 && !onGround){
        robot_y += 10;
        speed = 0;
        clear_keybuf();
      }
      else if( robot_y >= 550){
        robot_y = 550;
        motion = 0;
        onGround = true;
        clear_keybuf();
      }
    }

    // Touching top or bottom
    if( robot_y < 0){
      robot_y = 0;
      speed = 0;
    }
    if( robot_y > 550 && alive){
      speed = 14;
      if( !invincible){
        health -= 5;
        if(settings[SETTING_SOUND])
          play_sample( sound_hitground, 255, 125, 1000, 0);
        screenshake = 30;
      }
    }

    // Power up timers
    if( invincibleTimer > 0)
      invincibleTimer--;
    invincible = invincibleTimer > 0;

    if( magneticTimer > 0)
      magneticTimer--;
    magnetic = magneticTimer > 0;

    // Energy
    for( unsigned int i = 0; i < energys.size(); i++){
      energys.at(i).logic(motion);
      // Magnet
      if( magnetic){
        energys.at(i).move_towards( robot_x + robotWidth/2, robot_y + robotHeight/2, magneticStrength);
      }
      if( energys.at(i).offScreen()){
        energys.erase(energys.begin() + i);
        i--;
      }
    }

    // Asteroids
    for( unsigned int i = 0; i < asteroids.size(); i++){
      asteroids.at(i).logic(motion);
      if( asteroids.at(i).offScreen()){
        asteroids.erase(asteroids.begin() + i);
        i--;
      }
    }

    // Bombs
    for( unsigned int i = 0; i < bombs.size(); i++){
      bombs.at(i).logic(motion);
      if(bombs.at(i).offScreen()){
        bombs.erase(bombs.begin() + i);
        i--;
      }
    }

    // Comets
    for( unsigned int i = 0; i < comets.size(); i++){
      comets.at(i).logic(motion);
      if(comets.at(i).offScreen()){
        comets.erase(comets.begin() + i);
        i--;
      }
    }

    // Powerups
    for( unsigned int i = 0; i < powerups.size(); i++){
      powerups.at(i).logic(motion);
      if(powerups.at(i).dead()){
        powerups.erase(powerups.begin() + i);
        i--;
      }
    }

    // Spawning
    if( alive){
      // Energy ball spawning
      if( random(0,50) == 0 || (settings[SETTING_MEGA] && random(0, 20))){
        energy newEnergyBall( energyImage, sound_orb, SCREEN_W, random(30,550));
        energys.push_back( newEnergyBall);
      }
      // Asteroids spawning
      if( (score > 100 && random(0,50) == 0) || (settings[SETTING_MEGA] && random(0, 20))){
        asteroid newAsteroid( asteroidImage, sound_asteroid, SCREEN_W, random(30,550), random(4,20));
        asteroids.push_back( newAsteroid);
      }
      // Bomb spawning
      if( (score > 200 && random(0,80) == 0) || (settings[SETTING_MEGA] && random(0, 20))){
        bomb newBomb( bombImage, sound_bomb, SCREEN_W, random(30,550));
        bombs.push_back( newBomb);
      }
      // Comets spawning
      if( (score > 300 && random(0,200) == 0) || (settings[SETTING_MEGA] && random(0, 20))){
        comet newComet( cometImage, sound_asteroid, SCREEN_W, random(30,550));
        comets.push_back( newComet);
      }
      // Powerup spawning
      if( score > 100 && random(0,3000) == 0){
        powerup newPowerup( powerStar, sound_star, SCREEN_W, random(30,600), 500, 1, 0);
        powerups.push_back( newPowerup);
      }
      if( score > 100 && random(0,500) == 0){
        powerup newPowerup( powerMagnet[0], magnetSound, SCREEN_W, random(30,600), 500, 10, 1);
        powerups.push_back( newPowerup);
      }
      if( score > 200 && random(0,1000) == 0){
        powerup newPowerup( powerMagnet[1], magnetSound, SCREEN_W, random(30,600), 500, 11, 2);
        powerups.push_back( newPowerup);
      }
      if( score > 300 && random(0,2000) == 0){
        powerup newPowerup( powerMagnet[2], magnetSound, SCREEN_W, random(30,600), 500, 12, 3);
        powerups.push_back( newPowerup);
      }
      if( score > 500 && random(0,3000) == 0){
        powerup newPowerup( powerMagnet[3], magnetSound, SCREEN_W, random(30,600), 500, 13, 4);
        powerups.push_back( newPowerup);
      }
    }

    // Move the ground
    for( int i = 0; i < 13; i++){
      groundPieces[i].x -= motion;
      if(groundPieces[i].x <= -70){
        groundPieces[i].x = 840 + (groundPieces[i].x + 70);
      }
    }

    // Death smoke
    if( settings[SETTING_PARTICLE_TYPE] != 3 && !alive){
      for( int i = 0; i < 800; i++){
        if( random(0,10) == 0){
          int randnum = random(0,255);
          particle newParticle( robot_x + 20, robot_y + 20, makecol( randnum, randnum, randnum), random( -4, -1), random( -5, -3), 1, settings[SETTING_PARTICLE_TYPE]);
          smokePart.push_back( newParticle);
        }
      }
    }
    for( unsigned int i = 0; i < smokePart.size(); i++){
      smokePart.at(i).logic();
      if( random(0,10) == 0){
        smokePart.erase( smokePart.begin() + i);
      }
    }

    // Rocket particles
    if( settings[SETTING_PARTICLE_TYPE] != 3 && !rocket){
      for( int i = 0; i < 800; i++){
        if( random( 0, 10) == 0){
          int part_color = makecol( 255, random(0,255), 0);
          if( settings[SETTING_CHRISTMAS]){
            int red_or_green = random( 0, 1);
            part_color = makecol( 255 * red_or_green, 255 - red_or_green * 255, 0);
          }
          particle newParticle1( robot_x + 21, robot_y + 55, part_color, random( -2, 2), random( 0, 4), 1, settings[SETTING_PARTICLE_TYPE]);
          particle newParticle2( robot_x + 52, robot_y + 55, part_color, random( -2, 2), random( 0, 4), 1, settings[SETTING_PARTICLE_TYPE]);
          rocketPart.push_back( newParticle1);
          rocketPart.push_back( newParticle2);
        }
      }
    }
    for( unsigned int i = 0; i < rocketPart.size(); i++){
      rocketPart.at(i).logic();
      if( random( 0, 2) == 0){
        rocketPart.erase( rocketPart.begin() + i);
      }
    }
  }

  // Random test stuff for devs
  if( settings[SETTING_DEBUG]){
    if(key[KEY_I])score = score + 500;
    if(key[KEY_U])score = score + 50;
    if(key[KEY_Q])health = health - 1;
    if(key[KEY_E])health = 0;
    if(key[KEY_Y])robot_distance = robot_distance + 500;
    if(key[KEY_T])score = score - 2;
    if(key[KEY_R] || joy[0].button[2].b)health = 100;
  }

  // Pause loop code
  if( keyListener::keyPressed[KEY_ESC] || keyListener::keyPressed[KEY_P] || mouseListener::buttonPressed[2] & 2 || keyListener::keyPressed[KEY_SPACE] || keyListener::keyPressed[KEY_ENTER] ||
     ((joy[0].button[6].b || joy[0].button[7].b) && settings[SETTING_CONTROLMODE] != 2)){
    if( paused){
      paused = false;
      show_mouse( NULL);
    }
    else if( alive){
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
  draw_sprite( buffer, space, scroll, 0);
  draw_sprite( buffer, space, scroll + SCREEN_W, 0);

  // Mountain Paralax
  draw_sprite( buffer, space2, (scroll * 2) % SCREEN_W, 0);
  draw_sprite( buffer, space2, (scroll * 2) % SCREEN_W + SCREEN_W, 0);

  // Ground
  for( int i = 0; i < 2400; i += 800)
    draw_sprite( buffer, groundOverlay, groundScroll + i, 580);

  // Draw HUD
  if( alive){
    // Info
    textprintf_ex( buffer, orbitron, 10, 2, makecol(255,255,255), -1, "Score:%i", score);
    rectfill( buffer, 10, 65, 10 + (health * 1.7), 75, makecol( 255 - health * 2.5, 0 + health * 2.5, 0));
    textprintf_ex( buffer, orbitron, 10, 27, makecol(255,255,255), -1, "Health:%i", health);

    // Power up timers
    if( invincibleTimer > 0){
      circlefill( buffer, 45, 105, 20, makecol(255,255,255));
      draw_sprite( buffer, powerStar, 20, 80);
      textprintf_centre_ex( buffer, orbitron, 44, 88, makecol(255,255,255), -1, "%i", invincibleTimer/5);
      textprintf_centre_ex( buffer, orbitron, 45, 90, makecol(255,0,0), -1, "%i", invincibleTimer/5);
    }
    if( magneticTimer > 0){
      circlefill( buffer, 175, 105, 20, makecol(255,255,255));
      draw_sprite( buffer, powerMagnet[0], 150, 80);
      textprintf_centre_ex( buffer, orbitron, 174, 88, makecol(255,255,255), -1, "%i", magneticTimer/5);
      textprintf_centre_ex( buffer, orbitron, 175, 90, makecol(255,0,0), -1, "%i", magneticTimer/5);
    }
  }

  // Draw particles
  if( settings[SETTING_PARTICLE_TYPE] != 3){
    for( unsigned int i = 0; i < rocketPart.size(); i++){
      rocketPart.at(i).draw( buffer);
    }
    for( unsigned int i = 0; i < smokePart.size(); i++){
      smokePart.at(i).draw( buffer);
    }
  }

  // Energy
  for( unsigned int i = 0; i < energys.size(); i++)
    energys.at(i).draw(buffer);

  // Asteroids
  for( unsigned int i = 0; i < asteroids.size(); i++)
    asteroids.at(i).draw(buffer);

  // Bombs
  for( unsigned int i = 0; i < bombs.size(); i++)
    bombs.at(i).draw(buffer);

  // Comets
  for( unsigned int i = 0; i < comets.size(); i++)
    comets.at(i).draw(buffer);

  // Powerups
  for( unsigned int i = 0; i < powerups.size(); i++)
    powerups.at(i).draw(buffer);

  // Draw robot sprite
  if( alive){
    // Invincible
    if( invincible){
      if( rocket || (!rocket && settings[SETTING_PARTICLE_TYPE] != 3))
        draw_sprite( buffer, robotInvincible, robot_x, robot_y);
      else if( !rocket && settings[SETTING_PARTICLE_TYPE] == 3)
        draw_sprite( buffer, robotInvincibleFire, robot_x, robot_y);
      draw_sprite( buffer, robotInvincibleTop, robot_x, robot_y);
    }
    // Standard
    else{
      if( rocket || (!rocket && settings[SETTING_PARTICLE_TYPE] != 3))
        draw_sprite( buffer, robot, robot_x, robot_y);
      else if( !rocket && settings[SETTING_PARTICLE_TYPE] == 3)
        draw_sprite( buffer, robotFire, robot_x, robot_y);
    }
    // Xmas mode!
    if( settings[SETTING_CHRISTMAS])
      draw_sprite( buffer, christmas_hat, robot_x + 20, robot_y - 12);
  }
  // Death image
  else{
    draw_sprite( buffer,robotDie,robot_x,robot_y);
  }

  // Draw the scrolling ground
  for( int i = 0; i < 13; i++)
    draw_sprite( buffer, groundPieces[i].groundImage, groundPieces[i].x, groundPieces[i].y);

  // Lose scripts
  if( onGround){
    draw_sprite( buffer, ui_game_end, 0, 0);
    textprintf_ex( buffer, orbitron, 130, 125, makecol(0,0,0), -1, "Final Score: %i", score);
    textprintf_ex( buffer, orbitron, 130, 165, makecol(0,0,0), -1, "Distance Travelled: %i", robot_distance/10);
    textprintf_ex( buffer, orbitron, 130, 205, makecol(0,0,0), -1, "Energy Collected: %i", energyCollected);
    textprintf_ex( buffer, orbitron, 130, 245, makecol(0,0,0), -1, "Powerups Received: %i", powerupsCollected);
    textprintf_ex( buffer, orbitron, 130, 285, makecol(0,0,0), -1, "Debris Collided: %i", debrisCollided);

    if( is_high_score){
      // Input rectangle
      rectfill( buffer, 120, 388, text_length(orbitron, edittext.c_str()) + 132, 432, makecol(0,0,0));
      rectfill( buffer, 122, 390, text_length(orbitron, edittext.c_str()) + 130, 430, makecol(255,255,255));

      // Output the string to the screen
      textout_ex( buffer, orbitron, edittext.c_str(), 126, 390, makecol(0,0,0), -1);

      // Draw the caret
      vline( buffer, text_length(orbitron, edittext.c_str()) + 126, 392, 428, makecol(0,0,0));

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
    textprintf_ex( buffer, orbitron_14, 220, 250, makecol(255,250,250), -1, "Distance Flown: %i ft", robot_distance / 25);
    textprintf_ex( buffer, orbitron_14, 220, 280, makecol(255,250,250), -1, "Energy Collected: %i", energyCollected);
    textprintf_ex( buffer, orbitron_14, 220, 310, makecol(255,250,250), -1, "Powerups Received: %i", powerupsCollected);
    textprintf_ex( buffer, orbitron_14, 220, 340, makecol(255,250,250), -1, "Debris Collided: %i", debrisCollided);

    // Buttons
    textprintf_ex( buffer, orbitron_14, 220, 445, makecol(0,0,0), -1, "Quit");
    textprintf_ex( buffer, orbitron_14, 300, 445, makecol(0,0,0), -1, "Main Menu");
    textprintf_ex( buffer, orbitron_14, 470, 445, makecol(0,0,0), -1, "Resume");
  }

  // Draw buffer
  draw_sprite( screen, buffer, 0, 0);
}
