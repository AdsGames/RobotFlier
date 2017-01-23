#include "globals.h"

//Global variables
unsigned int score;
int screenshake;

int fps;
const float MAX_FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 600;

// Data
int stats[4];
std::string scores[10][2];
int settings[11];

// Is the joystick enabled?
bool joystick_enabled = false;

// Fonts
ALLEGRO_FONT *orbitron_12;
ALLEGRO_FONT *orbitron_18;
ALLEGRO_FONT *orbitron_24;
ALLEGRO_FONT *orbitron_30;
ALLEGRO_FONT *orbitron_36;
