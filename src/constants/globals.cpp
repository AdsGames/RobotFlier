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
asw::Font orbitron_12 = nullptr;
asw::Font orbitron_18 = nullptr;
asw::Font orbitron_24 = nullptr;
asw::Font orbitron_30 = nullptr;
asw::Font orbitron_36 = nullptr;
