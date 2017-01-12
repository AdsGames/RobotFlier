/*
 * Globals
 * Variables that are used by multiple files
 * A.D.S. Games
 */
#ifndef GLOBALS_H
#define GLOBALS_H

// Import libraries
#include <allegro.h>
#include <alpng.h>
#include <time.h>
#include <vector>
#include <fmod/fmod.h>
#include <fmod/fmod_errors.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>

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

using namespace std;

//Variables
extern int settings[11];
extern std::string scores[10][2];
extern bool is_high_score;

extern bool joy_buttonpressed();
extern void write_settings();
extern void read_settings();
extern std::string convertInt( int number);
extern int convertStringToInt( std::string newString);
extern void updateScores();
extern bool keyboard_keypressed();
extern void check_highscore();
extern void addScore( std::string name);

extern const int robotWidth;
extern const int robotHeight;

extern float robot_x;
extern float robot_y;

extern int health;
extern unsigned int score;
extern bool invincible;
extern int screenshake;
extern int magneticStrength;
extern int invincibleTimer;
extern int magneticTimer;
extern bool is_high_score;

// For stats
extern int robot_distance;
extern int energyCollected;
extern int powerupsCollected;
extern int debrisCollided;

extern bool joystick_enabled;



extern FONT* orbitron_14;
extern FONT* orbitron;

extern void abort_on_error( std::string message);

extern BITMAP *load_bitmap_ex( std::string file);
extern SAMPLE *load_sample_ex( std::string file);
extern FONT *load_font_ex( std::string file);

extern float Get2dDistance(float x1, float y1, float x2, float y2);

extern int random(int newLowest, int newHighest);

extern bool collision(float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2);

extern void fade_in(BITMAP* bmp_orig, int speed);
extern void fade_out(int speed);

#endif
