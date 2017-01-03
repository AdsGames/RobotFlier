#include "particle.h"

// Constructor
particle::particle(int newX, int newY, int newColor, int newXMin, int newXMax, int newYMin, int newYMax, int newSize){
  x = newX;
  y = newY;

  particleColor = newColor;
  particleRed = getr(particleColor);
  particleGreen = getg(particleColor);
  particleBlue = getb(particleColor);

  size = newSize;

  xMin = newXMin;
  xMax = newXMax;
  yMin = newYMin;
  yMax = newYMax;
}

// Deconstructor
particle::~particle(){

}

// Logic
void particle::logic(){
  x += random( xMin, xMax);
  y += random( yMin, yMax);

  if(x < 0){
    x = 0;
  }
  if(x > 800){
    x = 800;
  }
  if(y < 0){
    y = 0;
  }
  if(y > 600){
    y = 600;
  }
}

// Draw
void particle::draw( BITMAP* tempBitmap){
  if(particle_type == PIXEL){
    putpixel( tempBitmap, x, y, makecol( particleRed, particleGreen, particleBlue));
  }
  else if(particle_type == SQUARE){
    rectfill( tempBitmap, x, y, x + size, y + size, makecol( particleRed, particleGreen, particleBlue));
  }
  else if(particle_type == CIRCLE){
    circlefill( tempBitmap, x, y, size, makecol( particleRed, particleGreen, particleBlue));
  }
  else if(particle_type == RANDOM){
    switch(random(0,3)){
      case 0:
        putpixel( tempBitmap, x, y, makecol( particleRed, particleGreen, particleBlue));
        break;
      case 1:
        circlefill( tempBitmap, x, y, size, makecol( particleRed, particleGreen, particleBlue));
        break;
      case 2:
        rectfill( tempBitmap, x, y, x + size, y + size, makecol( particleRed, particleGreen, particleBlue));
        break;
    }
  }
}
