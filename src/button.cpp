#include "button.h"

// Constructor
Button::Button(){
  button_height = 10;
  button_width = 10;

  images[0] = NULL;
  images[1] = NULL;

  enabled = false;
}

// Destructor
Button::~Button(){
  // Destroy bitmaps
  destroy_bitmap( images[0]);
  destroy_bitmap( images[1]);
}

// Set images
void Button::set_images( std::string image1, std::string image2){
  images[0] = load_bitmap( image1.c_str(), NULL);
  images[1] = load_bitmap( image2.c_str(), NULL);

  // Get size from images
  if( images[0] != NULL){
    button_height = images[0] -> h;
    button_width = images[0] -> w;
  }
}

// Check hover state
bool Button::get_hover(){
  if( mouse_x > x && mouse_x < x + button_width && mouse_y > y && mouse_y < y + button_height)
    return true;
  return false;
}

// Reposition button
void Button::set_position( int newX, int newY){
  x = newX;
  y = newY;
}

// Get x
int Button::get_x(){
  return x;
}

// Get y
int Button::get_y(){
  return y;
}

// Draw to tempBitmap
void Button::draw( BITMAP* tempBitmap){
  // Check hover state
  if(get_hover()){
    if( images[1] != NULL)
      draw_sprite(tempBitmap, images[1], x, y);
    else
      rectfill( tempBitmap, x, y, x + 10, y + 10, 0xFF0000);
  }
  else{
    if( images[0] != NULL)
      draw_sprite(tempBitmap, images[0], x, y);
    else
      rectfill( tempBitmap, x, y, x + 10, y + 10, 0xFF0000);
  }
}
