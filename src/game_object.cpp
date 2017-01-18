#include "game_object.h"

// Constructor
game_object::game_object( BITMAP* newImage, SAMPLE* newSoundEffect, int newX, int newY, int newSize){
  image = newImage;
  soundEffect = newSoundEffect;
  x = newX;
  y = newY;
  isDead = false;

  height = newImage -> h;
  width = newImage -> w;

  damage = 0;
}

// Destructor
game_object::~game_object(){

}

// Updates object logic
void game_object::logic( int newMotion){
  //Update particles
  if( settings[SETTING_PARTICLE_TYPE] != 3){
    for( unsigned int i = 0; i < parts.size(); i++){
      parts.at(i).logic();
      parts.at(i).x -= newMotion;
    }
  }
}

// Has it been hit?
bool game_object::dead(){
  return isDead;
}

// Is the object off screen?
bool game_object::offScreen(){
  if(x <= 0 - width)
    return true;
  return false;
}

// Draw
void game_object::draw( BITMAP* tempBitmap){
  // Draw image unless dead
  if( !isDead){
    if( image != NULL){
      draw_sprite_hw( image, x, y);
    }
  }

  // Draw particles
  if( settings[SETTING_PARTICLE_TYPE] != 3){
    for( unsigned int i = 0; i < parts.size(); i++){
      parts.at(i).draw( screen);
    }
  }

  // Draw bounding box
  if( settings[SETTING_DEBUG] == 1){
    rect( screen, x, y, x + width, y + height, makecol(88, 88, 88));
  }
}

