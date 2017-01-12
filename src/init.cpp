#include "init.h"

// Construct state
init::init(){
  // Get graphics resolution
  int width;
  int height;
  get_desktop_resolution( &width, &height);

  // Set graphics mode
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);

  // Title
  set_window_title( "A.D.S. Games - Robot Flier");

  //Seed the random number generator with the time
  srand(time(NULL));

  //Joystick detector
  joystick_enabled = false;
  if( num_joysticks > 0)
    joystick_enabled = true;

  // Loads fonts
  // Orbitron size 14
  orbitron = load_font_ex("fonts/orbitron.pcx");
  orbitron_14 = load_font_ex("fonts/orbitron_14.pcx");

  // Go to menu
  set_next_state( STATE_MENU);
}

// Destruct state
init::~init(){

}
