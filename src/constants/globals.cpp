#include "globals.h"

// Global variables
int score;
int screenshake;

int fps      = 0;
int SCREEN_W = 800;
int SCREEN_H = 600;

// Data
int stats[4];
int settings[11];

// Is the joystick enabled?
bool joystick_enabled = false;

// Fonts
ALLEGRO_FONT* orbitron_12 = nullptr;
ALLEGRO_FONT* orbitron_18 = nullptr;
ALLEGRO_FONT* orbitron_24 = nullptr;
ALLEGRO_FONT* orbitron_30 = nullptr;
ALLEGRO_FONT* orbitron_36 = nullptr;

// Current music
ALLEGRO_SAMPLE_ID currentMusic;

// Display
ALLEGRO_DISPLAY* display = nullptr;
