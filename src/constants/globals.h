/*
 * Globals
 * Variables that are used by multiple files
 * A.D.S. Games
 */
#ifndef CONSTANTS_GLOBALS_H
#define CONSTANTS_GLOBALS_H

// Import libraries
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>

#include <string>

#define STAT_DISTANCE 0
#define STAT_ENERGY 1
#define STAT_POWERUPS 2
#define STAT_DEBRIS 3

// Global variables
extern int score;
extern int screenshake;
extern int fps;
extern int SCREEN_W;
extern int SCREEN_H;

// Data
extern int stats[4];

// Is the joystick enabled?
extern bool joystick_enabled;

// Fonts
extern ALLEGRO_FONT* orbitron_12;
extern ALLEGRO_FONT* orbitron_18;
extern ALLEGRO_FONT* orbitron_24;
extern ALLEGRO_FONT* orbitron_30;
extern ALLEGRO_FONT* orbitron_36;

// Current music
extern ALLEGRO_SAMPLE_ID currentMusic;

// Display
extern ALLEGRO_DISPLAY* display;

#endif  // CONSTANTS_GLOBALS_H
