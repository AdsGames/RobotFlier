#include "asteroid.h"

// Constructor
asteroid::asteroid(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY, int newSize) : game_object( newImage1, newImage2, newSoundEffect, newX, newY, newSize){
  height = newSize * 8;
  width = newSize * 10;
  damage = 5;
}

// Logic
void asteroid::logic( int newMotion){
  // Move across screen
  x -= newMotion;

  // Parent logic
  game_object::logic( newMotion);
}
