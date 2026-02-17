/*
 * Globals
 * Variables that are used by multiple files
 * A.D.S. Games
 */
#ifndef GLOBALS_H
#define GLOBALS_H

// Import libraries
#include <asw/asw.h>

#include <string>

#include "Settings.h"

#define STAT_DISTANCE 0
#define STAT_ENERGY 1
#define STAT_POWERUPS 2
#define STAT_DEBRIS 3

// Global variables
extern int score;
extern int screenshake;
extern int fps;

constexpr int   SCREEN_W = 800;
constexpr int   SCREEN_H = 600;
constexpr float S_W_F    = float(SCREEN_W);
constexpr float S_H_F    = float(SCREEN_H);

// Data
extern int stats[4];

// Fonts
extern asw::Font orbitron_12;
extern asw::Font orbitron_18;
extern asw::Font orbitron_24;
extern asw::Font orbitron_30;
extern asw::Font orbitron_36;

#endif
