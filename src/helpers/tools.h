/*
 * Tools Class
 * Allan Legemaate
 * 13/01/2017
 * Functions that may be needed by multiple files
 */
#ifndef TOOLS_H
#define TOOLS_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include <time.h>

#include <fstream>
#include <sstream>
#include <string>

// Error handling loading functions
extern ALLEGRO_BITMAP* load_bitmap_ex(std::string file);
extern ALLEGRO_SAMPLE* load_sample_ex(std::string file);
extern ALLEGRO_SAMPLE* logg_load_ex(std::string file);
extern ALLEGRO_FONT* load_font_ex(std::string file, int size, int flags);

extern void abort_on_error(std::string message);

// Random generator
extern int random(int newLowest, int newHighest);

// Math related functions
extern bool collision(float xMin1,
                      float xMax1,
                      float xMin2,
                      float xMax2,
                      float yMin1,
                      float yMax1,
                      float yMin2,
                      float yMax2);

#endif  // TOOLS_H
