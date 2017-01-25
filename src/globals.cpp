#include "globals.h"

//Global variables
unsigned int score;
int screenshake;

int fps = 0;;
const int SCREEN_W = 800;
const int SCREEN_H = 600;

// Data
int stats[4];
std::string scores[10][2];
int settings[11];

// Is the joystick enabled?
bool joystick_enabled = false;

// Fonts
ALLEGRO_FONT *orbitron_12 = NULL;
ALLEGRO_FONT *orbitron_18 = NULL;
ALLEGRO_FONT *orbitron_24 = NULL;
ALLEGRO_FONT *orbitron_30 = NULL;
ALLEGRO_FONT *orbitron_36 = NULL;

// Current music
ALLEGRO_SAMPLE_ID currentMusic;

// Display
ALLEGRO_DISPLAY *display = NULL;
