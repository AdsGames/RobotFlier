/**
 * Display
 * Danny Van Stemp and Allan Legemaate
 * Sets up and changes passed display
 * 20/11/2018
 **/

#ifndef ENGINE_DISPLAY_WINDOW_H
#define ENGINE_DISPLAY_WINDOW_H

#include <allegro5/display.h>
#include <string>

#include "../Scene.h"

// Possible screen modes
enum DISPLAY_MODE {
  FULLSCREEN_WINDOW_STRETCH,
  FULLSCREEN_WINDOW_LETTERBOX,
  FULLSCREEN_WINDOW_CENTER,
  WINDOWED,
  NUM_GRAPHICS_MODES
};

class Window {
 public:
  // Ctor and Dtor
  Window();
  virtual ~Window(){};

  // Setters
  void setMode(DISPLAY_MODE mode);

  // Getters
  int getDisplayMode();

  int getDrawWidth();
  int getDrawHeight();

  int getTranslationX();
  int getTranslationY();

  float getScaleX();
  float getScaleY();

  int getScaleWidth();
  int getScaleHeight();

  void hideMouse();
  void showMouse();

  void draw(Scene* current_scene);

  ALLEGRO_DISPLAY* getDisplay() { return display; }

  void setTitle(const std::string& title);

 private:
  // Size of drawing buffer
  int draw_w;
  int draw_h;

  // Size of window
  int window_w;
  int window_h;

  // Translation amount
  int translation_x;
  int translation_y;

  // Draw buffer scale percent (as decimal)
  float scale_x;
  float scale_y;

  // Display mode
  DISPLAY_MODE display_mode;

  // Active display
  ALLEGRO_DISPLAY* display;
  ALLEGRO_BITMAP* buffer;

  // Fps timer
  double old_time = 0;
  int frames_array[100];
  int frame_index = 0;
  int fps = 0;

  // Private setters to reduce copy code
  void setWindowSize(const int width, const int height);
  void setScale(const float x, const float y);
  void setTranslation(const int x, const int y);
};

#endif  // ENGINE_DISPLAY_WINDOW_H
