#include "globals.h"

//Global variables
unsigned int score;
bool invincible;
int screenshake;
int magneticStrength;
int invincibleTimer;
int magneticTimer;

// For stats
int stats[4];

bool joystick_enabled = false;

std::string scores[10][2];
int settings[11];

// Fonts
FONT* orbitron_14;
FONT* orbitron;
