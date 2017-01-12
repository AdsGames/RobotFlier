#include "bomb.h"

bomb::bomb( BITMAP *newImage, SAMPLE *newSoundEffect, int newX, int newY) : game_object( newImage, newSoundEffect, newX, newY, 0){
  damage = 10;
}

// Logic
void bomb::logic( int newMotion){
  // Move across screen
  x -= newMotion * 2;

  // Parent logic
  game_object::logic( newMotion);
}

