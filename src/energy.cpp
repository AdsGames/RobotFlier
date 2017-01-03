#include "energy.h"

// Constructor
energy::energy(BITMAP* newImage1, BITMAP* newImage2, SAMPLE* newSoundEffect, int newX, int newY) : game_object( newImage1, newImage2, newSoundEffect, newX, newY, 0){
}

// Game logic
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

  if( collision(x, x + width , robot_x, robot_x + robotWidth, y, y + height, robot_y, robot_y + robotHeight) && !isDead){
    score += 5;
    energyCollected += 1;
		if( health < 100){
      health += 1;
    }
    if(sound){
      play_sample(soundEffect,255,125,1000,0);
    }
    isDead = true;
  }
}
