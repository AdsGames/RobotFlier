#include "debrie.h"

// Constructor
debrie::debrie(BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newDamage, float newMotionMultiplier, int newSize) : game_object( newImage, newSoundEffect, newX, newY, newSize){
  if( newSize != -1){
    height = newSize * 8;
    width = newSize * 10;
  }
  motion_multiplier = newMotionMultiplier;
  damage = newDamage;
}

// Logic
void debrie::logic( int newMotion, robot *ourRobot){
  // Move across screen
  x -= newMotion * motion_multiplier;

  // Allow for some padding (since we use bounding box)
  int collisionBuffer = height / 3;

  // Collide with robot
  if( !isDead && !ourRobot -> isInvincible() && collision( x, x + width , ourRobot -> getX() + collisionBuffer, ourRobot -> getX() + ourRobot -> getWidth() - collisionBuffer, y, y + height, ourRobot -> getY() + collisionBuffer, ourRobot -> getY() + ourRobot -> getHeight() - collisionBuffer) && !isDead){
    // Hurt robot
    ourRobot -> addHealth( -damage);

    // Shake it up
    screenshake += damage * 4;

    // Play sound
    if( settings[SETTING_SOUND])
      play_sample(soundEffect,255,125,1000,0);

    // Get hit
    isDead = true;
    stats[STAT_DEBRIS] += 1;

		// Make particles
    if( settings[SETTING_PARTICLE_TYPE] != 3){
      int sampling_size = 5;
      for( int i = 0; i < (image -> w - sampling_size); i += sampling_size){
        for( int t = 0; t < (image -> h - sampling_size); t += sampling_size){
          particle newParticle( i + x, t + y, getpixel(image, i, t), random( -8, 8), random( -8, 8), 1, settings[SETTING_PARTICLE_TYPE]);
          parts.push_back( newParticle);
        }
      }
	  }
  }

  // Parent logic
  game_object::logic( newMotion);
}
