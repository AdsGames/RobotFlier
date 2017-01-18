#include "init.h"

// Construct state
init::init(){
  // Get graphics resolution
  int width;
  int height;
  get_desktop_resolution( &width, &height);

  // Set graphics mode
  allegro_gl_clear_settings();
  allegro_gl_set( AGL_DOUBLEBUFFER, 1);
  allegro_gl_set( AGL_WINDOWED, TRUE);
  allegro_gl_set( AGL_Z_DEPTH, 8);
  allegro_gl_set( AGL_COLOR_DEPTH, 32);
  allegro_gl_set( AGL_RENDERMETHOD, 1);
  allegro_gl_set( AGL_SUGGEST, AGL_RENDERMETHOD | AGL_DOUBLEBUFFER | AGL_WINDOWED | AGL_Z_DEPTH | AGL_COLOR_DEPTH);
  set_gfx_mode( GFX_OPENGL, 800, 600, 0, 0);

  // OPEN GL
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// VIEWPORT
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glFrustum( 0, SCREEN_W/2, SCREEN_H/2, 0, 1, 60.0);

  // Switching mode
  set_display_switch_mode( SWITCH_PAUSE);

  // Title
  set_window_title( "A.D.S. Games - Robot Flier");

  //Seed the random number generator with the time
  srand(time(NULL));
  random( 0, 100);

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
