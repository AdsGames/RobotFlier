#include "particle.h"

// Constructor
particle::particle(int newX, int newY, int newColor, int newXVel, int newYVel, int newSize, int newType){
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
void particle::draw( BITMAP* tempBitmap){
  if( type == PIXEL){
    putpixel( tempBitmap, x, y, color);
  }
  else if( type == SQUARE){
    rectfill( tempBitmap, x, y, x + size, y + size, color);
  }
  else if( type == CIRCLE){
    circlefill( tempBitmap, x, y, size, color);
  }
}
