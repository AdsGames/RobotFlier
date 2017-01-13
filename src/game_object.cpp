#include "game_object.h"

game_object::game_object( BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newSize){
  image = newImage;
  soundEffect = newSoundEffect;
  x = newX;
  y = newY;
  isDead = false;

  height = newImage -> h;
  width = newImage -> w;

  damage = 0;
}

game_object::~game_object(){

}

// Updates object logic
void game_object::logic(int newMotion){
  // Allow for some padding (since we use bounding box)
  int collisionBuffer = height/3;

  // Collide with robot
  if( collision(x, x + width , robot_x + collisionBuffer, robot_x + robotWidth - collisionBuffer, y, y + height, robot_y + collisionBuffer, robot_y + robotHeight - collisionBuffer) && !isDead){
    if( !invincible){
      health -= damage;
      screenshake += damage * 4;
    }
    if( settings[SETTING_SOUND] && !invincible){
      play_sample(soundEffect,255,125,1000,0);
    }
  }

  // Destroy
  if( isDead){
    //Update particles
  	if( settings[SETTING_PARTICLE_TYPE] != 3){
	    for( unsigned int i = 0; i < debris.size(); i++){
	      debris.at(i).logic();
	      debris.at(i).x -= newMotion;
	    }
	  }
  }
  //Check for death
  else{
    dead();
  }
}

// Has it been hit?
bool game_object::dead(){
  int collisionBuffer = height/3;
  if( collision( x, x + width , robot_x + collisionBuffer, robot_x + robotWidth - collisionBuffer, y, y + height, robot_y + collisionBuffer, robot_y + robotHeight - collisionBuffer)){
    // When the robot is invincible it goes through
    if( !invincible){
  		isDead = true;
  		debrisCollided +=1;
		}
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
	    	debris.push_back( newParticle);
	    }
	  }
  }
  return isDead;
}

// Is the object off screen?
bool game_object::offScreen(){
  if(x <= 0 - width)
    return true;
  return false;
}

// Draw
void game_object::draw( BITMAP* tempBitmap){
  // Draw image unless dead
  if( !isDead){
    if( image != NULL){
      stretch_sprite( tempBitmap, image, x, y, width, height);
    }
  }
  // Draw particles instead
  else{
  	if( settings[SETTING_PARTICLE_TYPE] != 3){
	    for( unsigned int i = 0; i < debris.size(); i++){
	      debris.at(i).draw( tempBitmap);
	    }
		}
  }

  // Draw bounding box
  if( settings[SETTING_DEBUG] == 1){
    rect( tempBitmap, x, y, x + width, y + height, makecol(88, 88, 88));
  }
}

