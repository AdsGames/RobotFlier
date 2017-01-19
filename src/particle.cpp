#include "particle.h"

// Constructor
particle::particle(int newX, int newY, ALLEGRO_COLOR newColor, int newXVel, int newYVel, int newSize, int newType){
  x = newX;
  y = newY;

  color = newColor;

  size = newSize;

  type = newType;

  velocity_x = newXVel;
  velocity_y = newYVel;
}

// Destructor
particle::~particle(){

}

// Logic
void particle::logic(){
  x += velocity_x;
  y += velocity_y;
}

// Draw
void particle::draw( ALLEGRO_BITMAP* tempBitmap){
  if( type == PIXEL){
    al_put_pixel( x, y, color);
  }
  else if( type == SQUARE){
    al_draw_rectangle( x, y, x + size, y + size, color, 1);
  }
  else if( type == CIRCLE){
    al_draw_circle( x, y, size, color, 1);
  }
}
