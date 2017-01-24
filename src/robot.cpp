#include "robot.h"

// Constructor
robot::robot(){
  // NULLIFY
  main_robot = NULL;
  robotFire = NULL;
  robotInvincible = NULL;
  robotInvincibleFire = NULL;
  robotInvincibleTop = NULL;
  robotDie = NULL;
  christmas_hat = NULL;
  sound_flame = NULL;
  sound_hitground = NULL;
}

// Constructor
robot::robot( float newX, float newY){
  // NULLIFY
  main_robot = NULL;
  robotFire = NULL;
  robotInvincible = NULL;
  robotInvincibleFire = NULL;
  robotInvincibleTop = NULL;
  robotDie = NULL;
  christmas_hat = NULL;
  sound_flame = NULL;
  sound_hitground = NULL;

  // Init vars
  gravity = 1.6;

  speed = 20;
  x = newX;
  y = newY;
  width = 70;
  height = 70;
  invincibleTimer = 0;
  magneticTimer = 0;

  health = 100;

  rocket = false;
  onGround = false;
  alive = true;
}

// Destructor
robot::~robot(){
  // Clear particles
  rocketPart.clear();
  smokePart.clear();

  // Destroy samples
  al_destroy_sample( sound_flame);
  al_destroy_sample( sound_hitground);

  // Destroy images
  al_destroy_bitmap( main_robot);
  al_destroy_bitmap( robotFire);
  al_destroy_bitmap( robotInvincible);
  al_destroy_bitmap( robotInvincibleFire);
  al_destroy_bitmap( robotInvincibleTop);
  al_destroy_bitmap( robotDie);
  al_destroy_bitmap( christmas_hat);
}

// Load images
void robot::load_resources(){
  // Images
  main_robot = load_bitmap_ex("images/robot/robot.png");
  robotFire = load_bitmap_ex("images/robot/robotfire.png");
  robotInvincible = load_bitmap_ex("images/robot/robotInvincible.png");
  robotInvincibleFire = load_bitmap_ex("images/robot/robotInvincibleFire.png");
  robotInvincibleTop = load_bitmap_ex("images/robot/robotInvincibleTop.png");
  robotDie = load_bitmap_ex("images/robot/robotDie.png");
  christmas_hat = load_bitmap_ex("images/robot/christmas_hat.png");

  // Sounds
  sound_flame = load_sample_ex( "audio/sound_flame.wav");
  sound_hitground = load_sample_ex( "audio/sound_hitground.wav");
}

// Update
void robot::logic(){
  // Check if you are dead!
  if( health < 1){
    alive = false;
    health = 0;
  }

  // Power up timers
  if( invincibleTimer > 0)
    invincibleTimer--;
  if( magneticTimer > 0)
    magneticTimer--;

  // Update robots y position
  y += gravity - speed;

  // Death smoke
  if( settings[SETTING_PARTICLE_TYPE] != 3 && !alive){
    for( int i = 0; i < 800; i++){
      if( random(0,10) == 0){
        int randnum = random(0,255);
        particle newParticle( x + 20, y + 20, al_map_rgb( randnum, randnum, randnum), random( -4, -1), random( -5, -3), 1, settings[SETTING_PARTICLE_TYPE]);
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
  if( settings[SETTING_PARTICLE_TYPE] != 3 && rocket){
    for( int i = 0; i < 800; i++){
      if( random( 0, 10) == 0){
        ALLEGRO_COLOR part_color = al_map_rgb( 255, random(0,255), 0);
        if( settings[SETTING_CHRISTMAS]){
          int red_or_green = random( 0, 1);
          part_color = al_map_rgb( 255 * red_or_green, 255 - red_or_green * 255, 0);
        }
        particle newParticle1( x + 21, y + 55, part_color, random( -2, 2), random( 1, 5), 1, settings[SETTING_PARTICLE_TYPE]);
        particle newParticle2( x + 52, y + 55, part_color, random( -2, 2), random( 0, 4), 1, settings[SETTING_PARTICLE_TYPE]);
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

  // Moving controls
  if( alive){
    //Controls movement up and down
    if( (keyListener::key[ALLEGRO_KEY_W] || keyListener::key[ALLEGRO_KEY_UP] || mouseListener::mouse_button & 1) || joystickListener::button[JOY_XBOX_A] || joystickListener::button[JOY_XBOX_BUMPER_LEFT]){
      if( settings[SETTING_SOUND] && random( 0, 3) == 1)
        al_play_sample( sound_flame, 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
      if( speed < 8){
        rocket = true;
        speed += 0.6;
      }
    }
    //If no keys pressed
    else{
      rocket = false;
      if( speed > -8){
        speed -= 0.6;
      }
    }
  }

  // Dying animation
  if( !alive){
    if( y < 550 && !onGround){
      y += 10;
      speed = 0;
      //clear_keybuf();
    }
    else if( y >= 550){
      y = 550;
      onGround = true;
      //clear_keybuf();
    }
  }

  // Touching top or bottom
  if( y < 0){
    y = 0;
    speed = 0;
  }
  if( y > 550 && alive){
    speed = 14;
    if( invincibleTimer <= 0){
      health -= 5;
      if( settings[SETTING_SOUND])
        al_play_sample( sound_hitground, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
      screenshake = 30;
    }
  }
}

// Draw
void robot::draw(){
  // Draw robot sprite
  if( alive){
    // Invincible
    if( invincibleTimer > 0){
      if( !rocket || (rocket && settings[SETTING_PARTICLE_TYPE] != 3))
        al_draw_bitmap( robotInvincible, x, y, 0);
      else if( rocket && settings[SETTING_PARTICLE_TYPE] == 3)
        al_draw_bitmap( robotInvincibleFire, x, y, 0);
    }
    // Standard
    else{
      if( !rocket || (rocket && settings[SETTING_PARTICLE_TYPE] != 3))
        al_draw_bitmap( main_robot, x, y, 0);
      else if( rocket && settings[SETTING_PARTICLE_TYPE] == 3)
        al_draw_bitmap( robotFire, x, y, 0);
    }
    // Xmas mode!
    if( settings[SETTING_CHRISTMAS])
      al_draw_bitmap( christmas_hat, x + 20, y - 12, 0);
  }
  // Death image
  else{
    al_draw_bitmap( robotDie, x, y, 0);
  }

  // Draw particles
  for( unsigned int i = 0; i < rocketPart.size(); i++)
    rocketPart.at(i).draw();
  for( unsigned int i = 0; i < smokePart.size(); i++)
    smokePart.at(i).draw();
}

// Draw overlay
void robot::draw_overlay(){
  if( alive && invincibleTimer > 0)
    al_draw_bitmap( robotInvincibleTop, x, y, 0);
}
