/**
 * Font
 * Allan Legemaate
 * Wrapper for allegro font
 * Easy interface to interact with fonts
 * 10/08/2020
 **/

#ifndef ENGINE_FONTS_FONT
#define ENGINE_FONTS_FONT

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>

class Font {
 public:
  Font();
  Font(const std::string path, const int size);
  virtual ~Font();

  void load(const std::string& path, const int size);

  void draw(const int x,
            const int y,
            const std::string& text,
            const int flags = 0);

  int getLineHeight();

 private:
  static ALLEGRO_FONT* loadFont(const std::string& file, const int size);

  ALLEGRO_FONT* font;
  int font_size;
};

#endif  // ENGINE_FONTS_FONT
