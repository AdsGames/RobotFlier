#include "bomb.h"

bomb::bomb(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY){
  image[0] = newImage1;
  image[1] = newImage2;
  soundEffect = newSoundEffect;
  x = newX;
  y = newY;
  isDead = false;

  height = image[0] -> h;
  width = image[1] -> w;
}

bomb::~bomb(){

}

void bomb::logic(int newMotion){
  x -= newMotion * 1.3;

  if(collision(x, x + width , robot_x, robot_x + robotWidth, y, y + height, robot_y, robot_y + robotHeight) && !isDead){
		if(!invincible){
      health -= 10;
    }
    if(sound && !invincible){
      play_sample(soundEffect,255,125,1000,0);
    }
  }

  if(isDead){
  	if( particles_on){
	    //Update particles
	    for( int i = 0; i < debris.size(); i++){
	      debris.at(i).logic();
	      debris.at(i).x -= newMotion;
	    }
	  }
  }
  else{
    //Check for death
    dead();
  }
}

bool bomb::dead(){
  if(collision(x, x + width , robot_x, robot_x + robotWidth, y, y + height, robot_y, robot_y + robotHeight)){
  	if(!invincible){
  		isDead = true;
  		debrisCollided +=1;
		}
    if( particles_on){
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
	      particle newParticle( iteratorX + x, iteratorY + y, makecol( 255, random( 0, 255), 0), random(-20,-5), random(5,20), random(-20,-5), random(5,20),0);
	    	debris.push_back( newParticle);
	    }
	  }
  }
  return isDead;
}
bool bomb::offScreen(){
  if(x <= 0 - width){
    return true;
  }
  return false;
}

// Draw
void bomb::draw( BITMAP* tempBitmap){
  if(!isDead){
    if(image[0] != NULL){
      stretch_sprite( tempBitmap, image[0], x, y, width, height);
    }
  }
  else{
  	if( particles_on){
	    for( int i = 0; i < debris.size(); i++){
	      debris.at(i).draw( tempBitmap);
	    }
		}
  }

  if(debugMode){
    rect(tempBitmap, x, y, x + width, y + height, makecol(88, 88, 88));
  }
}

