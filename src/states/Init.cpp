#include "Init.h"

// Construct state
init::init() {
  // Title
  al_set_window_title(display, "A.D.S. Games - Robot Flier");

  // Icon
  ALLEGRO_BITMAP* the_icon;
  the_icon = load_bitmap_ex("images/objects/bomb.png");
  al_set_display_icon(display, the_icon);

  // Seed the random number generator with the time
  srand(time(nullptr));
  random(0, 100);

  // Joystick detector
  joystick_enabled = bool(al_get_num_joysticks() > 0);

  // Loads fonts
  orbitron_12 = load_font_ex("fonts/orbitron_ttf.ttf", 12, 0);
  orbitron_18 = load_font_ex("fonts/orbitron_ttf.ttf", 18, 0);
  orbitron_24 = load_font_ex("fonts/orbitron_ttf.ttf", 24, 0);
  orbitron_30 = load_font_ex("fonts/orbitron_ttf.ttf", 30, 0);
  orbitron_36 = load_font_ex("fonts/orbitron_ttf.ttf", 36, 0);

  // Go to menu
  set_next_state(STATE_MENU);
}

// Destruct state
init::~init() {}
