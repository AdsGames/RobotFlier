#ifndef TOOLS_H
#define TOOLS_H

#include <allegro.h>
#include <alpng.h>
#include <time.h>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>

extern bool joy_buttonpressed();
extern std::string convertInt( int number);
extern int convertStringToInt( std::string newString);
extern void updateScores( std::string scoreCopy[][2]);
extern bool check_highscore( std::string scoreCopy[][2], int score);
extern void addScore( std::string scoreCopy[][2], int newScore, std::string name);
extern bool keyboard_keypressed();

extern void abort_on_error( std::string message);

extern BITMAP *load_bitmap_ex( std::string file);
extern SAMPLE *load_sample_ex( std::string file);
extern FONT *load_font_ex( std::string file);

extern float Get2dDistance(float x1, float y1, float x2, float y2);

extern int random(int newLowest, int newHighest);

extern bool collision(float xMin1, float xMax1, float xMin2, float xMax2, float yMin1, float yMax1, float yMin2, float yMax2);

extern void fade_in(BITMAP* bmp_orig, int speed);
extern void fade_out(int speed);

#endif // TOOLS_H
