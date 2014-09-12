#include "powerup.h"

powerup::powerup(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY, int newTimerLength, int newType, int newStrength){ 
  image[0] = newImage1;
  image[1] = newImage2;
  soundEffect = newSoundEffect;
  x = newX;
  y = newY;
  
  timerLength = newTimerLength;
  type = newType;
  strength = newStrength;
  
  height = image[0] -> h;
  width = image[1] -> w;
}

powerup::~powerup(){
  
}

void powerup::logic(int newMotion){
  x -= newMotion;
  
  if(collision(x, x + width , robotX, robotX + robotWidth, y, y + height, robotY, robotY + robotHeight)){  
    powerupsCollected += 1;
    if(type == 1){
      invincibleTimer = timerLength; 
    }           
    else{
      magneticTimer = timerLength;
      magneticStrength = strength;
    }
    if(sound)
      play_sample(soundEffect,255,125,1000,0);
  }
}

bool powerup::dead(){
  if(x <= 0 - width || collision(x, x + width , robotX, robotX + robotWidth, y, y + height, robotY, robotY + robotHeight)){
    return true;
  }
  return false;
}

// Draw
void powerup::draw( BITMAP* tempBitmap){
  if(image[0] != NULL){
    stretch_sprite( tempBitmap, image[0], x, y, width, height);
  }
  
  if(debugMode){
    rect(tempBitmap, x, y, x + width, y + height, makecol(88, 88, 88));
  }
}

