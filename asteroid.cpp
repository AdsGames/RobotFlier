#include "asteroid.h"

asteroid::asteroid(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY, int newSize) {
  image[0] = newImage1;
  image[1] = newImage2;
  soundEffect = newSoundEffect;
  x = newX;
  y = newY;
  isDead = false;

  int size = newSize;
  height = size * 8;
  width = size * 10;
}

asteroid::~asteroid(){

}

void asteroid::logic(int newMotion){
  x -= newMotion;
  int collisionBuffer = height/3;
  if(collision(x, x + width , robot_x + collisionBuffer, robot_x + robotWidth - collisionBuffer, y, y + height, robot_y + collisionBuffer, robot_y + robotHeight - collisionBuffer) && !isDead){
    if(!invincible){
      health -= 5;
    }
    if(sound && !invincible){
      play_sample(soundEffect,255,125,1000,0);
    }
  }

  if(isDead){
  	if( particlesOn){
	    //Update particles
	    for( int i = 0; i < debris.size(); i++){
	      debris.at(i).logic();
	      debris.at(i).x -= newMotion;

	    }
	  }
  }else{
    //Check for death
    dead();
  }
}

bool asteroid::dead(){
  int collisionBuffer = height/3;
  if(collision(x, x + width , robot_x + collisionBuffer, robot_x + robotWidth - collisionBuffer, y, y + height, robot_y + collisionBuffer, robot_y + robotHeight - collisionBuffer)){
    if(!invincible){
  		isDead = true;
  		debrisCollided +=1;
		}
    if( particlesOn){
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
	      particle newParticle( iteratorX + x, iteratorY + y, getpixel(image[0], iteratorX, iteratorY), random(-8,-1), random(1,8), random(-8,-1), random(1,8), PIXEL, 0);
	    	debris.push_back( newParticle);
	    }
	  }
  }
  return isDead;
}
bool asteroid::offScreen(){
  if(x <= 0 - width){
    return true;
  }
  return false;
}

// Draw
void asteroid::draw( BITMAP* tempBitmap){
  if(!isDead){
    if(image[0] != NULL){
      stretch_sprite( tempBitmap, image[0], x, y, width, height);
    }
  }
  else{
  	if( particlesOn){
	    for( int i = 0; i < debris.size(); i++){
	      debris.at(i).draw( tempBitmap);
	    }
		}
  }

  if(debugMode){
    rect(tempBitmap, x, y, x + width, y + height, makecol(88, 88, 88));
  }
}

