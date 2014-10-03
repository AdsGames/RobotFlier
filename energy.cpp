#include "energy.h"

energy::energy(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY) {
  image[0] = newImage1;
  image[1] = newImage2;
  soundEffect = newSoundEffect;
  x = newX;
  y = newY;
  isDead = false;

  height = image[0] -> h;
  width = image[1] -> w;
}

energy::~energy(){

}

void energy::logic(int newMotion){
  x -= newMotion;

  if(magnetic){
    if(robot_y + 2 > y)
      y += magneticStrength  + Get2dDistance( robot_x, x, robot_y, y)/400;
    if(robot_y - 2 < y)
      y -= magneticStrength  + Get2dDistance( robot_x, x, robot_y, y)/400;
    if(robot_x + 2 > x)
      x += magneticStrength  + Get2dDistance( robot_x, x, robot_y, y)/400;
    if(robot_x - 2 < x)
      x -= magneticStrength  + Get2dDistance( robot_x, x, robot_y, y)/400;
  }

  if(collision(x, x + width , robot_x, robot_x + robotWidth, y, y + height, robot_y, robot_y + robotHeight) && !isDead){
    score += 5;
    energyCollected += 1;
		if( health < 100){
      health += 1;
    }
    if(sound){
      play_sample(soundEffect,255,125,1000,0);
    }
  }

  if(isDead){
    //Update particles
    /*if( particles_on){
	    for( int i = 0; i < debris.size(); i++){
	    	debris.at(i).logic();
	      if(robot_y + robotHeight/2 + 2 > debris.at(i).y)
		      debris.at(i).y += magneticStrength + Get2dDistance( robot_x + robotWidth/2, debris.at(i).x, robot_y + robotHeight/2, debris.at(i).y)/100;
		    if(robot_y + robotHeight/2 - 2 < debris.at(i).y)
		      debris.at(i).y -= magneticStrength + Get2dDistance( robot_x + robotWidth/2, debris.at(i).x, robot_y + robotHeight/2, debris.at(i).y)/100;
		    if(robot_x + robotWidth/2 + 2 > debris.at(i).x)
		      debris.at(i).x += magneticStrength + newMotion + Get2dDistance( robot_x + robotWidth/2, debris.at(i).x, robot_y + robotHeight/2, debris.at(i).y)/100;
		    if(robot_x + robotWidth/2 - 2 < debris.at(i).x)
		      debris.at(i).x -= magneticStrength + Get2dDistance( robot_x + robotWidth/2, debris.at(i).x, robot_y + robotHeight/2, debris.at(i).y)/100;
	    }
	  }*/
  }
  else{
    //Check for death
    dead();
  }
}

bool energy::dead(){
  if(collision(x, x + width , robot_x, robot_x + robotWidth, y, y + height, robot_y, robot_y + robotHeight)){
    isDead = true;
    /*if( particles_on){
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
	      particle newParticle( iteratorX + x, iteratorY + y, getpixel(image[0], iteratorX, iteratorY), random(-6,-1), random(1,6), random(-6,-1), random(1,6), PIXEL, 0);
	    	debris.push_back( newParticle);
	    }
	  }*/
  }
  return isDead;
}
bool energy::offScreen(){
  if(x <= 0 - width){
    return true;
  }
  return false;
}

// Draw
void energy::draw( BITMAP* tempBitmap){
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

