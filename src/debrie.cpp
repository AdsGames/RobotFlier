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

  // Parent logic
  game_object::logic( newMotion * motion_multiplier, ourRobot);
}
