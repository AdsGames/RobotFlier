#include "bomb.h"

bomb::bomb( BITMAP *newImage1, BITMAP *newImage2, SAMPLE *newSoundEffect, int newX, int newY) : game_object( newImage1, newImage2, newSoundEffect, newX, newY, 0){
  damage = 10;
}

// Logic
void bomb::logic( int newMotion){
  // Move across screen
  x -= newMotion * 2;

  // Parent logic
  game_object::logic( newMotion);
}

