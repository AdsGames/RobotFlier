/*
 * Globals
 * Variables that are used by multiple files
 * A.D.S. Games
 */
#ifndef GLOBALS_H
#define GLOBALS_H

// Import libraries
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
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
extern const float MAX_FPS;
extern const int SCREEN_W;
extern const int SCREEN_H;

// Data
extern int stats[4];
extern std::string scores[10][2];
extern int settings[11];

// Is the joystick enabled?
extern bool joystick_enabled;

// Fonts
extern ALLEGRO_FONT *orbitron_12;
extern ALLEGRO_FONT *orbitron_18;
extern ALLEGRO_FONT *orbitron_24;
extern ALLEGRO_FONT *orbitron_30;
extern ALLEGRO_FONT *orbitron_36;

#endif
