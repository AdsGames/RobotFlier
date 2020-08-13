/**
 * Display Mode
 * Danny Van Stemp and Allan Legemaate
 * Sets up and changes passed display
 * 20/11/2018
 **/

#ifndef ENGINE_DISPLAY_DISPLAYMODE_H
#define ENGINE_DISPLAY_DISPLAYMODE_H

#include <allegro5/display.h>

#include <string>

class DisplayMode {
 public:
  // Ctor and Dtor
  DisplayMode(){};
  virtual ~DisplayMode(){};

  // Possible screen modes
  enum {
    FULLSCREEN_WINDOW_STRETCH,
    FULLSCREEN_WINDOW_LETTERBOX,
    FULLSCREEN_WINDOW_CENTER,
    WINDOWED,
    NUM_GRAPHICS_MODES
  };

  // Setters
  static void setMode(int);
  static void setActiveDisplay(ALLEGRO_DISPLAY** newdisplay);

  // Getters
  static int getDisplayMode();

  static int getDrawWidth();
  static int getDrawHeight();

  static int getTranslationX();
  static int getTranslationY();

  static float getScaleX();
  static float getScaleY();

  static int getScaleWidth();
  static int getScaleHeight();

 private:
  // Size of drawing buffer
  static int draw_w;
  static int draw_h;

  // Size of window
  static int window_w;
  static int window_h;

  // Translation amount
  static int translation_x;
  static int translation_y;

  // Draw buffer scale percent (as decimal)
  static float scale_x;
  static float scale_y;

  // Display mode
  static int display_mode;

  // Active display
  static ALLEGRO_DISPLAY** display;

  // Private setters to reduce copy code
  static void setWindowSize(const int width, const int height);
  static void setScale(const float x, const float y);
  static void setTranslation(const int x, const int y);
};

#endif  // ENGINE_DISPLAY_DISPLAYMODE_H
