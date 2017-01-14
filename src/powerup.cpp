#include "powerup.h"

// Constructor
powerup::powerup( BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newTimerLength, int newType) : game_object( newImage, newSoundEffect, newX, newY, 0){
  timerLength = newTimerLength;
  type = newType;
}

// Logic loop!
void powerup::logic(int newMotion, robot *ourRobot){
  x -= newMotion;

  if( !isDead && collision( x, x + width , ourRobot -> getX(), ourRobot -> getX() + ourRobot -> getWidth(), y, y + height, ourRobot -> getY(), ourRobot -> getY() + ourRobot -> getHeight())){
    stats[STAT_POWERUPS] += 1;
    if( type == 1)
      ourRobot -> setInvincibleTimer( timerLength);
    else
      ourRobot -> setMagneticTimer( timerLength);

    if( settings[SETTING_SOUND])
      play_sample( soundEffect, 255, 125, 1000, 0);
    isDead = true;
  }
}
