/*
 * Globals
 * Variables that are used by multiple files
 * A.D.S. Games
 */
#pragma once

// Import libraries
#include <array>
#include <asw/asw.h>

#include "settings.h"

#define STAT_DISTANCE 0
#define STAT_ENERGY 1
#define STAT_POWERUPS 2
#define STAT_DEBRIS 3

// Global variables
extern int score;
extern float screenshake;
extern int fps;

constexpr int SCREEN_W = 800;
constexpr int SCREEN_H = 600;
constexpr float S_W_F = float(SCREEN_W);
constexpr float S_H_F = float(SCREEN_H);

// Data
extern std::array<int, 4> stats;

// Fonts
extern asw::Font orbitron_12;
extern asw::Font orbitron_18;
extern asw::Font orbitron_24;
extern asw::Font orbitron_30;
extern asw::Font orbitron_36;
