#include "robot.h"

// Constructor
robot::robot(){

}

robot::robot( float newX, float newY){
  // Robot
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

  // Init vars
  gravity = 1.6;

  speed = 15;
  x = newX;
  y = newY;
  width = 70;
  height = 70;

  health = 100;

  rocket = false;
  onGround = false;
  alive = true;
}

// Destructor
robot::~robot(){

}

// Update
void robot::logic(){
  // Check if you are dead!
  if( health < 1){
    alive = false;
    health = 0;
  }

  // Update robots y position
  y += gravity - speed;

  // Death smoke
  if( settings[SETTING_PARTICLE_TYPE] != 3 && !alive){
    for( int i = 0; i < 800; i++){
      if( random(0,10) == 0){
        int randnum = random(0,255);
        particle newParticle( x + 20, y + 20, makecol( randnum, randnum, randnum), random( -4, -1), random( -5, -3), 1, settings[SETTING_PARTICLE_TYPE]);
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
        int part_color = makecol( 255, random(0,255), 0);
        if( settings[SETTING_CHRISTMAS]){
          int red_or_green = random( 0, 1);
          part_color = makecol( 255 * red_or_green, 255 - red_or_green * 255, 0);
        }
        particle newParticle1( x + 21, y + 55, part_color, random( -2, 2), random( 0, 4), 1, settings[SETTING_PARTICLE_TYPE]);
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
    if( ((key[KEY_W] || key[KEY_UP] || mouse_b & 1) && settings[SETTING_CONTROLMODE] != 3) || ((joy[0].button[0].b || joy[0].button[5].b) && settings[SETTING_CONTROLMODE] != 2)){
      if( settings[SETTING_SOUND] && random( 0, 3) == 1)
        play_sample( sound_flame, 10, 155, 1000, 0);
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
      clear_keybuf();
    }
    else if( y >= 550){
      y = 550;
      onGround = true;
      clear_keybuf();
    }
  }

  // Touching top or bottom
  if( y < 0){
    y = 0;
    speed = 0;
  }
  if( y > 550 && alive){
    speed = 14;
    if( !invincible){
      health -= 5;
      if(settings[SETTING_SOUND])
        play_sample( sound_hitground, 255, 125, 1000, 0);
      screenshake = 30;
    }
  }
}

// Draw
void robot::draw( BITMAP *tempBitmap){
  // Draw robot sprite
  if( alive){
    // Invincible
    if( invincible){
      if( !rocket || (rocket && settings[SETTING_PARTICLE_TYPE] != 3))
        draw_sprite( tempBitmap, robotInvincible, x, y);
      else if( rocket && settings[SETTING_PARTICLE_TYPE] == 3)
        draw_sprite( tempBitmap, robotInvincibleFire, x, y);
    }
    // Standard
    else{
      if( !rocket || (rocket && settings[SETTING_PARTICLE_TYPE] != 3))
        draw_sprite( tempBitmap, main_robot, x, y);
      else if( rocket && settings[SETTING_PARTICLE_TYPE] == 3)
        draw_sprite( tempBitmap, robotFire, x, y);
    }
    // Xmas mode!
    if( settings[SETTING_CHRISTMAS])
      draw_sprite( tempBitmap, christmas_hat, x + 20, y - 12);
  }
  // Death image
  else{
    draw_sprite( tempBitmap,robotDie,x,y);
  }

  // Draw particles
  for( unsigned int i = 0; i < rocketPart.size(); i++)
    rocketPart.at(i).draw( tempBitmap);
  for( unsigned int i = 0; i < smokePart.size(); i++)
    smokePart.at(i).draw( tempBitmap);
}

// Draw overlay
void robot::draw_overlay( BITMAP *tempBitmap){
  if( alive && invincible)
    draw_sprite( tempBitmap, robotInvincibleTop, x, y);
}
