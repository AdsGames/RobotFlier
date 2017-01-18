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
  // SET ALLEGRO GL
  allegro_gl_set_allegro_mode();

  // Intro screen
  fade_in( img_intro, 16);
  rest( 1000);
  fade_out( 16);

  // UNSET ALLEGRO GL
  allegro_gl_unset_allegro_mode();

  // Go to menu
  set_next_state( STATE_MENU);
}
