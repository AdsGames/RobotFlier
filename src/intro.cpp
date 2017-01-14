#include "intro.h"

// Construct state
intro::intro(){
  // Load intro image
  img_intro = load_bitmap_ex("images/backgrounds/intro.png");
}

// Destruct state
intro::~intro(){
  // Clen up
  destroy_bitmap( img_intro);
}

// Update (goto menu!)
void intro::update(){
  // Intro screen
  fade_in( img_intro, 16);
  rest( 1000);
  fade_out( 16);

  // Go to menu
  set_next_state( STATE_MENU);
}
