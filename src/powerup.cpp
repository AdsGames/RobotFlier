#include "powerup.h"

// Constructor
powerup::powerup( BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newTimerLength, int newType, int newStrength) : game_object( newImage, newSoundEffect, newX, newY, 0){
  timerLength = newTimerLength;
  type = newType;
  strength = newStrength;
}

// Logic loop!
void powerup::logic(int newMotion){
  x -= newMotion;

  if( collision( x, x + width , robot_x, robot_x + robotWidth, y, y + height, robot_y, robot_y + robotHeight)){
    powerupsCollected += 1;
    if( type == 1){
      invincibleTimer = timerLength;
    }
    else{
      magneticTimer = timerLength;
      magneticStrength = strength;
    }
    if( settings[SETTING_SOUND])
      play_sample( soundEffect, 255, 125, 1000, 0);
  }
}
