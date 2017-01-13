/*
 * Globals
 * Variables that are used by multiple files
 * A.D.S. Games
 */
#ifndef GLOBALS_H
#define GLOBALS_H

// Import libraries
#include <allegro.h>
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

//Variables
extern int settings[11];
extern std::string scores[10][2];

extern int health;
extern unsigned int score;
extern bool invincible;
extern int screenshake;
extern int magneticStrength;
extern int invincibleTimer;
extern int magneticTimer;
extern bool is_high_score;

// For stats
extern int stats[4];
extern bool joystick_enabled;

extern FONT* orbitron_14;
extern FONT* orbitron;

#endif
