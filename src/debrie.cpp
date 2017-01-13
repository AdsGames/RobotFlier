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
  int collisionBuffer = height/3;

  // Collide with robot
  if( !isDead && collision(x, x + width , ourRobot -> getX() + collisionBuffer, ourRobot -> getX() + ourRobot -> getWidth() - collisionBuffer, y, y + height, ourRobot -> getY() + collisionBuffer, ourRobot -> getY() + ourRobot -> getHeight() - collisionBuffer) && !isDead){
    // Hurt robot
    ourRobot -> addHealth( -damage);

    // Shake it up
    screenshake += damage * 4;

    // Play sound
    if( settings[SETTING_SOUND] && !(invincibleTimer > 0))
      play_sample(soundEffect,255,125,1000,0);

    // Get hit
    isDead = true;
    stats[STAT_DEBRIS] += 1;

		// Make particles
    if( settings[SETTING_PARTICLE_TYPE] != 3){
	    int iteratorX = 0;
	    int iteratorY = 0;
	    for(int i = 0; i < width * height; i++){
	      if(iteratorX < width - 1){
	        iteratorX ++;
	      }
	      else{
	        iteratorX = 0;
	        iteratorY ++;
	      }
	      particle newParticle( iteratorX + x, iteratorY + y, getpixel(image, iteratorX, iteratorY), random( -8, 8), random( -8, 8), 0, settings[SETTING_PARTICLE_TYPE]);
	    	parts.push_back( newParticle);
	    }
	  }
  }

  // Parent logic
  game_object::logic( newMotion);
}
