#include "game_object.h"

// Constructor
game_object::game_object( ALLEGRO_BITMAP* newImage, ALLEGRO_SAMPLE* newSoundEffect, int newX, int newY, int newSize){
  image = newImage;
  soundEffect = newSoundEffect;
  x = newX;
  y = newY;
  isDead = false;

  height = al_get_bitmap_height(newImage);
  width = al_get_bitmap_width(newImage);

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
void game_object::draw(){
  // Draw image unless dead
  if( !isDead){
    if( image != NULL){
      al_draw_scaled_bitmap( image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), x, y, width, height, 0);
    }
  }

  // Draw particles
  if( settings[SETTING_PARTICLE_TYPE] != 3){
    for( unsigned int i = 0; i < parts.size(); i++){
      parts.at(i).draw();
    }
  }

  // Draw bounding box
  if( settings[SETTING_DEBUG] == 1){
    al_draw_rectangle( x, y, x + width, y + height, al_map_rgb(88, 88, 88), 1);
  }
}

