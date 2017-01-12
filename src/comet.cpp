#include "comet.h"

// Constructor
comet::comet(BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY) : game_object( newImage, newSoundEffect, newX, newY, 0){
  damage = 3;
}

// Logic
void comet::logic( int newMotion){
  // Move across screen
  x -= newMotion * 2;

  // Parent logic
  game_object::logic( newMotion);
}

