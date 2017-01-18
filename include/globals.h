/*
 * Globals
 * Variables that are used by multiple files
 * A.D.S. Games
 */
#ifndef GLOBALS_H
#define GLOBALS_H

// Import libraries
#include <allegro.h>
#include <alleggl.h>
#include <string>

#define SETTING_PARTICLE_TYPE 0
#define SETTING_SOUND 1
#define SETTING_MUSIC 2
#define SETTING_FULLSCREEN 3
#define SETTING_SCREENSHAKE 4
#define SETTING_CONTROLMODE 5
#define SETTING_DEBUG 6
#define SETTING_MEGA 7
#define SETTING_SUPERSHAKE 8
#define SETTING_CHRISTMAS 9

#define STAT_DISTANCE 0
#define STAT_ENERGY 1
#define STAT_POWERUPS 2
#define STAT_DEBRIS 3

//Global variables
extern unsigned int score;
extern int screenshake;
extern int fps;

// Data
extern int stats[4];
extern std::string scores[10][2];
extern int settings[11];

// Is the joystick enabled?
extern bool joystick_enabled;

// Fonts
extern FONT* orbitron_14;
extern FONT* orbitron;

#endif
