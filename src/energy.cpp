#include "energy.h"

// Constructor
energy::energy( BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY) : game_object( newImage, newSoundEffect, newX, newY, 0){
}

// Game logic
void energy::logic(int newMotion){
  x -= newMotion;

  if( collision(x, x + width , robot_x, robot_x + robotWidth, y, y + height, robot_y, robot_y + robotHeight) && !isDead){
    score += 5;
    energyCollected += 1;
		if( health < 100){
      health += 1;
    }
    if( settings[SETTING_SOUND]){
      play_sample(soundEffect,255,125,1000,0);
    }
    isDead = true;
  }
}

// Move towards robot
void energy::move_towards( int mov_x, int mov_y, int speed){
  if( mov_y + 2 > y)
    y += speed + Get2dDistance( mov_x, x, mov_y, y)/400;
  if( mov_y - 2 < y)
    y -= speed + Get2dDistance( mov_x, x, mov_y, y)/400;
  if( mov_x + 2 > x)
    x += speed + Get2dDistance( mov_x, x, mov_y, y)/400;
  if( mov_x - 2 < x)
    x -= speed + Get2dDistance( mov_x, x, mov_y, y)/400;
}
