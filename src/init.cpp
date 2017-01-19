#include "init.h"

// Construct state
init::init(){
  // Get graphics resolution
  /*int width;
  int height;
  get_desktop_resolution( &width, &height);*/

  // Title
  //set_window_title( "A.D.S. Games - Robot Flier");

  //Seed the random number generator with the time
  srand(time(NULL));
  random( 0, 100);

  //Joystick detector
  joystick_enabled = false;
  if( al_get_num_joysticks > 0)
    joystick_enabled = true;

  // Loads fonts
  // Orbitron size 14
  orbitron_12 = al_load_ttf_font( "fonts/orbitron_ttf.ttf", 12, 0);
  orbitron_18 = al_load_ttf_font( "fonts/orbitron_ttf.ttf", 18, 0);
  orbitron_24 = al_load_ttf_font( "fonts/orbitron_ttf.ttf", 24, 0);
  orbitron_36 = al_load_ttf_font( "fonts/orbitron_ttf.ttf", 36, 0);

  // Go to menu
  set_next_state( STATE_MENU);
}

// Destruct state
init::~init(){

}
